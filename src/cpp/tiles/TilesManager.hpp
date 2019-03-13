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

// Mark c0de4un::org::path2d::TilesManager as declared, to avoid forward-declaration.
#define C0DE4UN_ORG_PATH_2D_TILES_MANAGER_DECL

namespace c0de4un
{

	namespace org
	{

		namespace path2d
		{

			// -------------------------------------------------------- \\

			/*
			 * TilesManager - manage 2D tiles.
			 * 
			 * @version 1.0.0
			 * @authors: Z. Denis (code4un@yandex.ru)
			 * @since 10.03.2019
			*/
			class TilesManager final
			{

			private:

				// -------------------------------------------------------- \\
				
				// ===========================================================
				// Fields
				// ===========================================================
				
				/* Tiles queues. Used to rotate/switch between current & next Tiles queue. */
				std::vector<Tile*> mTilesQueue[2];
				
				/* Aquired Tiles queue. Used to reset unused Tiles when Route is found. */
				std::vector<Tile*> mAquiredTiles;
				
				/* Start */
				Tile * mStart;
				
				/* Finish */
				Tile * mFinish;
				
				// ===========================================================
				// Getter & Setter
				// ===========================================================
				
				/*
				 * Searches for available Tile with minimum steps count.
				 * 
				 * @thread_safety - not required.
				 * @param srcTile - Tile to search from.
				*/
				Tile *const getTile_Backward( const Tile *const srcTile ) noexcept;
				
				// ===========================================================
				// Methods
				// ===========================================================
				
				/*
				 * Resets not requested Tiles (candidates).
				 * 
				 * @thread_safety - not required.
				 * @throws - no exceptions.
				*/
				void resetUnusedTiles( ) noexcept;
				
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
				const bool searchTiles( Tile *const srcTile, std::vector<Tile*> & pQueue, const std::uint16_t & pStep ) noexcept;
				
				/*
				 * Gathering (collecting) all available Tiles.
				 * 
				 * @thread_safety - not required.
				 * @param srcTile - source-Tile (start).
				 * @throws - no exceptions.
				*/
				void waveSearchTiles( Tile *const srcTile ) noexcept;
				
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
				Route *const buildRoute( Tile *const dstTile ) noexcept;
				
				/*
				 * Loads Tile-Map data.
				 * 
				 * @thread_safety - not thread-safe.
				 * @param pFile - source-file.
				 * @throws - can throw exception (file not found || io, bad_alloc)
				*/
				void onLoadMap( const std::string & pFile );
				
				// -------------------------------------------------------- \\

			public:

				// -------------------------------------------------------- \\
				
				// ===========================================================
				// Fields
				// ===========================================================
				
				/* Map */
				path2D_TMap * mMap;
				
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
				 * @throws - can throw bad_alloc, io.
				*/
				explicit TilesManager( const std::string & pFile );

				// ===========================================================
				// Destructor
				// ===========================================================
				
				/*
				 * TilesManager destructor.
				 * 
				 * @thread_safety - not thread-safe.
				 * throws - no exceptions.
				*/
				~TilesManager( );
				
				// ===========================================================
				// Getter & Setter
				// ===========================================================
				
				/* Returns start-Tile. */
				Tile *const getStart( ) const noexcept;
				
				/* Returns finish-Tile. */
				Tile *const getFinish( ) const noexcept;
				
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
				Route *const getRoute( Tile *const srcTile, Tile *const dstTile ) noexcept;
				
				// ===========================================================
				// Methods
				// ===========================================================
				
				/*
				 * Prints Tiles to a console.
				 * 
				 * @thread_safety - not thread-safe.
				 * @throws - no exceptions.
				*/
				void printTiles( ) const noexcept;
				
				/*
				 * Prits Tiles steps-count from destination-Tile to source-Tile.
				 * 
				 * @thread_safety - not required.
				 * @throws - no exceptions.
				*/
				void printSteps( ) const noexcept;
				
				// -------------------------------------------------------- \\

			}; // TilesManager

			// -------------------------------------------------------- \\

		}// path2d

	}// org

}// c0de4un