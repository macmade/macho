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
 * @file        NList.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/NList.hpp>

namespace MachO
{
    class NList::IMPL
    {
        public:
            
            IMPL( void );
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL( void );
    };

    NList::NList( void ):
        impl( std::make_unique< IMPL >() )
    {}

    NList::NList( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}

    NList::NList( const NList & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    NList::NList( NList && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    NList::~NList( void )
    {}

    NList & NList::operator =( NList o )
    {
        swap( *( this ), o );
        
        return *( this );
    }

    void swap( NList & o1, NList & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }

    NList::IMPL::IMPL( void )
    {}

    NList::IMPL::IMPL( BinaryStream & stream )
    {
        ( void )stream;
    }

    NList::IMPL::IMPL( const IMPL & o )
    {
        ( void )o;
    }

    NList::IMPL::~IMPL( void )
    {}
}
