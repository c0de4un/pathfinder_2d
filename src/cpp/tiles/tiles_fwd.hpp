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

// -------------------------------------------------------- \\

namespace c0de4un
{

    namespace org
    {

        namespace path2d
        {
            
            // -------------------------------------------------------- \\

#ifndef C0DE4UN_ORG_PATH_2D_TILE_DECL
#define C0DE4UN_ORG_PATH_2D_TILE_DECL
            struct Tile;
#endif // !C0DE4UN_ORG_PATH_2D_TILE_DECL

#ifndef C0DE4UN_ORG_PATH_2D_TILES_MANAGER_DECL
#define C0DE4UN_ORG_PATH_2D_TILES_MANAGER_DECL
            class TilesManager;
#endif // !C0DE4UN_ORG_PATH_2D_TILES_MANAGER_DECL

#ifndef C0DE4UN_ORG_PATH_2D_ROUTE_DECL
#define C0DE4UN_ORG_PATH_2D_ROUTE_DECL
            struct Route;
#endif // !C0DE4UN_ORG_PATH_2D_ROUTE_DECL

#ifndef C0DE4UN_ORG_PATH_2D_TMAP_DECL
#define C0DE4UN_ORG_PATH_2D_TMAP_DECL
            struct TMap;
#endif // !C0DE4UN_ORG_PATH_2D_TMAP_DECL

            // -------------------------------------------------------- \\

        }// path2d

    }// org

}// c0de4un

// -------------------------------------------------------- \\

/* Type-alias for c0de4un::org::path2d::Tile */
using path2D_Tile = c0de4un::org::path2d::Tile;

/* Type-alias for c0de4un::org::path2d::TilesManager */
using path2D_TilesManager = c0de4un::org::path2d::TilesManager;

/* Type-alias for c0de4un::org::path2d::Route */
using path2D_Route = c0de4un::org::path2d::Route;

/* Type-alias for c0de4un::org::path2d::TMap */
using path2D_TMap = c0de4un::org::path2d::TMap;

// -------------------------------------------------------- \\