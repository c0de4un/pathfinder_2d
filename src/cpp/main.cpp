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

// HEADER
#include "main.hpp"

/*
 * Runs testing of 2D path finding with Tiles.
 * 
 * @thread_safety - called from main (system/ui) thread.
 * @throws - can throw exception.
*/
void testPathfinding2D( )
{
	
	// Print Message to the console
	std::cout << "Testing 2D Tiles Path(Route) finding . . ." << std::endl;
	
	// Create TilesManager
	mTilesManager = new path2D_TilesManager( std::string( "../../../assets/tiles_map.txt" ) );
	
	// Get start-Tile
	path2D_Tile *const srcTile( mTilesManager->getStart( ) );
	
	// Get finish-Tile
	path2D_Tile *const dstTile( mTilesManager->getFinish( ) );
	
	// Build Path [2 alternative-Routes]
	path2D_Route *const route_( mTilesManager->getRoute( srcTile, dstTile ) );
	
	// Stop if Route not found
	if ( route_ == nullptr )
	{
		
		// Print message to the Console
		std::cout << "route not found !" << std::endl;
		
		// Print Tiles
		mTilesManager->printTiles( );
		
	}
	else
	{
		
		// Delete Route
		delete route_;
	
	}
	
	// Delete TilesManager
	delete mTilesManager;
	mTilesManager = nullptr;
	
	// Print Message to the console
	std::cout << "2D Tiles Path(Route) finding test complete !" << std::endl;
	
}

/*
 * Main
 * 
 * @thread_Safety - called from main (system/uit) thread.
 * @return - 0 if OK.
 * @throws - no exceptions.
*/
int main( )
{

	// Print to Console
	std::cout << "Hello World !" << std::endl;

	// Run Test
	testPathfinding2D( );

	// Wait for input
	std::cin.get( );

	// Return OK
	return( 0 );
	
}
