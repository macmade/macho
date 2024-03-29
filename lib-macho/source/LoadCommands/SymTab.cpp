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
 * @file        SymTab.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/SymTab.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class SymTab::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _symbolOffset;
                uint32_t _symbolCount;
                uint32_t _stringOffset;
                uint32_t _stringSize;

                std::vector< std::string >  _strings;
                std::vector< Symbol >       _symbols;
        };

        SymTab::SymTab( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        SymTab::SymTab( const SymTab & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        SymTab::SymTab( SymTab && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        SymTab::~SymTab()
        {}

        SymTab & SymTab::operator =( SymTab o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info SymTab::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Symbol offset", XS::ToString::Hex( this->symbolOffset() ) } );
            i.addChild( { "Symbol size",   XS::ToString::Hex( this->symbolCount() ) } );
            i.addChild( { "String offset", XS::ToString::Hex( this->stringOffset() ) } );
            i.addChild( { "String size",   XS::ToString::Hex( this->stringSize() ) } );
            
            return i;
        }
        
        uint32_t SymTab::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t SymTab::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t SymTab::symbolOffset() const
        {
            return this->impl->_symbolOffset;
        }
        
        uint32_t SymTab::symbolCount() const
        {
            return this->impl->_symbolCount;
        }
        
        uint32_t SymTab::stringOffset() const
        {
            return this->impl->_stringOffset;
        }
        
        uint32_t SymTab::stringSize() const
        {
            return this->impl->_stringSize;
        }

        std::vector< std::string > SymTab::strings() const
        {
            return this->impl->_strings;
        }

        std::vector< Symbol > SymTab::symbols() const
        {
            return this->impl->_symbols;
        }

        void swap( SymTab & o1, SymTab & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        SymTab::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command(      command ),
            _size(         size ),
            _symbolOffset( stream.readUInt32() ),
            _symbolCount(  stream.readUInt32() ),
            _stringOffset( stream.readUInt32() ),
            _stringSize(   stream.readUInt32() )
        {
            stream.seek( this->_stringOffset, XS::IO::BinaryStream::SeekDirection::Begin );

            while( stream.tell() < this->_stringOffset + this->_stringSize )
            {
                this->_strings.push_back( stream.readNULLTerminatedString() );
            }

            stream.seek( this->_symbolOffset, XS::IO::BinaryStream::SeekDirection::Begin );

            for( uint32_t i = 0; i < this->_symbolCount; i++ )
            {
                this->_symbols.push_back( { kind, this->_stringOffset, stream } );
            }
        }
        
        SymTab::IMPL::IMPL( const IMPL & o ):
            _command(      o._command ),
            _size(         o._size ),
            _symbolOffset( o._symbolOffset ),
            _symbolCount(  o._symbolCount ),
            _stringOffset( o._stringOffset ),
            _stringSize(   o._stringSize ),
            _strings(      o._strings ),
            _symbols(      o._symbols )
        {}

        SymTab::IMPL::~IMPL()
        {}
    }
}
