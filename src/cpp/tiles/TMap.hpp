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

// Enable structure-data (fields, variables) alignment (by compiler) to 1 byte
#pragma pack( push, 1 )

// Mark c0de4un::org::path2d::TMap as declared, to avoid forward-declaration.
#define C0DE4UN_ORG_PATH_2D_TMAP_DECL

namespace c0de4un
{

	namespace org
	{

		namespace path2d
		{

			// -------------------------------------------------------- \\
			
			/*
			 * TMap - 2D Tiles Map.
			 * 
			 * @version 1.0.0
			 * @authors: Z. Denis (code4un@yandex.ru)
			 * @since 10.03.2019
			*/
			struct TMap final
			{

				// -------------------------------------------------------- \\

				// ===========================================================
				// Constants
				// ===========================================================
				
				/* Cols */
				const std::uint16_t mCols;
				
				/* Rows */
				const std::uint16_t mRows;
				
				// ===========================================================
				// Fields
				// ===========================================================
				
				/* Tiles 2D Array */
				Tile* ** mTiles;
				
				// ===========================================================
				// Constructor
				// ===========================================================
				
				/*
				 * TMap constructor.
				 * 
				 * @thread_safety - not thread-safe.
				 * @param pRows - number of Rows, value copied.
				 * @param pCols - number of Cols, value copied.
				 * @throws - can throw bad_alloc.
				*/
				explicit TMap( const std::uint16_t & pRows, const std::uint16_t & pCols )
					: mCols( pCols ),
					mRows( pRows ),
					mTiles( nullptr )
				{
					
					// Print Debug-message to the console
					std::cout << "TMap::constructor" << std::endl;
					
					// Allocate Rows
					mTiles = new Tile* * [mRows];
					
					// Allocate Cols
					for( std::uint16_t rowIndex_ = 0; rowIndex_ < mRows; rowIndex_++ )
					{
						
						// Create Col
						mTiles[rowIndex_] = new Tile*[mCols];
						
						// Create Tiles
						for( std::uint16_t colIndex_ = 0; colIndex_ < mCols; colIndex_++ )
						{
							
							// Create Tile
							mTiles[rowIndex_][colIndex_] = new Tile( rowIndex_, colIndex_ );
							
						}
						
					}
					
				}
				
				// ===========================================================
				// Destructor
				// ===========================================================
				
				/*
				 * TMap destructor.
				 * 
				 * @thread_safety - not thread-safe.
				 * @throws - no exceptions.
				*/
				~TMap( )
				{
					
					// Print Debug-message to the console
					std::cout << "TMap::destructor" << std::endl;
					
					// Rows
					for( std::uint16_t rowIndex_ = 0; rowIndex_ < mRows; rowIndex_++ )
					{
						
						// Delete Tiles
						for( std::uint16_t colIndex_ = 0; colIndex_ < mCols; colIndex_++ )
						{
							
							// Delete Tile
							delete mTiles[rowIndex_][colIndex_];
							
						}
						
						// Delete Cols
						delete[] mTiles[rowIndex_];
						
					}
					
					// Delete Rows
					delete[] mTiles;
					
				}
				
				// -------------------------------------------------------- \\

			private:

				// -------------------------------------------------------- \\

				// ===========================================================
				// Deleted
				// ===========================================================

				TMap( const TMap & ) = delete;
				TMap & operator=( const TMap & ) = delete;
				TMap( TMap && ) = delete;
				TMap & operator=( TMap && ) = delete;

				// -------------------------------------------------------- \\
				
			};

			// -------------------------------------------------------- \\

		}// path2d

	}// org

}// c0de4un

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )