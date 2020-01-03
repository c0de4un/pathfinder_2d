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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef C0DE4UN_PATHFINDER_2D_MAP_HPP
#include "Map2D.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_MAP_HPP

// IMap2DEventsHandler
#ifndef C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_HXX
#include "IMap2DEventsHandler.hxx"
#endif // !C0DE4UN_PATHFINDER_2D_I_MAP_2D_EVENTS_HANDLER_HXX

// ===========================================================
// PathSearchParams
// ===========================================================

//PathSearchParams::PathSearchParams( const PathSearchParams& pOther )
//	: mSrcRow( pOther.mSrcRow ),
//	mSrcCol( pOther.mSrcCol ),
//	mDstRow( pOther.mDstRow ),
//	mDstCol( pOther.mDstCol ),
//	MapListener( pOther.MapListener ),
//	mSearchFlags( pOther.mSearchFlags ),
//	mSearchCriteria( pOther.mSearchCriteria )
//{
//}

// ===========================================================
// Map2D
// ===========================================================

Map2D::Map2D(const tint32_t pWidth, const tint32_t pHeight)
	: mData( nullptr ),
	mParams{ 0, 0, 0, 0, nullptr, std::bitset<2>( false ), ESearchCriteria::SHORTEST },
	mRows(pHeight),
	mCols(pWidth)
{
	AllocateTiles();
}

Map2D::~Map2D()
{
	ReleaseTiles();
}

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
Path2D* Map2D::FindPath_Stack( PathSearchParams &inParams )
{

	// Apply Search params.
	// mParams.mSrcRow = inParams.mSrcRow;
	// mParams.mSrcCol = inParams.mSrcCol;
	// mParams.mDstRow = inParams.mDstRow;
	// mParams.mDstCol = inParams.mDstCol;
	// mParams.MapListener = inParams.MapListener;
	// mParams.mSearchFlags = inParams.mSearchFlags;
	// mParams.mSearchCriteria = inParams.mSearchCriteria;

#ifdef DEBUG // DEBUG
 	assert(mParams.mSrcRow >= 0 && mParams.mSrcRow < mRows && mParams.mSrcCol >= 0 && mParams.mSrcCol < mCols && "Map2D::FindPath - invalid start.");
 	assert(mParams.mDstRow >= 0 && mParams.mDstRow < mRows && mParams.mDstCol >= 0 && mParams.mDstCol < mCols && "Map2D::FindPath - invalid finish.");
#else // DEBUG
	if ( mParams.mSrcRow < 0 || mParams.mSrcRow > mRows
		|| mParams.mDstRow < 0 || mParams.mDstRow > mRows )
	{
		return nullptr;
	}
#endif // DEBUG

 	// Search-Query
 	mParams = inParams; // Copy

 	// Tiles cache.
 	std::vector<Tile2D*> tilesCache;
	tilesCache.reserve( ( mRows * mCols ) / 2 );

 	// Search result.
 	Path2D* resultPath = FindPath( mParams.mSrcRow, mParams.mSrcCol, mParams.mDstRow, mParams.mDstCol, tilesCache );

 	// Reset not used Tiles.
 	ResetTiles( tilesCache );

 	return resultPath;
}

/**
 * Sets Tile at specific coords.
 *
 * @thread_safety - not thread-safe.
 * @param pRow - Row (Y).
 * @param pCol - Col (X).
 * @param pState - Tile-State.
 * @throws - can throw exception.
 **/
void Map2D::SetTileAt(const tint32_t pRow, const tint32_t pCol, const ETileState pState)
{
#ifdef DEBUG // DEBUG
	assert( pRow >= 0 && pRow < mRows && "Map2D::SetTileAt - invalid Row value." );
	assert( pCol >= 0 && pCol < mCols && "Map2D::SetTileAt - invalid Col value." );
#else
	if ( pRow < 0 || pRow > mRows
		|| pCol < 0 || pCol > mCols )
	{
		return;
	}
#endif // DEBUG

	Tile2D* const tile2D = mData[pCol][pRow];
	tile2D->mState = pState;
}

/**
 * Returns Rows & Cols num.
 *
 * @thread_safety - not thread-safe.
 * @param outRows - Rows (Height) output.
 * @param outCols - Cols (Width) output.
 * @throws - can throw exception.
 **/
void Map2D::GetMapSize( tint32_t &outRows, tint32_t& outCols ) const
{
	outRows = mRows;
	outCols = mCols;
}

/**
 * Release 2D Path & reset Tiles from it.
 *
 * @thread_safety - not thread-safe.
 * @param inPath - Path to release.
 * @throws - can throw exception.
 **/
void Map2D::ReleasePath( Path2D *const inPath )
{
#ifdef DEBUG // DEBUG
	assert( inPath && "Map2D::ReleasePath - Path is null !" );
#else
	if ( !inPath )
	{
		return;
	}
#endif // DEBUG

	DeletePath( inPath );
}

const Tile2D* Map2D::GetTileAt( const tint32_t pRow, const tint32_t pCol ) const
{
#ifdef DEBUG // DEBUG
	assert( pRow >= 0 && pRow < mRows && "Map2D::GetTileAt - invalid Row value." );
	assert( pCol >= 0 && pCol < mCols && "Map2D::GetTileAt - invalid Col value." );
#else
	if ( pRow < 0 || pRow > mRows
		|| pCol < 0 || pCol > mCols )
	{
		return nullptr;
	}
#endif // DEBUG

	return mData[pCol][pRow];
}

// ===========================================================
// METHODS
// ===========================================================

// Path2D* Map2D::FindPath(PathSearchParams& searchParams, const tint32_t srcRow, const tint32_t srcCol, const tint32_t dstRow, const tint32_t dstCol )
// {
// #ifdef DEBUG // DEBUG
// 	assert(srcRow >= 0 && srcRow < mRows && srcCol >= 0 && srcCol < mCols && "Map2D::FindPath - invalid start.");
// 	assert(dstRow >= 0 && dstRow < mRows && dstCol >= 0 && dstCol < mCols && "Map2D::FindPath - invalid finish.");
// #endif // DEBUG

// 	// Search-Query
// 	mParams = searchParams; // Copy

// 	// Tiles cache.
// 	std::vector<Tile2D*> tilesCache( ( mRows * mCols ) / 2 );

// 	// Search result.
// 	Path2D* resultPath = FindPath( srcRow, srcCol, dstRow, dstCol, tilesCache );

// 	// Reset not used Tiles.
// 	ResetTiles( tilesCache );

// 	return resultPath;
// } /// Map2D::FindPath

void Map2D::ResetTiles( std::vector<Tile2D*>& pTiles )
{
	for( Tile2D* tile2D : pTiles )
	{
		if ( tile2D->mState == ETileState::PROCESSING )
		{
			ResetTile( tile2D );
		}

	}
} /// Map2D::ResetTiles

void Map2D::AllocateTiles()
{
	mData = new Tile2D* * [mCols];

	// Rows
	for(tint32_t col = 0; col < mCols; col++)
	{
		mData[col] = new Tile2D*[mRows];

		// Tiles
		for(tint32_t row = 0; row < mRows; row++)
		{
			mData[col][row] = new Tile2D{ row, col, ETileState::AVAILABLE, 0 };
		} // Tiles
	} // Rows
} /// Map2D::AllocateTiles

void Map2D::ReleaseTiles()
{
	// Cols
	for(tint32_t col = 0; col < mCols; col++)
	{
		// Rows
		for(tint32_t row = 0; row < mRows; row++)
		{
			delete mData[col][row];
		} // Cols
		delete[] mData[col];
	} // Rows
	delete[] mData;
} /// Map2D::ReleaseTiles

Path2D* Map2D::FindPath(const tint32_t srcRow, const tint32_t srcCol, const tint32_t dstRow, const tint32_t dstCol, std::vector<Tile2D*>& processedTiles)
{
	// Path2D
	Path2D* resultPath = nullptr;

	// Allocate Tiles-Stack
	std::stack<Tile2D*> tilesStack;

	// Get first Tile.
	GetTilesAround( srcRow, srcCol, 1, tilesStack, processedTiles );

	// Tile
	Tile2D* currentTile = nullptr;

	// Search all Tiles.
	while(tilesStack.size() > 0)
	{

		currentTile = tilesStack.top();
		tilesStack.pop(); // @TODO Replace with null & swap.

		// Path Complete ?
		if ( GetAbsDist2D(currentTile->mRow, currentTile->mCol, dstRow, dstCol) < 2 )
		{
			if ( mParams.MapListener && mParams.MapListener->OnDestinationReached(this))
			{
				break;
			}
		}

		// Search Tiles
		GetTilesAround(currentTile->mRow, currentTile->mCol, currentTile->mStep + 1, tilesStack, processedTiles);

	} /// Search all Tiles

	// Build Path
	resultPath = ProcessPath( GetTileAt(srcRow, srcCol), GetTileAt(dstRow, dstCol), processedTiles );

	return resultPath;

} /// Map2D::FindPath

void Map2D::GetTilesAround(const tint32_t srcRow, const tint32_t srcCol, const tint32_t stepIndex, std::stack<Tile2D*>& pStack, std::vector<Tile2D*>& processedTiles)
{
	// Up
	if (srcRow + 1 < mRows)
	{
		ProcessTile(mData[srcCol][srcRow + 1], stepIndex, pStack, processedTiles);
	}

	// Down
	if (srcRow > 0)
	{
		ProcessTile(mData[srcCol][srcRow - 1], stepIndex, pStack, processedTiles);
	}

	// Left
	if (srcCol > 0)
	{
		ProcessTile(mData[srcCol - 1][srcRow], stepIndex, pStack, processedTiles);
	}

	// Right
	if (srcCol + 1 < mCols)
	{
		ProcessTile(mData[srcCol + 1][srcRow], stepIndex, pStack, processedTiles);
	}

	// Diagonal
	if ( mParams.mSearchFlags[DIAGONAL_SEARCH_FLAG_MASK] )
	{
		
		// Up-Left
		if ( srcRow < mRows - 1 && srcCol > 0 )
		{
			ProcessTile(mData[srcCol - 1][srcRow + 1], stepIndex, pStack, processedTiles);
		}

		// Down-Left
		if ( srcRow > 0 && srcCol > 0 )
		{
			ProcessTile(mData[srcCol - 1][srcRow - 1], stepIndex, pStack, processedTiles);
		}

		// Top-Rigth
		if ( srcRow < mRows - 1 && srcCol < mCols - 1 )
		{
			ProcessTile(mData[srcCol + 1][srcRow + 1], stepIndex, pStack, processedTiles);
		}

		// Down-Right
		if ( srcRow > 0 && srcCol < mCols - 1 )
		{
			ProcessTile(mData[srcCol + 1][srcRow - 1], stepIndex, pStack, processedTiles);
		}
	} /// Diagonal
} /// Map2D::GetTilesAround

void Map2D::ProcessTile(Tile2D* const pTile, const tint32_t stepIndex, std::stack<Tile2D*>& pStack, std::vector<Tile2D*>& processedTiles)
{
#ifdef DEBUG // DEBUG
	assert( pTile && "Map2D::ProcessTile - Tile is null !" );
	assert( stepIndex >= 0 && "Map2D::ProcessTile - Tile step-index is invalid !" );
#endif // DEBUG

	if (pTile->mState == ETileState::AVAILABLE)
	{
	   pStack.push(pTile);
	   processedTiles.push_back(pTile);
	   pTile->mState = ETileState::PROCESSING;
	   pTile->mStep = stepIndex;
	}
} /// Map2D::ProcessTile

tint32_t Map2D::GetAbsDist2D(const tint32_t srcRow, const tint32_t srcCol, const tint32_t dstRow, const tint32_t dstCol)
{
	tint32_t distRow = dstRow - srcRow;
	if (distRow < 0)
	{
		distRow *= -1;
	}

	tint32_t distCol = dstCol - srcCol;
	if ( distCol < 0 )
	{
		distCol *= -1;
	}

	return(distRow + distCol);
} /// Map2D::GetDist2D

Path2D* Map2D::ProcessPath( const Tile2D* const pStart, const Tile2D* const pFinish, std::vector<Tile2D*>& processedTiles )
{
	// Allocate Path
	Path2D* resultPath = nullptr;

	// Path Tiles
	std::vector<Tile2D*> pathTiles;
	pathTiles.reserve( processedTiles.size() / 2 );

	// Add Tiles to Path
	GatherTilesBackward( pFinish->mRow, pFinish->mCol, pathTiles );
	const size_t tilesNum = pathTiles.size();

	// Complete Path
	if ( tilesNum > 0 )
	{
		resultPath = new Path2D{ pathTiles, pStart, pFinish };
	}

	return resultPath;
} /// Map2D::ProcessPath

void Map2D::ResetTile(Tile2D* const pTile) noexcept
{
	pTile->mState = ETileState::AVAILABLE;
	pTile->mStep = 0;
}

void Map2D::DeletePath(Path2D* const inPath)
{

#ifdef DEBUG // DEBUG
	assert(inPath && "Map2D::DeletePath - null argument !");
#endif // DEBUG

	// Reset Tiles
	for( Tile2D* tile2D : inPath->mTiles )
	{
		ResetTile(tile2D);
	} /// Reset Tiles

	delete inPath;

} /// Map2D::DeletePath

Tile2D* Map2D::ProcessTileBackward( const tint32_t pRow, const tint32_t pCol, Tile2D* const prevTile )
{
	Tile2D* tile2D = mData[pCol][pRow];

	// Compare Tiles
	if ( tile2D->mState == ETileState::PROCESSING )
	{
		if ( prevTile )
		{
			switch( mParams.mSearchCriteria )
			{
				case ESearchCriteria::SHORTEST:
				{
					if ( tile2D->mStep < prevTile->mStep )
					{
						tile2D->mState = ETileState::PATH_RESERVED;
						prevTile->mState = ETileState::PROCESSING;
					}
					else
					{
						tile2D = nullptr;
					}
				}
			break;
				case ESearchCriteria::LONGEST:
				{
					if ( tile2D->mStep > prevTile->mStep )
					{
						tile2D->mState = ETileState::PATH_RESERVED;
						prevTile->mState = ETileState::PROCESSING;
					}
					else
					{
						tile2D = nullptr;
					}
				}
			break;
			}
		}
		else
		{
			tile2D->mState = ETileState::PATH_RESERVED;
		}
	}
	else
	{
		return nullptr;
	} /// Compare Tiles

	return tile2D;
} /// Map2D::ProcessTileBackward

Tile2D* Map2D::GetTileBackward(const tint32_t pRow, const tint32_t pCol)
{
	// Tile
	Tile2D* resultTile = nullptr;
	Tile2D* tempTile = nullptr;

	// Up
	if ( pRow + 1 < mRows )
	{
		resultTile = ProcessTileBackward(pRow + 1, pCol, nullptr);
	}

	// Down
	if ( pRow > 0 )
	{
		if ( tempTile = ProcessTileBackward(pRow - 1, pCol, resultTile) )
		{
			resultTile = tempTile;
		}
	}

	// Left
	if ( pCol > 0 )
	{
		if ( tempTile = ProcessTileBackward(pRow, pCol - 1, resultTile) )
		{
			resultTile = tempTile;
		}
	}

	// Right
	if ( pCol + 1 < mCols )
	{
		if ( tempTile = ProcessTileBackward(pRow, pCol + 1, resultTile) )
		{
			resultTile = tempTile;
		}
	}

	// Diagonal Search
	if ( mParams.mSearchFlags[DIAGONAL_SEARCH_FLAG_MASK] )
	{
		// Up-Left
		if ( pRow + 1 < mRows && pCol > 0 )
		{
			if ( tempTile = ProcessTileBackward(pRow + 1, pCol - 1, resultTile) )
			{
				resultTile = tempTile;
			}
		}

		// Up-Right
		if ( pRow + 1 < mRows && pCol + 1 < mCols )
		{
			if ( tempTile = ProcessTileBackward(pRow + 1, pCol + 1, resultTile) )
			{
				resultTile = tempTile;
			}
		}

		// Down-Left
		if ( pRow > 0 && pCol > 0 )
		{
			if ( tempTile = ProcessTileBackward(pRow - 1, pCol - 1, resultTile) )
			{
				resultTile = tempTile;
			}
		}

		// Down-Right
		if ( pRow > 0 && pCol + 1 < mCols )
		{
			if ( tempTile = ProcessTileBackward(pRow - 1, pCol + 1, resultTile) )
			{
				resultTile = tempTile;
			}
		}

	} /// Diagonal Search

	return resultTile;
} /// Map2D::GetTileBackward

void Map2D::GatherTilesBackward(const tint32_t dstRow, const tint32_t dstCol, std::vector<Tile2D*>& pOutput)
{
	// Get first Tile.
	Tile2D* nextTile = GetTileBackward( dstRow, dstCol );

	// Add Tiles to the Path.
	while( nextTile )
	{
		pOutput.push_back( nextTile );
		nextTile = GetTileBackward( nextTile->mRow, nextTile->mCol );
	}
} /// Map2D::GatherTilesBackward

// -----------------------------------------------------------