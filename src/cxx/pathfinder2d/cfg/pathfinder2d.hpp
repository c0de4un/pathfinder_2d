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

#ifndef C0DE4UN_PATHFINDER_2D_HPP
#define C0DE4UN_PATHFINDER_2D_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include C++ stack
#include <stack>

// Include C++ bitset.
#include <bitset>

// Include C++ vector
#include <vector>

// C++ assert
#ifdef DEBUG // DEBUG
#include <cassert>
#endif // DEBUG

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-declare Map2D, Tile2D, Path2D
#ifndef C0DE4UN_PATHFINDER_2D_MAP_DECL
#define C0DE4UN_PATHFINDER_2D_MAP_DECL
class IMap2D;
class Map2D;
class IMap2DEventsHandler;
#endif // !C0DE4UN_PATHFINDER_2D_MAP_DECL

// ===========================================================
// TYPES
// ===========================================================

typedef unsigned int tint32_t;

/** Diagonal-Search flag bit-mask. **/
static constexpr unsigned char DIAGONAL_SEARCH_FLAG_MASK = 0;

/** Parial-Result flag bit-mask. **/
static constexpr unsigned char PARTIAL_SEARCH_FLAG_MASK = 1;

// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )

/**
 * Tile states enum.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
enum ETileState : unsigned char
{

    // -----------------------------------------------------------

    AVAILABLE = 0,
    PROCESSING = 1,
    PATH_RESERVED = 2,
    OCCUPIED = 3

    // -----------------------------------------------------------

};

/**
 * Path search criteria.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
enum ESearchCriteria : unsigned char
{

    // -----------------------------------------------------------

    SHORTEST,
    LONGEST

    // -----------------------------------------------------------

};

/**
 * Path search params.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
struct PathSearchParams
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTANTS & FIELDS
    // ===========================================================

    /** Start **/
    tint32_t mSrcRow;
    tint32_t mSrcCol;

    /** Finish **/
    tint32_t mDstRow;
    tint32_t mDstCol;

    /** Callbacks Interface **/
    IMap2DEventsHandler* MapListener;

    /** Search-Flags. **/
    std::bitset<2> mSearchFlags;

    /** Search Criteria. **/
    ESearchCriteria mSearchCriteria;

    // -----------------------------------------------------------

}; /// PathSearchParams

/**
 * Tile2D - 2D Tile struct.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
struct Tile2D
{

    // -----------------------------------------------------------

    /** Row **/
    tint32_t mRow;

    /** Col **/
    tint32_t mCol;

    /** Tile State **/
    ETileState mState;

    /** Step Index. **/
    tint32_t mStep;

    // -----------------------------------------------------------

};

/**
 * 2D Path struct.
 * 
 * @since 23.12.2019
 * @version 1.0
 * @authors Denis Z. (code4un@yandex.ru)
**/
struct Path2D
{

    // -----------------------------------------------------------

    /** Tiles **/
    std::vector<Tile2D*> mTiles;

    /** Start-Tile **/
    const Tile2D* const mStart;

    /** Finish-Tile **/
    const Tile2D* const mFinish;

    // -----------------------------------------------------------

}; /// Path2D

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

// -----------------------------------------------------------

#endif C0DE4UN_PATHFINDER_2D_HPP // !C0DE4UN_PATHFINDER_2D_HPP