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
#ifndef C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX
#include "IMap2D.hxx"
#endif // !C0DE4UN_PATH_FINDER_2D_I_MAP_2D_HXX

// Include Map2D
#ifndef C0DE4UN_PATHFINDER_2D_MAP_HPP
#include "Map2D.hpp"
#endif // !C0DE4UN_PATHFINDER_2D_MAP_HPP

// ===========================================================
// IMap2D
// ===========================================================

IMap2D::~IMap2D()
{
}

IMap2D* IMap2D::CreateNew( const tint32_t pRows, const tint32_t pCols )
{
	return new Map2D( pRows, pCols );
}

// -----------------------------------------------------------