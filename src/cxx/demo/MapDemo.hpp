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

#ifndef C0DE4UN_PATH_FINDER_2D_MAP_DEMO_HPP
#define C0DE4UN_PATH_FINDER_2D_MAP_DEMO_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// IMap2DEventsHandler
#ifndef C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_HXX
#include "../pathfinder2d/core/IMap2DEventsHandler.hxx"
#endif // !C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_HXX

// C++ String
#include <string>

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// MapDemo
// ===========================================================

/**
 * 2D Map search demo-runner.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
class MapDemo final
{

    // -----------------------------------------------------------
    // -----------------------------------------------------------

private:

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTANTS & FIELDS
    // ===========================================================

    /** Map-File. **/
    const std::string mDataFile;

    /** 2D Map. **/
    IMap2D* mMap2D;

    /** Start Tile. **/
    const Tile2D* mStart;

    /** Finish Tile. **/
    const Tile2D* mFinish;

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Sets symbols (elements, chars, text) output color.
     * 
     * (?) Not all platforms (console-program) supports colorizing console output.
     * 
     * @thread_safety - not thread-safe.
     * @param pTile - Tile to set color for.
     * @throws - can throw exception.
    **/
    inline void SetConsoleColorForTile( const Tile2D* const pTile ) const;

    /**
     * Print Tile to comsole-output.
     * 
     * @thread_safety - not thread-safe.
     * @param pTile - Tile to set print.
     * @throws - can throw exception.
    **/
    inline void PrintTileToConsole( const Tile2D* const pTile ) const;

    /**
     * Prints all map data using colors & special symbols (elements, chars) for
     * tile state.
     * 
     * @thread_safety - not thread-safe.
     * @throws - can throw exception.
    **/
    inline void PrintMap();

    /**
     * Load Map data from file.
     * 
     * (?) Parses Start, Finish and other Tiles values.
     * 
     * @thread_safety - not thread-safe.
     * @throws - can throw exception (io, access-violation, null).
    **/
    void LoadMap();

    // -----------------------------------------------------------

public:

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTANTS & FIELDS
    // ===========================================================

    // ===========================================================
    // CONSTRUCTORS & DESTRUCTOR
    // ===========================================================

    /**
     * MapDemo constructor.
     * 
     * @param pFile - Map data file.
     * @throws - can throw exception (out of memory).
    **/
    explicit MapDemo( const std::string& pFile );

    /**
     * MapDemo destructor.
     * 
     * @throws - can throw exception.
    **/
    virtual ~MapDemo() final;

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Run Demo.
     * 
     * @thread_safety - not thread-safe, not required.
     * @throws - can throw exception.
    **/
    void Run();

    // -----------------------------------------------------------

}; /// MapDemo

// -----------------------------------------------------------

#endif // !C0DE4UN_PATH_FINDER_2D_MAP_DEMO_HPP