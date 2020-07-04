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
 * @file        ToString.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/ToString.hpp>

namespace MachO
{
    namespace ToString
    {
        std::string Size( uint64_t size )
        {
            if( size < 1000 )
            {
                return std::to_string( size ) + " bytes";
            }
            else
            {
                double            s( static_cast< double >( size ) );
                std::stringstream ss;
                
                ss << std::fixed << std::setprecision( 2 );
                
                if( size < 1000 * 1000 )
                {
                    ss << s / 1000.0;
                    ss << " KB";
                }
                else if( size < 1000 * 1000 * 1000 )
                {
                    ss << ( s / 1000.0 ) / 1000.0;
                    ss << " MB";
                }
                else
                {
                    ss << ( ( s / 1000.0 ) / 1000.0 ) / 1000.0;
                    ss << " GB";
                }
                
                return ss.str();
            }
        }
        
        std::string Filename( const std::string & path )
        {
            size_t pos( path.rfind( '/' ) );
            
            if( pos == std::string::npos )
            {
                return path;
            }
            
            return path.substr( pos + 1 );
        }
        
        std::string UUID( const uint8_t * bytes )
        {
            std::stringstream ss;
            
            for( int i = 0; i < 16; i++ )
            {
                if( i == 4 || i == 6 || i == 8 || i == 10 )
                {
                    ss << "-";
                }
                
                ss << std::hex
                   << std::uppercase
                   << std::setfill( '0' )
                   << std::setw( 0 )
                   << static_cast< int >( bytes[ i ] );
            }
            
            return ss.str();
        }
    }
}
