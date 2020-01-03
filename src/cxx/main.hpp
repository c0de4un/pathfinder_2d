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

// Windows Command Line API Support
#if defined(WIN32) || defined(WIN64)
#include <Windows.h>
#endif

// C++ IO
#include <iostream>

// C++ String
#include <string>

// C++ locale
#include <locale>

// Include IConsoleOutput
#include "demo/IConsoleOutput.hpp"

// Include MapDemo
#ifndef C0DE4UN_PATH_FINDER_2D_MAP_DEMO_HPP
#include "demo/MapDemo.hpp"
#endif // !C0DE4UN_PATH_FINDER_2D_MAP_DEMO_HPP

// Include Tiles
#ifndef C0DE4UN_PATH_FINDER_2D_MAP_HPP
#include "pathfinder2d/core/Map2D.hpp"
#endif // !C0DE4UN_PATH_FINDER_2D_MAP_HPP

// ===========================================================
// FIELDS & CONSTANTS
// ===========================================================

// ===========================================================
// METHODS
// ===========================================================

// -----------------------------------------------------------