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
			 * @version 0.1.0
			 * @authors: Z. Denis (code4un@yandex.ru)
			 * @since 10.03.2019
			*/
			class TilesManager final
			{

			private:

				// -------------------------------------------------------- \\

				// ===========================================================
				// Constants
				// ===========================================================

				// ===========================================================
				// Fields
				// ===========================================================
				
				/* Map */
				path2D_TMap * mMap;
				
				// -------------------------------------------------------- \\

			public:

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
				// Methods
				// ===========================================================

				/*
				 * Loads Tile-Map data.
				 * 
				 * @thread_safety - not thread-safe.
				 * @param pFile - source-file.
				 * @throws - can throw exception (file not found || io, bad_alloc)
				*/
				void onLoadMap( const std::string & pFile );

				// -------------------------------------------------------- \\

			}; // TilesManager

			// -------------------------------------------------------- \\

		}// path2d

	}// org

}// c0de4un