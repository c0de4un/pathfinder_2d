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

#ifndef C0DE4UN_PATHFINDER_2D_MAP_HPP
#define C0DE4UN_PATHFINDER_2D_MAP_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// PathFinder2D Config
#ifndef C0DE4UN_PATHFINDER_2D_HPP
#include "../cfg/pathfinder2d.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_HPP

// IMap2D
#ifndef C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX
#include "IMap2D.hxx"
#endif // !C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// IMap2DEventsHandler
#ifndef C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_DECL
#define C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_DECL
class IMap2DEventsHandler;
#endif // !C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_DECL

// ===========================================================
// Types
// ===========================================================

// ===========================================================
// Map2D
// ===========================================================

/**
 * 2D Map.
 * Recursive search not used due to limits on some devices (some Android phones have up to 50 recursive calls limit).
 * 
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
class Map2D : public IMap2D
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONFIGS
    // ===========================================================

    // -----------------------------------------------------------

private:

    // -----------------------------------------------------------

    // ===========================================================
    // CONFIGS
    // ===========================================================

    // ===========================================================
    // FIELDS & CONSTANTS
    // ===========================================================

    /** Tiles data. **/
    Tile2D* ** mData;

    /** Search params. **/
    PathSearchParams mParams;

    /** Rows num. **/
    const tint32_t mRows;

    /** Cols num. **/
    const tint32_t mCols;

    // -----------------------------------------------------------

public:

    // -----------------------------------------------------------

    // ===========================================================
    // CONFIGS
    // ===========================================================

    // ===========================================================
    // CONSTRUCTORS & DESTRUCTOR
    // ===========================================================

    /**
     * Map2D constructor.
     * 
     * @param pWidth - Width of Map in Rows.
     * @param pHeight - Height of Map in Cols.
     * @throws - can throw exceptions.
    **/
    explicit Map2D( const tint32_t pWidth, const tint32_t pHeight );

    /**
     * Map2D destructor.
     * 
     * @throws - can throw exception.
    **/
    ~Map2D();

    // ===========================================================
    // Override: IMap2D
    // ===========================================================

    /**
     * Search 2D Path using stack-container.
     * 
     * @thread_safety - not thread-safe.
     * @param inParams - Search Params.
     * @returns - Path, or null if none found.
     * @throws - can throw exception.
    **/
    virtual Path2D* FindPath_Stack( PathSearchParams& inParams ) override;

    /**
     * Sets Tile at specific coords.
     * 
     * @thread_safety - not thread-safe.
     * @param pRow - Row (Y).
     * @param pCol - Col (X).
     * @param pState - Tile-State.
     * @throws - can throw exception.
    **/
    virtual void SetTileAt( const tint32_t pRow, const tint32_t pCol, const ETileState pState ) override;

    /**
     * Returns Rows & Cols num.
     * 
     * @thread_safety - not thread-safe.
     * @param outRows - Rows (Height) output.
     * @param outCols - Cols (Width) output.
     * @throws - can throw exception.
    **/
    virtual void GetMapSize( tint32_t& outRows, tint32_t& outCols ) const override;

    /**
     * Release 2D Path & reset Tiles from it.
     * 
     * @thread_safety - not thread-safe.
     * @param inPath - Path to release.
     * @throws - can throw exception.
    **/
    virtual void ReleasePath( Path2D* const inPath ) override;

    /**
     * Returns specific 2D Tile.
     * 
     * @thread_safety - not thread-safe.
     * @param pRow - Row index (Y).
     * @param pCol - Col index (X).
     * @return - Tile or null.
     * @throws - can throw exception.
    **/
    virtual const Tile2D* GetTileAt( const tint32_t pRow, const tint32_t pCol ) const override;

    // -----------------------------------------------------------

private:

    // -----------------------------------------------------------

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Searches for any available Path.
     * 
     * @thread_safety - not thread-safe.
     * @param srcRow - Source-Tile Row (Y).
     * @param srcCol - Source-Tile Col (X).
     * @param dstRow - Destination-Tile Row (Y).
     * @param dstCol - Destination-Tile Col (X).
     * @param processedTiles - Tiles to reset after search is complete.
     * @throws - can throw exceptions.
    **/
    inline Path2D* FindPath(const tint32_t srcRow, const tint32_t srcCol, const tint32_t dstRow, const tint32_t dstCol, std::vector<Tile2D*>& processedTiles);

    /**
     * Searches available Tiles around source.
     * 
     * @inline - called for every queue item.
     * @thread_safety - not thread-safe.
     * @param srcRow - Source-Tile Row (Y).
     * @param srcCol - Source-Tile Col (X).
     * @param pStack - Tiles stack.
     * @param processedTiles - Tiles to reset after search is complete.
     * @throws - can throw exceptions.
    **/
    inline void GetTilesAround(const tint32_t srcRow, const tint32_t srcCol, const tint32_t stepIndex, std::stack<Tile2D*>& pStack, std::vector<Tile2D*>& processedTiles);

    /**
     * Process Tile.
     * 
     * @inline - called often, inner-use only.
     * @thread_safety - not thread-safe.
     * @param pTile - Tile.
     * @param stepIndex - Source-Tile Step Index.
     * @param pStack - Tiles stack.
     * @param processedTiles - Processed Tiles list (collection, vector, container).
     * @throws - can throw exception.
    **/
    inline void ProcessTile(Tile2D* const pTile, const tint32_t stepIndex, std::stack<Tile2D*>& pStack, std::vector<Tile2D*>& processedTiles);

    /**
     * Calculates simple 2D-Vector distance.
     * 
     * @inline - called often.
     * @thread_safety - not thread-safe.
     * @param srcRow - Source-Tile Row.
     * @param srcCol - Source-Tile Col.
     * @param dstRow - Destination/Target Row.
     * @param dstCol - Destination/Target Col.
     * @return - 2d vector length.
     * @throws - can throw exception.
    **/
    inline tint32_t GetAbsDist2D(const tint32_t srcRow, const tint32_t srcCol, const tint32_t dstRow, const tint32_t dstCol);

    /**
     * Build Path using collected by the Wave Tiles.
     * 
     * @inline - inner-use only, called every time Path found.
     * @thread_safety - not thread-safe.
     * @param pStart - Start.
     * @param pFinish - Finish.
     * @param waveTile - Tiles collection to pick from.
     * @param pComplete - 'true' if Path is complete (reaches destination).
     * @param processedTiles - Tiles collection for reset after search complete.
     * @returns - Path or null.
     * @throws - can throw exception.
    **/
    inline Path2D* ProcessPath( const Tile2D* const pStart, const Tile2D* const pFinish, std::vector<Tile2D*>& processedTiles );

    /**
     * Deletes Path & resets its Tiles.
     * 
     * @inline - inner-use only, called every time Path deleted.
     * @thread_safety - not thread-safe.
     * @param inPath - Path to delete.
     * @throws - can throw exception.
    **/
    inline void DeletePath(Path2D* const inPath);

    /**
     * Resets Tile data.
     * 
     * @inline - inner-use only, called every time Tiles reset.
     * @thread_safety - not thread-safe.
     * @throws - no exceptions.
    **/
    inline void ResetTile(Tile2D* const pTile) noexcept;

    /**
     * Resets Tiles not used in Path.
     * 
     * (?) Only Tiles with Processing-status are reset.
     * 
     * @inline - inner-use only.
     * @param pTiles - Tiles to reset.
     * @throws - no exceptions.
    **/
    inline void ResetTiles( std::vector<Tile2D*>& pTiles );

    /**
     * Selects Tiles, using sorting-criteria, into
     * Output-container.
     * 
     * (?) Depending on criteria this methods collects Tiles from smallest
     * or largest Step-index.
     * 
     * @inline - inner-use only, called every search for every route.
     * @thread_safety - not thread-safe.
     * @param dstRow - Destination-Tile Row (Y).
     * @param dstCol - Destination-Tile Col (X).
     * @param pOutput - Collection to add selected Tiles.
     * @throws - can throw exception.
    **/
    inline void GatherTilesBackward(const tint32_t dstRow, const tint32_t dstCol, std::vector<Tile2D*>& pOutput);

    /**
     * Search best Tile around.
     * 
     * (?) To compare used enum (shortest or longest).
     * 
     * @inline - inner-use only, called often.
     * @param pRow - Row (Y).
     * @param pCol - Col (X).
     * @returns - Tile.
     * @throws - can throw exception.
    **/
    inline Tile2D* GetTileBackward(const tint32_t pRow, const tint32_t pCol);

    /**
     * 
     * @inline - inner-use only, called often.
     * @param pRow - Row (Y).
     * @param pCol - Col (X).
     * @param prevTile - previous Tile to compare with, can be null if none.
     * If replaced, - reset.
     * @returns - null if previous-Tile is better, Tile if previous Tile should be replaced.
     * @throws - can throw exception.
    **/
    inline Tile2D* ProcessTileBackward(const tint32_t pRow, const tint32_t pCol, Tile2D* const prevTile = nullptr);

    /**
     * Allocate 2D Map data.
     * 
     * @thread_safety - not thread-safe (not required).
     * @throws - can throw exception (out of memory).
    **/
    void AllocateTiles();

    /**
     * Release (de-allocate) 2D Map data.
     * 
     * @thread_safety - not thread-safe (not required).
     * @throws - can throw exception (null-ptr, out-of-bounds).
    **/
    void ReleaseTiles();

    // -----------------------------------------------------------

}; /// Map2D
#define C0DE4UN_PATHFINDER_2D_MAP_DECL

// -----------------------------------------------------------

#endif // !C0DE4UN_PATHFINDER_2D_MAP_HPP