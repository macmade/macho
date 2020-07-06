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
 * @file        EntryPoint.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/EntryPoint.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class EntryPoint::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint64_t _offset;
                uint64_t _stackSize;
        };

        EntryPoint::EntryPoint( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        EntryPoint::EntryPoint( const EntryPoint & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        EntryPoint::EntryPoint( EntryPoint && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        EntryPoint::~EntryPoint()
        {}

        EntryPoint & EntryPoint::operator =( EntryPoint o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        Info EntryPoint::getInfo() const
        {
            Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Offset",     ToString::Hex( this->offset() ) } );
            i.addChild( { "Stack size", ToString::Hex( this->stackSize() ) } );
            
            return i;
        }
        
        uint32_t EntryPoint::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t EntryPoint::size() const
        {
            return this->impl->_size;
        }
        
        uint64_t EntryPoint::offset() const
        {
            return this->impl->_offset;
        }
        
        uint64_t EntryPoint::stackSize() const
        {
            return this->impl->_stackSize;
        }
        
        void swap( EntryPoint & o1, EntryPoint & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        EntryPoint::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  ):
            _command(   command ),
            _size(      size ),
            _offset(    stream.readUInt64() ),
            _stackSize( stream.readUInt64() )
        {
            ( void )kind;
        }
        
        EntryPoint::IMPL::IMPL( const IMPL & o ):
            _command(   o._command ),
            _size(      o._size ),
            _offset(    o._offset ),
            _stackSize( o._stackSize )
        {}

        EntryPoint::IMPL::~IMPL()
        {}
    }
}
