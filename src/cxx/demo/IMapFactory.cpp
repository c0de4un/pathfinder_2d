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
#ifndef C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_HXX
#include "IMapFactory.hxx"
#endif // !C0DE4UN_PATH_FINDER_2D_I_MAP_FACTORY_HXX

// Include C++ iostream
#include <iostream>

// Include C++ fstream
#include <fstream>

// Include C++ string
#include <string>

// Include Map2D
#ifndef C0DE4UN_PATHFINDER_2D_MAP_HPP
#include "../pathfinder2d/core/Map2D.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_MAP_HPP

// ===========================================================
// IMapFactory
// ===========================================================

void IMapFactory::LoadMap2DFromFile( const std::string& pFile, MapLoadingResponse& pOutput )
{
	// Map2D
	Map2D* resultMap = nullptr;

		// Create input-stream to a File & open it
		std::ifstream inputStream_( pFile, std::ifstream::in );

		// Check input stream state
		if ( !inputStream_.good( ) )
		{	
			// Print message to a console
			std::cout << "IMapFactory::LoadMap2DFromFile - failed to open file#" << pFile << std::endl;
			
			// Cancel
			return;
		}

		// Buffer to store readed line
		char charsBuffer_[8192]; // 8 Kb

		// Read Cols
		inputStream_.getline( charsBuffer_, 8192 );

		// Cast chars to std::string
		std::string line_ = charsBuffer_;

		// Value in string
		std::string valStr_ = line_.substr( line_.find_last_of( '=' ) + 1 );

		// Cast string-value to integer
		const tint32_t cols_ = (tint32_t)std::stoi( valStr_ );

		// Read Rows
		inputStream_.getline( charsBuffer_, 8192 );

		// Cast chars to string
		line_ = charsBuffer_; // constructor

		// Value in string
		valStr_ = line_.substr( line_.find_last_of( '=' ) + 1 );

		// Cast string-value to integer
		const tint32_t rows_ = (tint32_t)std::stoi( valStr_ );

		// Create 2D Map
		resultMap = new Map2D( rows_, cols_ );

		// Tile State
		uint8_t tileState = 0;

		// String to store Tile state
		std::string tileStateName( "" );

		// Rows
		for( tint32_t row = 0; row < rows_; row++ )
		{ // Inverted, Rows first, Cols after, otherwise its fills by Y (Height), then by X (Width).
			// Read line
			inputStream_.getline( charsBuffer_, 8192 );

			// Cast chars to string
			line_ = charsBuffer_; // constructor

			// Check Cols Width
			if ( line_.size( ) < cols_ )
			{
				throw std::exception( "bad tile map format ! Invalid row size." );
			}

			// Tile
			Tile2D* tile2D = nullptr;

			// Cols
			for( tint32_t col = 0; col < cols_; col++ )
			{
				// Cast Tile State Name from char to string
				tileStateName = line_[col];

				// Handle Tile
				if ( tileStateName == "A" || tileStateName == "S" )
				{ // Start
					resultMap->SetTileAt( row, col, ETileState::AVAILABLE );
					pOutput.mStart = resultMap->GetTileAt(row, col);
				}
				else if ( tileStateName == "B" || tileStateName == "F" )
				{ // Finish
					resultMap->SetTileAt( row, col, ETileState::AVAILABLE );
					pOutput.mFinish = resultMap->GetTileAt(row, col);
				}
				else if ( tileStateName == "X" )
				{ // Reserver
					resultMap->SetTileAt( row, col, ETileState::OCCUPIED );
				}
				else
				{ // Empty
					resultMap->SetTileAt( row, col, ETileState::AVAILABLE );
				}
			} /// Rows
		} /// Cols

	// Return result.
	pOutput.mMap = resultMap;
} /// IMapFactory::LoadMap2DFromFile

// -----------------------------------------------------------