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

#pragma once

// Include 'Precompiled-Headers'
#include "../pch_cxx.hpp"

// Include 'forward-declarations'
#include "tiles_fwd.hpp"

// Include Tile
#include "Tile.hpp"

// Mark c0de4un::org::path2d::Route as declared, to avoid forward-declaration.
#define C0DE4UN_ORG_PATH_2D_ROUTE_DECL

// Enable structure-data (fields, variables) alignment (by compiler) to 1 byte
#pragma pack( push, 1 )

namespace c0de4un
{

	namespace org
	{

		namespace path2d
		{

			// -------------------------------------------------------- \\

			/*
			 * Route - 2D Route of Tiles.
			 * 
			 * @version 1.0.0
			 * @authors: Z. Denis (code4un@yandex.ru)
			 * @since 10.03.2019
			*/
			struct Route final
			{

				// -------------------------------------------------------- \\
				
				// ===========================================================
				// Fields
				// ===========================================================

				/* Length */
				std::uint16_t mLength;

				/* Tiles */
				std::vector<Tile*> mTiles;
				
				/* Distance from final Tile to destination Tile (1 - max. close). */
				std::uint16_t mDistance;
				
				// ===========================================================
				// Constructor
				// ===========================================================
				
				/*
				 * Route constructor.
				 * 
				 * @thread_safety - not required.
				 * @throws - can throw bad_alloc.
				*/
				explicit Route( )
					: mLength( 0 ),
					mTiles( ),
					mDistance( 0 )
				{
				}
				
				// ===========================================================
				// Destructor
				// ===========================================================
				
				/*
				 * Route destructor.
				 * 
				 * @thread_safety - not thread-safe.
				 * @throws - no exceptions.
				*/
				~Route( )
				{
					
					// Clear
					this->clear( );
					
				}
				
				// ===========================================================
				// Methods
				// ===========================================================
				
				/*
				 * Add Tile.
				 * 
				 * @thread_safety - not thread-safe (not required).
				 * @param pTile - Tile.
				 * @throws - no exceptions.
				*/
				void addTile( Tile *const pTile ) noexcept
				{
					
					// Add Tile
					mTiles.push_back( pTile );
					
					// Update Route Length
					mLength = (std::uint16_t)mTiles.size( );
					
				}
				
				/*
				 * Clear Route
				 * 
				 * @thread_safety - not thread-safe.
				 * @throws - no exceptions.
				*/
				void clear( ) noexcept
				{
					
					// Cancel if not Tiles added
					if ( mTiles.empty( ) )
						return;
					
					// Reset each Tile
					for( Tile *const tile_ : mTiles )
					{
						
						// Reset Tile
						if ( tile_->mState == Tile::TILE_STATE_RESERVED )
						{
							
							// Reset Tile-state
							tile_->mState = Tile::TILE_STATE_NONE;
							
							// Reset Tile steps count
							tile_->mStepID = 0;
							
						}
						
					}
					
					// Clear Route
					mTiles.clear( );
					
				}
				
				// -------------------------------------------------------- \\

			private:

				// -------------------------------------------------------- \\
				
				// ===========================================================
				// Deleted
				// ===========================================================

				Route( const Route & ) = delete;
				Route & operator=( const Route & ) = delete;
				Route( Route && ) = delete;
				Route & operator=( Route && ) = delete;

				// -------------------------------------------------------- \\

			};

			// -------------------------------------------------------- \\

		}// path2d

	}// org

}// c0de4un

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )