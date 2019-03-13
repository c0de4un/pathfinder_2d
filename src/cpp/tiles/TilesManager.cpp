/*
* Copyright © 2019 Denis Zyamaev (code4un@yandex.ru) All rights reserved.
* Authors: Denis Zyamaev (code4un@yandex.ru)
* All rights reserved.
* API: C++ 11
* License: see LICENSE.txt
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must display the names 'Denis Zyamaev' and
* in the credits of the application, if such credits exist.
* The authors of this work must be notified via email (code4un@yandex.ru) in
* this case of redistribution.
* 3. Neither the name of copyright holders nor the names of its contributors
* may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
* IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

// HEADER
#include "TilesManager.hpp"

// Include Tile
#include "Tile.hpp"

// Include Route
#include "Route.hpp"

// Include TMap
#include "TMap.hpp"

namespace c0de4un
{
	
	namespace org
	{
		
		namespace path2d
		{
			
			// -------------------------------------------------------- \\
			
			// ===========================================================
			// Constructor
			// ===========================================================
			
			/*
			 * TilesManager constructor.
			 * 
			 * (!) Cause generation of Tiles-Map, so large memory allocation
			 * caused by this constructor.
			 * 
			 * @thread_safety - not thread-safe.
			 * @param pFile - tile-map source-file.
			 * @throws - can throw bad_alloc.
			*/
			TilesManager::TilesManager( const std::string & pFile )
				: mMap( nullptr ),
				mTilesQueue{ std::vector<Tile*>( ), std::vector<Tile*>( ) },
				mAquiredTiles( ), mStart( nullptr ), mFinish( nullptr )
			{
				
				// Print Debug-message to the console
				std::cout << "TilesManager::constructor" << std::endl;
				
				// Load Map
				onLoadMap( pFile );
				
				// Calculate initial Tiles queue capacity
				const std::uint16_t initialQueueCapacity_( ( mMap->mRows * mMap->mCols ) / 2 );
				
				// Pre-Reserve Tiles Queues
				mTilesQueue[0].reserve( initialQueueCapacity_ );
				mTilesQueue[1].reserve( initialQueueCapacity_ );
				
				// Reserve aquired-Tiles queue.
				mAquiredTiles.reserve( initialQueueCapacity_ );
				
			}
			
			// ===========================================================
			// Destructor
			// ===========================================================
			
			/*
			 * TilesManager destructor.
			 * 
			 * @thread_safety - not thread-safe.
			 * throws - no exceptions.
			*/
			TilesManager::~TilesManager( )
			{
				
				// Print Debug-message to the console
				std::cout << "TilesManager::destructor" << std::endl;
				
				// Release Map
				if ( mMap != nullptr )
					delete mMap;
				
			}
			
			// ===========================================================
			// Getter & Setter
			// ===========================================================
			
			/* Returns start-Tile. */
			Tile *const TilesManager::getStart( ) const noexcept
			{ return( mStart ); }
			
			/* Returns finish-Tile. */
			Tile *const TilesManager::getFinish( ) const noexcept
			{ return( mFinish ); }
			
			/*
			 * Searches for available Tile with minimum steps count.
			 * 
			 * @thread_safety - not required.
			 * @param srcTile - Tile to search from.
			*/
			Tile *const TilesManager::getTile_Backward( const Tile *const srcTile ) noexcept
			{
				
				// Result
				Tile * result_( nullptr );
				
				// Bottom Row
				std::uint16_t row_( srcTile->mRow + 1 );
				
				// Tile
				Tile * tile_( nullptr );
				
				// Check Bottom-Border
				if ( row_ < mMap->mRows )
				{
					
					// Get Tile
					tile_ = mMap->mTiles[row_][srcTile->mCol];
					
					// Check Tile state
					if ( tile_->mState == Tile::TILE_STATE_PRE_RESERVED )
						result_ = tile_;
					
				}
				
				// Check Top-Border
				if ( srcTile->mRow > 0 )
				{
					
					// Upper Row
					row_ = srcTile->mRow - 1;
					
					// Get Tile
					tile_ = mMap->mTiles[row_][srcTile->mCol];
					
					// Check Tile state & compare to the previous-Tile.
					if ( ( result_ == nullptr || result_->mStepID > tile_->mStepID ) && tile_->mState == Tile::TILE_STATE_PRE_RESERVED )
						result_ = tile_;
					
				}
				
				// Col
				std::uint16_t col_( 0 );
				
				// Check Left-Border
				if ( srcTile->mCol > 0 )
				{
					
					// Left Col
					col_ = srcTile->mCol - 1;
					
					// Get Left Tile
					tile_ = mMap->mTiles[srcTile->mRow][col_];
					
					// Check Tile state & compare to the previous-Tile.
					if ( ( result_ == nullptr || result_->mStepID > tile_->mStepID ) && tile_->mState == Tile::TILE_STATE_PRE_RESERVED )
						result_ = tile_;
					
				}
				
				// Right Col
				col_ = srcTile->mCol + 1;
				
				// Check Right-Border
				if ( col_ < mMap->mCols )
				{
					
					// Get Right Tile
					tile_ = mMap->mTiles[srcTile->mRow][col_];
					
					// Check Tile state & compare to the previous-Tile.
					if ( ( result_ == nullptr || result_->mStepID > tile_->mStepID ) && tile_->mState == Tile::TILE_STATE_PRE_RESERVED )
						result_ = tile_;
					
				}
				
				// Return result
				return( result_ );
				
			}
			
			/*
			 * Gathering (collecting) all available Tiles.
			 * 
			 * @thread_safety - not required.
			 * @param srcTile - source-Tile (start).
			 * @throws - no exceptions.
			*/
			void TilesManager::waveSearchTiles( Tile *const srcTile ) noexcept
			{
				
				// Current Tiles queue
				std::vector<Tile*> * tilesQueue_( &mTilesQueue[0] );
				
				// Search Tiles
				if ( !searchTiles( srcTile, *tilesQueue_, 1 ) )
					return;
				
				// Steps counter
				std::uint16_t stepCount( 2 );
				
				// Stop Tiles search
				bool stopSearch_( false );
				
				// Tile
				Tile * tile_( nullptr );
				
				// Next Tiles queue
				std::vector<Tile*> * nextTilesQueue_( &mTilesQueue[1] );
				
				// Gather (collect, aquire) all available Tiles
				while( !stopSearch_ )
				{
					
					// Search Tiles for next queue
					for( Tile * tile_ : *tilesQueue_ )
					{
						
						// Set Tile-state
						tile_->mState = Tile::TILE_STATE_PRE_RESERVED;
						
						// Search Tiles
						searchTiles( tile_, *nextTilesQueue_, stepCount );
						
					}
					
					// Clear Tiles queue
					tilesQueue_->clear( );
					
					// Check if both Queues are empty
					if ( nextTilesQueue_->empty( ) )
					{
						
						// Stop search if nothing found
						stopSearch_ = true;
						
						// Stop
						break;
						
					}
					
					// Switch Tiles queues
					tilesQueue_ = nextTilesQueue_;
					nextTilesQueue_ = tilesQueue_ == &mTilesQueue[0] ? &mTilesQueue[1] : &mTilesQueue[0];
					
					// Next step
					stepCount++;
					
				}
				
				//
				std::cout << "Available Tiles collected" << std::endl;
				
				// Print Tiles
				printTiles( );
				
			}
			
			/*
			 * Search available Tiles & build shortest-Route from source-Tile to the destination-Tile.
			 * 
			 * (?) Route/Path is build with Lee-Wave Lagorithm, where entire
			 * map scanned/searched for all available Tiles, then around
			 * destination-Tile Route with lesser Tiles-count selected.
			 * 
			 * (?) No diagonally moves.
			 * 
			 * @thread_safety - not thread-safe.
			 * @param srcTile - source-Tile (start).
			 * @param dstTile - destination-Tile (finish).
			 * @return - Route or null.
			 * @throws - no exceptions.
			*/
			Route *const TilesManager::getRoute( Tile *const srcTile, Tile *const dstTile ) noexcept
			{
				
				// Collect/gether Tiles using Wave-algorithm, starting from destination-Tile.
				waveSearchTiles( dstTile );
				
				// Build optimized Route
				Route *const result_( buildRoute( srcTile ) );
				
				// Reset unused Tiles
				resetUnusedTiles( );
				
				// Print Tiles map to show Route
				printTiles( );
				
				// Return result-Route
				return( result_ );
				
			}
			
			// ===========================================================
			// Methods
			// ===========================================================
			
			/*
			 * Resets not requested Tiles (candidates).
			 * 
			 * @thread_safety - not required.
			 * @throws - no exceptions.
			*/
			void TilesManager::resetUnusedTiles( ) noexcept
			{
				
				// Reset all unused Tiles
				for( Tile * tile_ : mAquiredTiles )
				{
					
					// Reset candidate-Tile
					if ( tile_->mState == Tile::TILE_STATE_PRE_RESERVED )
					{
						
						// Reset Tile state
						tile_->mState = Tile::TILE_STATE_NONE;
						
						// Reset previous-Tile pointer-value
						tile_->mPrevTile = nullptr;
						
						// Reset Tile steps
						tile_->mStepID = 0;
						
					}
					
				}
				
				// Clear Aquired candidate-Tiles queue
				mAquiredTiles.clear( );
				
				// Clear Tiles queues
				mTilesQueue[0].clear( );
				mTilesQueue[1].clear( );
				
			}
			
			/*
			 * Searches for the available Tiles & add them to the provided queue.
			 * 
			 * (?) Since we don't use diagonal directions, this method
			 * don't use cycles to read surrounding Tiles states.
			 * 
			 * (?) This method doesn't check map-border to reduce calculations-tile,
			 * so all borders of a map must be reserved.
			 * 
			 * @thread_safety - not thread-safe (not required).
			 * @param srcTile - Tile to search from.
			 * @param pQueue - Tiles queue.
			 * @param pStep - Step.
			 * @return - 'false' if nothing found.
			 * @throws - no exceptions.
			*/
			const bool TilesManager::searchTiles( Tile *const srcTile, std::vector<Tile*> & pQueue, const std::uint16_t & pStep ) noexcept
			{
				
				// Result
				bool result_( false );
				
				// Bottom-Row
				std::uint16_t row_( srcTile->mRow + 1 );
				
				// Tile
				Tile * tile_( nullptr );
				
				//
				if ( row_ < mMap->mRows )
				{
					
					// Get Bottom Tile
					tile_ = mMap->mTiles[row_][srcTile->mCol];
					
					// Check Tile state
					if ( tile_->mState == Tile::TILE_STATE_NONE )
					{
						// Set result
						result_ = true;
						
						// Set Tile state
						tile_->mState = Tile::TILE_STATE_UNCHECKED;
						
						// Set Tile's previous-Tile
						tile_->mPrevTile = srcTile;
						
						// Set Tile Step-ID
						tile_->mStepID = pStep;
						
						// Add Tile to aquired (collected/gathered) Tiles container.
						mAquiredTiles.push_back( tile_ );
					
						// Add Tile to the queue
						pQueue.push_back( tile_ );
					
					}
					
				}
				
				//
				if ( srcTile->mRow > 0 )
				{
					
					// Up-Row
					row_ = srcTile->mRow - 1;
					
					// Get Upper Tile
					tile_ = mMap->mTiles[row_][srcTile->mCol];
					
					// Check Tile state
					if ( tile_->mState == Tile::TILE_STATE_NONE )
					{
						// Set result
						result_ = true;
					
						// Set Tile state
						tile_->mState = Tile::TILE_STATE_UNCHECKED;
					
						// Set Tile's previous-Tile
						tile_->mPrevTile = srcTile;
					
						// Set Tile Step-ID
						tile_->mStepID = pStep;
					
						// Add Tile to aquired (collected/gathered) Tiles container.
						mAquiredTiles.push_back( tile_ );
					
						// Add Tile to the queue
						pQueue.push_back( tile_ );
					
					}
					
				}
				
				// Left Col
				std::uint16_t col_( 0 );
				
				//
				if ( srcTile->mCol > 0 )
				{
					
					//
					col_ = srcTile->mCol - 1;
					
					// Get Left Tile
					tile_ = mMap->mTiles[srcTile->mRow][col_];
				
					// Check Tile state
					if ( tile_->mState == Tile::TILE_STATE_NONE )
					{
						// Set result
						result_ = true;
					
						// Set Tile state
						tile_->mState = Tile::TILE_STATE_UNCHECKED;
						
						// Set Tile's previous-Tile
						tile_->mPrevTile = srcTile;
						
						// Set Tile Step-ID
						tile_->mStepID = pStep;
					
						// Add Tile to aquired (collected/gathered) Tiles container.
						mAquiredTiles.push_back( tile_ );
					
						// Add Tile to the queue
						pQueue.push_back( tile_ );
					
					}
					
				}
				
				// Right Colr
				col_ = srcTile->mCol + 1;
				
				//
				if ( col_ < mMap->mCols )
				{
					
					// Get Rigth Tile
					tile_ = mMap->mTiles[srcTile->mRow][col_];
					
					// Check Tile state
					if ( tile_->mState == Tile::TILE_STATE_NONE )
					{
						// Set result
						result_ = true;
						
						// Set Tile state
						tile_->mState = Tile::TILE_STATE_UNCHECKED;
						
						// Set Tile's previous-Tile
						tile_->mPrevTile = srcTile;
						
						// Set Tile Step-ID
						tile_->mStepID = pStep;
					
						// Add Tile to aquired (collected/gathered) Tiles container.
						mAquiredTiles.push_back( tile_ );
					
						// Add Tile to the queue
						pQueue.push_back( tile_ );
					
					}
					
				}
				
				// Return result
				return( result_);
				
			}
			
				/*
				 * Builds Route (path) using backward-steps.
				 * 
				 * (?) Lee-Wave algorithm sorts Tiles by their steps number,
				 * to build optimized path/route.
				 * 
				 * @thread_safety - not required.
				 * @param dstTile - Route destination-Tile.
				 * @throws - no exceptions.
				*/
				Route *const TilesManager::buildRoute( Tile *const dstTile ) noexcept
				{
					
					// Print Steps
					printSteps( );
					
					// Next-Tile
					Tile * tile_( getTile_Backward( dstTile ) );
					
					// Cancel if Route not complete
					if ( tile_ == nullptr )
						return( nullptr );
					
					// Steps counter
					std::uint16_t stepsCount_( 0 );
					
					// Result
					Route *const result_( new Route( ) );
					
					// Get number of steps
					const std::uint16_t & totalSteps_( tile_->mStepID );
					
					// Reserve Tile
					tile_->mState = Tile::TILE_STATE_RESERVED;
					
					// Add first Tile to the Route
					result_->mTiles.push_back( tile_ );
					
					// Previous-Tile
					Tile * prevTile_( nullptr );
					
					// Collect Tile for the Route with backward steps.
					while( stepsCount_ < totalSteps_ )
					{
						
						// Get previous-Tile
						prevTile_ = tile_->mPrevTile;
						
						// No backward step is available
						if ( prevTile_ == nullptr )
						{
							
							// Print error-message
							std::cout << "TilesManager::buildRoute - previous Tile not found !" << std::endl;
							
							// Delete Route
							delete result_;
							
							// Return null
							return( nullptr );
							
						}
						
						// Reserve Tile
						tile_->mState = Tile::TILE_STATE_RESERVED;
						
						// Next (Backward) Tile
						tile_ = prevTile_;
						
						// Add Tile to the Route
						result_->mTiles.push_back( tile_ );
						
						// Backward
						stepsCount_++;
						
					}
					
					// Return result-Route
					return( result_ );
					
				}
			
			/*
			 * Loads Tile-Map data.
			 * 
			 * @thread_safety - not thread-safe.
			 * @param pFile - source-file.
			 * @throws - can throw exception (file not found || io, bad_alloc)
			*/
			void TilesManager::onLoadMap( const std::string & pFile )
			{
				
				// Guarded-Block
				try
				{
					
					// Create input-stream to a File & open it
					std::ifstream inputStream_( pFile, std::ifstream::in );
					
					// Check input stream state
					if ( !inputStream_.good( ) )
					{
						
						// Print message to a console
						std::cout << "TilesManager::onLoadMap - failed to open file#" << pFile << std::endl;
						
						// Cancel
						return;
						
					}
					
					// Buffer to store readed line
					char charsBuffer_[8192]; // 8 Kb
					
					// Read Cols
					inputStream_.getline( charsBuffer_, 8192 );
					
					// Cast chars to std::string
					std::string line_( charsBuffer_ );
					
					// Value in string
					std::string valStr_( line_.substr( line_.find_last_of( '=' ) + 1 ) );
					
					// Cast string-value to integer
					const std::uint16_t cols_( (std::uint16_t)std::stoi( valStr_ ) );
					
					// Print Number of Cols
					std::cout << "Cols=" << std::to_string( cols_ ) << std::endl;
					
					// Read Rows
					inputStream_.getline( charsBuffer_, 8192 );
					
					// Cast chars to string
					line_ = charsBuffer_; // constructor
					
					// Value in string
					valStr_ = line_.substr( line_.find_last_of( '=' ) + 1 );
					
					// Cast string-value to integer
					const std::uint16_t rows_( (std::uint16_t)std::stoi( valStr_ ) );
					
					// Print Number of Rows
					std::cout << "Rows=" << std::to_string( rows_ ) << std::endl;
					
					// Create Tiles Map
					this->mMap = new TMap( rows_, cols_ );
					
					// Tile state
					std::uint8_t tileState_( 0 );
					
					// String to store Tile state
					std::string tileStateName( "" );
					
					// Read Rows
					for( std::uint16_t rowIndex = 0; rowIndex < rows_; rowIndex++ )
					{
						
						// Read line
						inputStream_.getline( charsBuffer_, 8192 );
						
						// Cast chars to string
						line_ = charsBuffer_; // constructor
						
						// Check Rows Width
						if ( line_.size( ) < cols_ )
							throw std::exception( "bad tile map format ! Invalid row size." );
						
						// Tile
						Tile * tile_( nullptr );
						
						// Read Cols
						for( std::uint16_t colIndex = 0; colIndex < cols_; colIndex++ )
						{
							
							// Get Tile
							tile_ = mMap->mTiles[rowIndex][colIndex];
							
							// Cast Tile State Name from char to string
							tileStateName = line_[colIndex];
							
							// Cast Tile State from string to integer
							tileState_ = std::stoi( tileStateName );
							
							// Print Tile State ID
							switch( tileState_ )
							{
								case Tile::TILE_STATE_START:
									mStart = tile_;
									std::cout << "S";
									break;
								case Tile::TILE_STATE_FINISH:
									mFinish = tile_;
									std::cout << "F";
									break;
								default:
									std::cout << std::to_string( tileState_ );
									break;
							}
							
							// Set Tile State
							tile_->mState = tileState_;
							
						}
						
						// Next line in Console
						std::cout << std::endl;
						
					}
					
				}
				catch( const std::exception & pException )
				{
					
					// Print to console
					std::cout << "TilesManager::onLoadMap - failed to load from file#" << pFile << ", error: " << pException.what( ) << std::endl;
					
				}
				
			}
			
			/*
			 * Prints Tiles to a console.
			 * 
			 * @thread_safety - not thread-safe.
			 * @throws - no exceptions.
			*/
			void TilesManager::printTiles( ) const noexcept
			{
				
				// Tile state
				std::uint8_t tileState_( 0 );
				
				// Rows
				for( std::uint16_t rowIndex_ = 0; rowIndex_ < mMap->mRows; rowIndex_++ )
				{
					
					// Cols
					for( std::uint16_t colIndex_ = 0; colIndex_ < mMap->mCols; colIndex_++ )
					{
						
						// Get Tile-state
						tileState_ = mMap->mTiles[rowIndex_][colIndex_]->mState;
						
						// Print Tile State ID
						switch( tileState_ )
						{
							case Tile::TILE_STATE_START:
								std::cout << "S";
								break;
							case Tile::TILE_STATE_FINISH:
								std::cout << "F";
								break;
							default:
								std::cout << std::to_string( tileState_ );
								break;
						}
						
					}
					
					// Next line in Console
					std::cout << std::endl;
					
				}
				
			}
			
				/*
				 * Prits Tiles steps-count from destination-Tile to source-Tile.
				 * 
				 * @thread_safety - not required.
				 * @throws - no exceptions.
				*/
				void TilesManager::printSteps( ) const noexcept
				{
					
					// Print message
					std::cout << "Steps:" << std::endl;
					
					// Tile
					Tile * tile_( nullptr );
					
					// Rows
					for( std::uint16_t rowIndex_ = 0; rowIndex_ < mMap->mRows; rowIndex_++ )
					{
						
						// Cols
						for( std::uint16_t colIndex_ = 0; colIndex_ < mMap->mCols; colIndex_++ )
						{
							
							// Get Tile
							tile_ = mMap->mTiles[rowIndex_][colIndex_];
							
							//Print Tile Step-ID
							if ( tile_->mStepID < 10 )
								std::cout << " " << std::to_string( tile_->mStepID );
							else
								std::cout << std::to_string( tile_->mStepID );
							
						}
						
						// Next line in Console
						std::cout << std::endl;
						
					}
					
				}
			
			// -------------------------------------------------------- \\
			
		}// path2d
		
	}// org
	
}// c0de4un