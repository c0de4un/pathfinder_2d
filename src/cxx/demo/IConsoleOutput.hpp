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

#ifndef C0DE4UN_PATHFINDER_2D_I_CONSOLE_OUTPUT_HXX
#define C0DE4UN_PATHFINDER_2D_I_CONSOLE_OUTPUT_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDE
// ===========================================================

// Include C++ string
#include <string>

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// EConsoleColor
// ===========================================================

/**
 * Console-Supported colors enum.
 * 
 * @version 0.1
 * @since 23.12.2019
 * @authors Denis Z. (code4un@yandex.ru)
**/
enum EConsoleColor : unsigned char
{

    // -----------------------------------------------------------

    WHITE,
    DEFAULT = WHITE,
    BLACK,
    BLUE,
    GREEN,
    RED,
    YELLOW,
    PINK

    // -----------------------------------------------------------

};

// ===========================================================
// IConsoleOutput
// ===========================================================

/**
 * IConsoleOutput - interface to use when specific console-features required
 * (background/foreground color, cursor location, encoding).
 * 
 * @version 0.1
 * @since 23.12.2019
 * @authors Denis Z. (code4un@yandex.ru)
**/
class IConsoleOutput
{
    // -----------------------------------------------------------

    // ===========================================================
    // CONFIGS
    // ===========================================================

    // -----------------------------------------------------------

public:

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTRUCTORS & DESTRUCTOR
    // ===========================================================

    /**
     * IConsoleOutput destructor.
     * 
     * @throw - can throw exception.
    **/
    virtual ~IConsoleOutput();

    // ===========================================================
    // METHODS
    // ===========================================================

    /**
     * Sets Text-Color for a Console-Output.
     * 
     * @thread_safety - not thread-safe.
     * @param InColor - Color for Console-Text.
     * @throws - can throw exception.
    **/
    static void SetTextColor( const EConsoleColor InColor );

    /**
     * Prints string to console-output as line.
     * 
     * @thread_safety - not thread-safe.
     * @param pText - Text string to print.
     * @throws - can throw exception.
    **/
    static void PrintLine( const std::string& pText );

    /**
     * Prints chars to console-output.
     * 
     * @thread_safety - not thread-safe.
     * @param pChar - c-string to print.
     * @throws - can throw exception.
    **/
    static void PrintChar( const char* const pChar );

    /**
     * Prints numeric-value to console-output.
     * 
     * @thread_safety - not thread-safe.
     * @param pNum - numeric-value to print.
     * @throws - can throw exception.
    **/
    static void PrintNum( const unsigned int pNum );

    /**
     * Prints new line.
     * 
     * @thread_safety - not thread-safe.
     * @param pNum - numeric-value to print.
     * @throws - can throw exception.
    **/
    static void NewLine();

    // -----------------------------------------------------------

};

// -----------------------------------------------------------

#endif // !C0DE4UN_PATHFINDER_2D_I_CONSOLE_OUTPUT_HXX