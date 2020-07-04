/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2020 Jean-David Gadina - www.xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @header      ToString.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_TO_STRING_HPP
#define MACHO_TO_STRING_HPP

#include <type_traits>
#include <ios>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

namespace MachO
{
    namespace ToString
    {
        std::string Size( uint64_t size );
        std::string Filename( const std::string & path );
        
        template
        <
            typename _T_,
            typename std::enable_if
            <
                   std::is_integral< _T_ >::value
                && std::is_unsigned< _T_ >::value
            >
            ::type * = nullptr
        >
        std::string Hex( _T_ value )
        {
            std::stringstream ss;
            
            ss << "0x"
               << std::setfill( '0' )
               << std::setw( sizeof( _T_ ) * 2 )
               << std::hex
               << std::uppercase
               << value;
            
            return ss.str();
        }
    }
}

#endif /* MACHO_TO_STRING_HPP */
