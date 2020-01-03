/**
* Copyright © 2019 Denis Z. (code4un@yandex.ru) All rights reserved.
* Authors: Denis Z. (code4un@yandex.ru)
* All rights reserved.
* License: see LICENSE.txt
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
**/

#ifndef C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX
#define C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// PathFinder Config
#ifndef C0DE4UN_PATHFINDER_2D_HPP
#include "../cfg/pathfinder2d.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// IMap2D
// ===========================================================

/**
 * 2D Map Interface.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
class IMap2D
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONFIGS
    // ===========================================================

    // -----------------------------------------------------------

public:

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTRUCTORS & DESTRUCTOR
    // ===========================================================

    /**
     * IMap2D destructor.
     * 
     * @throws - can throw exception.
    **/
    virtual ~IMap2D();

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Creates new 2D Map.
     * 
     * @thread_safety - not thread-safe.
     * @param pRows - Rows (Height).
     * @param pCols - Cols (Width).
     * @returns - 2D Map.
     * @throws - can throw exception.
    **/
    static IMap2D* CreateNew( const tint32_t pRows, const tint32_t pCols );

    /**
     * Search 2D Path using stack-container.
     * 
     * @thread_safety - not thread-safe.
     * @param inParams - Search Params.
     * @returns - Path, or null if none found.
     * @throws - can throw exception.
    **/
    virtual Path2D* FindPath_Stack( PathSearchParams& inParams ) = 0;

    /**
     * Sets Tile at specific coords.
     * 
     * @thread_safety - not thread-safe.
     * @param pRow - Row (Y).
     * @param pCol - Col (X).
     * @param pState - Tile-State.
     * @throws - can throw exception.
    **/
    virtual void SetTileAt( const tint32_t pRow, const tint32_t pCol, const ETileState pState ) = 0;

    /**
     * Returns specific 2D Tile.
     * 
     * @thread_safety - not thread-safe.
     * @param pRow - Row index (Y).
     * @param pCol - Col index (X).
     * @return - Tile or null.
     * @throws - can throw exception.
    **/
    virtual const Tile2D* GetTileAt( const tint32_t pRow, const tint32_t pCol ) const = 0;

    /**
     * Returns Rows & Cols num.
     * 
     * @thread_safety - not thread-safe.
     * @param outRows - Rows (Height) output.
     * @param outCols - Cols (Width) output.
     * @throws - can throw exception.
    **/
    virtual void GetMapSize( tint32_t& outRows, tint32_t& outCols ) const = 0;

    /**
     * Release 2D Path & reset Tiles from it.
     * 
     * @thread_safety - not thread-safe.
     * @param inPath - Path to release.
     * @throws - can throw exception.
    **/
    virtual void ReleasePath( Path2D* const inPath ) = 0;

    // -----------------------------------------------------------

}; /// IMap2D
#define C0DE4UN_PATH_FINDER_2D_I_MAP_2D_DECL

// -----------------------------------------------------------

#endif // !C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX