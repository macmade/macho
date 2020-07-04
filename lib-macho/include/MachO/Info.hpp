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
 * @header      Info.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_INFO_HPP
#define MACHO_INFO_HPP

#include <algorithm>
#include <string>
#include <variant>
#include <vector>
#include <ostream>

namespace MachO
{
    class Info
    {
        public:
            
            Info( const std::string & label );
            Info( const std::string & label, const std::string & value );
            Info( const std::string & label, const std::vector< Info > & children );
            Info( const Info & o );
            Info( Info && o ) noexcept;
            
            virtual ~Info();
            
            Info & operator  =( Info o );
            Info & operator +=( const Info & child );
            
            void addChild( const Info & child );
            
            void label( const std::string & label );
            void value( const std::string & value );
            void value( const std::vector< Info > & children );
            
            std::string         label()    const;
            std::string         value()    const;
            std::vector< Info > children() const;
            
            std::string toString( size_t level = 0, size_t align = 0 ) const;
            
            friend void swap( Info & o1, Info & o2 );
            
            friend std::ostream & operator <<( std::ostream & os, const Info & o );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_INFO_HPP */
