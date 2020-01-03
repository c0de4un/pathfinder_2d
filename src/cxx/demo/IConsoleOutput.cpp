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
// INCLUDE
// ===========================================================

// HEADER
#include "IConsoleOutput.hpp"

// Include C++ IO
#include <iostream>

// Include C++ string
#include <string>

// Windows Command Line API Support
#if defined(WIN32) || defined(WIN64)
#include <Windows.h>
#endif

// ===========================================================
// IConsoleOutput
// ===========================================================

IConsoleOutput::~IConsoleOutput()
{
}

void IConsoleOutput::SetTextColor(const EConsoleColor InColor)
{
#if defined(WIN32) || defined(WIN64)
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    switch(InColor)
    {
        case EConsoleColor::GREEN:
        {
#if defined(WIN32) || defined(WIN64)
    SetConsoleTextAttribute(hConsoleHandle, 10 | 0);
#endif
        }
    break;
        case EConsoleColor::RED:
        {
#if defined(WIN32) || defined(WIN64)
    SetConsoleTextAttribute(hConsoleHandle, 12 | 0);
#endif
        }
    break;
        case EConsoleColor::YELLOW:
        {
#if defined(WIN32) || defined(WIN64)
    SetConsoleTextAttribute(hConsoleHandle, 14 | 0);
#endif
        }
    break;
        case EConsoleColor::PINK:
        {
#if defined(WIN32) || defined(WIN64)
    SetConsoleTextAttribute(hConsoleHandle, 13 | 0);
#endif
        }
    break;
        case EConsoleColor::BLUE:
        {
#if defined(WIN32) || defined(WIN64)
    SetConsoleTextAttribute(hConsoleHandle, 9 | 0);
#endif
        }
    break;
        default:
#if defined(WIN32) || defined(WIN64)
    SetConsoleTextAttribute(hConsoleHandle, 15 | 0);
#endif
    break;
    }
} /// IConsoleOutput::SetTextColor

void IConsoleOutput::PrintLine( const std::string& pText )
{
    std::cout << pText << std::endl;
} /// IConsoleOutput::PrintLine

void IConsoleOutput::PrintChar( const char* const pChar )
{
    std::cout << pChar;
} /// IConsoleOutput::PrintChar

void IConsoleOutput::PrintNum( const unsigned int pNum )
{
    std::cout << std::to_string( pNum );
} /// IConsoleOutput::PrintNum

void IConsoleOutput::NewLine()
{
    std::cout << std::endl;
} /// IConsoleOutput::NewLine

// -----------------------------------------------------------