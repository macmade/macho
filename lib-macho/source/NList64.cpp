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
 * @file        NList64.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/NList64.hpp>

namespace MachO
{
    class NList64::IMPL
    {
        public:
            
            IMPL( void );
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL( void );
    };

    NList64::NList64( void ):
        impl( std::make_unique< IMPL >() )
    {}

    NList64::NList64( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}

    NList64::NList64( const NList64 & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    NList64::NList64( NList64 && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    NList64::~NList64( void )
    {}

    NList64 & NList64::operator =( NList64 o )
    {
        swap( *( this ), o );
        
        return *( this );
    }

    void swap( NList64 & o1, NList64 & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }

    NList64::IMPL::IMPL( void )
    {}

    NList64::IMPL::IMPL( BinaryStream & stream )
    {
        ( void )stream;
    }

    NList64::IMPL::IMPL( const IMPL & o )
    {
        ( void )o;
    }

    NList64::IMPL::~IMPL( void )
    {}
}
