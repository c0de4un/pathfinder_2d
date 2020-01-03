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

#ifndef C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_HXX
#define C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include base-types.
#ifndef C0DE4UN_PATHFINDER_2D_HPP
#include "../pathfinder2d/cfg/pathfinder2d.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// TYPES
// ===========================================================

/**
 * MapLoadingResponse - output structure to store result (response)
 * of Map loading.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
struct MapLoadingResponse
{

	// -----------------------------------------------------------

	/** Start Tile. **/
	const Tile2D* mStart;

	/** Finish Tile. **/
	const Tile2D* mFinish;

	/** 2D Map. **/
	IMap2D* mMap;

	// -----------------------------------------------------------

}; /// MapFactoryOutput

/**
 * IMapFactory - Interface to separate objects initialization object (factory) from
 * user (MapDemo).
 * 
 * (?) Factory template allows to simplify switching of the obects initialziation logic.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
class IMapFactory
{

	// -----------------------------------------------------------

    // ===========================================================
    // CONFIGS
    // ===========================================================

	// -----------------------------------------------------------

private:

	// -----------------------------------------------------------

    // ===========================================================
    // FIELDS & CONSTANTS
    // ===========================================================

	// -----------------------------------------------------------

public:

	// -----------------------------------------------------------

    // ===========================================================
    // METHODS
    // ===========================================================

	/**
	 * Load 2D Map data from file.
	 * 
	 * @thread_safety - not thread-safe.
	 * @param pFile - File.
	 * @param specialTiles - Output for Start & Finish Row & Cols (4 values).
	 * @returns - 2D Map, or null.
	 * @throws - can throw exception.
	**/
	static void LoadMap2DFromFile( const std::string& pFile, MapLoadingResponse& pOutput );

	// -----------------------------------------------------------

}; /// IMapFactory
#define C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_DECL

// -----------------------------------------------------------

#endif // !C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_HXX