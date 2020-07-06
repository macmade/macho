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
 * @file        PreboundDylib.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/PreboundDylib.hpp>
#include <MachO/Casts.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class PreboundDylib::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
        };

        PreboundDylib::PreboundDylib( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        PreboundDylib::PreboundDylib( const PreboundDylib & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        PreboundDylib::PreboundDylib( PreboundDylib && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        PreboundDylib::~PreboundDylib()
        {}

        PreboundDylib & PreboundDylib::operator =( PreboundDylib o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        uint32_t PreboundDylib::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t PreboundDylib::size() const
        {
            return this->impl->_size;
        }
        
        void swap( PreboundDylib & o1, PreboundDylib & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        PreboundDylib::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            _command( command ),
            _size(    size )
        {
            ( void )kind;
            ( void )stream;
        }
        
        PreboundDylib::IMPL::IMPL( const IMPL & o ):
            _command( o._command ),
            _size(    o._size )
        {}

        PreboundDylib::IMPL::~IMPL()
        {}
    }
}
