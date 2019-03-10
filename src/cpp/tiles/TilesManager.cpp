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
				: mMap( nullptr )
			{
				
				// Print Debug-message to the console
				std::cout << "TilesManager::constructor" << std::endl;
				
				// Load Map
				onLoadMap( pFile );
				
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
			// Methods
			// ===========================================================

			/*
			 * Loads Tile-Map data.
			 * 
			 * @thread_safety - not thread-safe.
			 * @param pFile - source-file.
			 * @throws - can throw exception (file not found || io, bad_alloc)
			*/
			void TilesManager::onLoadMap( const std::string & pFile )
			{// TODO TilesManager::onLoadMap
				
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
						
						// Read Cols
						for( std::uint16_t colIndex = 0; colIndex < cols_; colIndex++ )
						{
							
							// Cast Tile State Name from char to string
							tileStateName = line_[colIndex];
							
							// Cast Tile State from string to integer
							tileState_ = std::stoi( tileStateName );
							
							// Print Tile State ID
							std::cout << std::to_string( tileState_ );
							
							// Set Tile State
							mMap->mTiles[rowIndex][colIndex]->mState = tileState_;
							
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
			
			// -------------------------------------------------------- \\
			
		}// path2d
		
	}// org
	
}// c0de4un