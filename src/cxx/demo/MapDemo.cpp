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
#ifndef C0DE4UN_PATH_FINDER_2D_MAP_DEMO_HPP
#include "MapDemo.hpp"
#endif // !C0DE4UN_PATH_FINDER_2D_MAP_DEMO_HPP

// Include IMap2D
#ifndef C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX
#include "../pathfinder2d/core/IMap2D.hxx"
#endif // !C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX

// Include IConsoleOutput
#ifndef C0DE4UN_PATHFINDER_2D_I_CONSOLE_OUTPUT_HXX
#include "IConsoleOutput.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_I_CONSOLE_OUTPUT_HXX

// Include MapFactory
#ifndef C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_HXX
#include "IMapFactory.hxx"
#endif // !C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_HXX

// ===========================================================
// MapDemo
// ===========================================================

MapDemo::MapDemo( const std::string& pFile )
	: mDataFile( pFile ),
	mMap2D( nullptr ),
	mStart( nullptr ),
	mFinish( nullptr )
{
}

MapDemo::~MapDemo()
{
	if (mMap2D)
	{
		delete mMap2D;
	}
}

void MapDemo::SetConsoleColorForTile( const Tile2D* const pTile ) const
{
#ifdef DEBUG // DEBUG
	assert( pTile && "MapDemo::SetConsoleColorForTile - null argument !" );
#else
	if ( !pTile )
	{
		return;
	}
#endif // DEBUG

	// Handle Tile-State
	switch( pTile->mState )
	{
	case ETileState::OCCUPIED:
	{
		IConsoleOutput::SetTextColor( EConsoleColor::RED );
	}
		break;
	case ETileState::PROCESSING:
	{
		IConsoleOutput::SetTextColor( EConsoleColor::PINK );
	}
		break;
	case ETileState::PATH_RESERVED:
	{
		IConsoleOutput::SetTextColor( EConsoleColor::GREEN );
	}
		break;
	default:
	{
		IConsoleOutput::SetTextColor( EConsoleColor::DEFAULT );
	}
		break;
	}

} /// MapDemo::SetConsoleColorForTile

void MapDemo::PrintTileToConsole( const Tile2D* const pTile ) const
{
	if ( mStart == pTile )
	{
		IConsoleOutput::PrintChar( " A" );
	}
	else if ( mFinish == pTile )
	{
		IConsoleOutput::PrintChar( " B" );
	}
	else
	{
		switch( pTile->mState )
		{
		case ETileState::OCCUPIED:
		{
			IConsoleOutput::PrintChar( " X" );
		}
			break;
		case ETileState::PATH_RESERVED:
		case ETileState::AVAILABLE:
		{
			const tint32_t stepNum = pTile->mStep;

			if ( stepNum > 98 )
			{
				IConsoleOutput::PrintNum( 99 );
			}
			else if ( stepNum > 9 )
			{
				IConsoleOutput::PrintNum( stepNum );
			}
			else
			{
				std::string strVal( "0" );
				strVal += std::to_string( stepNum );
				IConsoleOutput::PrintChar( strVal.c_str() );
			}
		}
			break;
		default:
		{
			IConsoleOutput::PrintChar( " ?" );
		}
			break;
		}
	}

} /// MapDemo::PrintTileToConsole

void MapDemo::PrintMap()
{
#ifdef DEBUG // DEBUG
	assert( mMap2D && mStart && mFinish && "MapDemo::PrintMap - invalid data." );
#else // !DEBUG
	if ( !mMap2D || !mStart || !mFinish )
	{
		return;
	}
#endif // DEBUG

	tint32_t outRows, outCols = 0;
	mMap2D->GetMapSize(outRows, outCols);

	// Tile
	const Tile2D* tile2D = nullptr;

	// Rows
	for( tint32_t row = 0; row < outRows; row++ )
	{
		// Cols
		for( tint32_t col = 0; col < outCols; col++ )
		{
			tile2D = mMap2D->GetTileAt( row, col );
			SetConsoleColorForTile( tile2D );
			PrintTileToConsole( tile2D );
		} /// Cols

		// New Line
		IConsoleOutput::NewLine();

	} /// Rows

} /// MapDemo::PrintMap

void MapDemo::Run()
{ // @TODO MapDemo::Run
	// Print Console-Output Info-Message
	IConsoleOutput::SetTextColor( EConsoleColor::BLUE );
	IConsoleOutput::PrintLine( "MapDemo - data from file:" );

	// Load Map
	MapLoadingResponse mapLoadParams;
	IMapFactory::LoadMap2DFromFile( mDataFile, mapLoadParams );

#ifdef DEBUG // DEBUG
	assert( mapLoadParams.mMap && "MapDemo::Run - invalid map data !" );
#else // !DEBUG
	if ( !mapLoadParams.mMap )
	{
		return;
	}
#endif // DEBUG

	mMap2D = mapLoadParams.mMap;
	mStart = mapLoadParams.mStart;
	mFinish = mapLoadParams.mFinish;

	// Print Map State
	IConsoleOutput::SetTextColor( EConsoleColor::DEFAULT );
	PrintMap();

	// Print Console-Output Info-Message
	IConsoleOutput::SetTextColor( EConsoleColor::BLUE );
	IConsoleOutput::PrintLine( "MapDemo - Search path:" );

	// Search Path
	PathSearchParams pathParams;
	pathParams.MapListener = nullptr;
	pathParams.mSearchFlags = std::bitset<2>( false );
	pathParams.mSearchFlags[DIAGONAL_SEARCH_FLAG_MASK] = false;
	pathParams.mSearchFlags[PARTIAL_SEARCH_FLAG_MASK] = false;
	pathParams.mSearchCriteria = ESearchCriteria::SHORTEST;
	pathParams.mSrcRow = mStart->mRow;
	pathParams.mSrcCol = mStart->mCol;
	pathParams.mDstRow = mFinish->mRow;
	pathParams.mDstCol = mFinish->mCol;
	Path2D* const path2D = mMap2D->FindPath_Stack( pathParams );

	// Path not found.
	if ( !path2D )
	{
		IConsoleOutput::SetTextColor( EConsoleColor::RED );
		IConsoleOutput::PrintLine( "Path not found !" );
	}
	else
	{
		// Print Map State
		IConsoleOutput::SetTextColor( EConsoleColor::DEFAULT );
		PrintMap();
	}

} /// MapDemo::Run

// -----------------------------------------------------------