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

#ifndef C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_HXX
#define C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// PathFinder2D Config
#ifndef C0DE4UN_PATHFINDER_2D_HPP
#include "../cfg/pathfinder2d.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-declare Map2D, Tile2D, Path2D
#ifndef C0DE4UN_PATHFINDER_2D_MAP_DECL
#define C0DE4UN_PATHFINDER_2D_MAP_DECL
class Map2D;
struct Path2D;
struct Tile2D;
#endif // !C0DE4UN_PATHFINDER_2D_MAP_DECL

// ===========================================================
// IMap2DEventsHandler
// ===========================================================

/**
 * Interface to handle Map2D events/callbacks.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
class IMap2DEventsHandler
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONFIGS
    // ===========================================================

    // -----------------------------------------------------------

public:

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS & CONSTANTS
    // ===========================================================

    // ===========================================================
    // CONSTRUCTORS & DESTRUCTOR
    // ===========================================================

    /**
     * IMap2DEventsHandler destructor.
     * 
     * @throw - can throw exception.
    **/
    virtual ~IMap2DEventsHandler() { }

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================



    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Called when next Step Tile found.
     * Allows to cancel search.
     * 
     * @thread_safety - not thread-safe.
     * @param pTile - next Tile.
     * @param pMap - 2D Map.
     * @returns - 'true' to continue search, 'false' to stop.
     * @throws - can throw exception.
    **/
    virtual bool OnNextStep( const Tile2D* const pTile, const Map2D* const pMap ) = 0;

    /**
     * Called when Path found. Allows to stop search or try collecting
     * all available routes.
     * 
     * @thread_safety - not thread-safe.
     * @param inPath - Path.
     * @param pMap - 2D Map.
     * @returns - 'true' to continue searching next available path, 'false' to stop.
     * @throws - can throw exception.
    **/
    virtual bool OnPathFound( const Path2D* const inPath, const Map2D* const pMap ) = 0;

    /**
     * Called when any of Wave tile (node, item) reached destination.
     * Allows to cancel search and use only first Path. Obviously this is not
     * best route, but doesn't requires complete search.
     * 
     * @Greedy-Algorith - allows to early cancel search.
     * 
     * @thread_safety - not thread-safe.
     * @param pMap - Map instance.
     * @returns - 'true' to continue search for all possible routes. 'false' to apply Path based
     * on found tiles (nodes, items).
     * @throws - can throw exception.
    **/
    virtual bool OnDestinationReached(const Map2D* const pMap) = 0;

    // -----------------------------------------------------------

}; // IMap2DEventsHandler
#define C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_DECL

// -----------------------------------------------------------

#endif // !C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_HXX