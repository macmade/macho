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
 * @file        DysymTab.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/DysymTab.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class DysymTab::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _symbolOffset;
                uint32_t _symbolCount;
                uint32_t _stringOffset;
                uint32_t _stringSize;
        };

        DysymTab::DysymTab( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        DysymTab::DysymTab( const DysymTab & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        DysymTab::DysymTab( DysymTab && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        DysymTab::~DysymTab()
        {}

        DysymTab & DysymTab::operator =( DysymTab o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        Info DysymTab::getInfo() const
        {
            Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Symbol offset", ToString::Hex( this->symbolOffset() ) } );
            i.addChild( { "Symbol size",   ToString::Hex( this->symbolCount() ) } );
            i.addChild( { "String offset", ToString::Hex( this->stringOffset() ) } );
            i.addChild( { "String size",   ToString::Hex( this->stringSize() ) } );
            
            return i;
        }
        
        uint32_t DysymTab::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t DysymTab::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t DysymTab::symbolOffset() const
        {
            return this->impl->_symbolOffset;
        }
        
        uint32_t DysymTab::symbolCount() const
        {
            return this->impl->_symbolCount;
        }
        
        uint32_t DysymTab::stringOffset() const
        {
            return this->impl->_stringOffset;
        }
        
        uint32_t DysymTab::stringSize() const
        {
            return this->impl->_stringSize;
        }
        
        void swap( DysymTab & o1, DysymTab & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        DysymTab::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            _command(      command ),
            _size(         size ),
            _symbolOffset( stream.readUInt32() ),
            _symbolCount(  stream.readUInt32() ),
            _stringOffset( stream.readUInt32() ),
            _stringSize(   stream.readUInt32() )
        {
            ( void )kind;
        }
        
        DysymTab::IMPL::IMPL( const IMPL & o ):
            _command(      o._command ),
            _size(         o._size ),
            _symbolOffset( o._symbolOffset ),
            _symbolCount(  o._symbolCount ),
            _stringOffset( o._stringOffset ),
            _stringSize(   o._stringSize )
        {}

        DysymTab::IMPL::~IMPL()
        {}
    }
}
