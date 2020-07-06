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
 * @file        LinkEditData.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/LinkEditData.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class LinkEditData::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _dataOffset;
                uint32_t _dataSize;
        };

        LinkEditData::LinkEditData( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        LinkEditData::LinkEditData( const LinkEditData & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        LinkEditData::LinkEditData( LinkEditData && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        LinkEditData::~LinkEditData()
        {}

        LinkEditData & LinkEditData::operator =( LinkEditData o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        Info LinkEditData::getInfo() const
        {
            Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Data offset", ToString::Hex( this->dataOffset() ) } );
            i.addChild( { "Data size",   ToString::Hex( this->dataSize() ) } );
            
            return i;
        }
        
        uint32_t LinkEditData::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t LinkEditData::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t LinkEditData::dataOffset() const
        {
            return this->impl->_dataOffset;
        }
        
        uint32_t LinkEditData::dataSize() const
        {
            return this->impl->_dataSize;
        }
        
        void swap( LinkEditData & o1, LinkEditData & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        LinkEditData::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            _command(    command ),
            _size(       size ),
            _dataOffset( stream.readUInt32() ),
            _dataSize(   stream.readUInt32() )
        {
            ( void )kind;
        }
        
        LinkEditData::IMPL::IMPL( const IMPL & o ):
            _command( o._command ),
            _size(    o._size ),
            _dataOffset( o._dataOffset ),
            _dataSize(   o._dataSize )
        {}

        LinkEditData::IMPL::~IMPL()
        {}
    }
}
