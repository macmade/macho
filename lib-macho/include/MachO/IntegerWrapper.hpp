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
 * @header      IntegerWrapper.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_INTEGER_WRAPPER_HPP
#define MACHO_INTEGER_WRAPPER_HPP

#include <type_traits>
#include <cstdint>

namespace MachO
{
    template< typename T >
    class IntegerWrapper
    {
        public:
            
            IntegerWrapper( T value = 0 ):
                _value( value )
            {}
            
            IntegerWrapper( const IntegerWrapper & o ):
                _value( o._value )
            {}
            
            IntegerWrapper( IntegerWrapper && o ) noexcept:
                _value( o._value )
            {}
            
            virtual ~IntegerWrapper()
            {}
            
            IntegerWrapper & operator =( IntegerWrapper o )
            {
                swap( *( this ), o );
                
                return *( this );
            }
            
            IntegerWrapper & operator =( T value )
            {
                this->_value = value;
                
                return *( this );
            }
            
            operator T() const
            {
                return this->_value;
            }
            
            T value() const
            {
                return this->_value;
            }
            
            friend void swap( IntegerWrapper & o1, IntegerWrapper & o2 )
            {
                using std::swap;
                
                swap( o1._value, o2._value );
            }
            
        private:
            
            T _value;
    };
}

#endif /* MACHO_INTEGER_WRAPPER_HPP */
