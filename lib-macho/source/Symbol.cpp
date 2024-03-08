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
 * @file        Symbol.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/Symbol.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    class Symbol::IMPL
    {
        public:

            IMPL( File::Kind kind, uint32_t stringTableOffset, XS::IO::BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();

            std::string _name;
            uint32_t    _nameIndex;
            uint8_t     _type;
            uint8_t     _section;
            uint16_t    _description;
            uint64_t    _value;
    };

    Symbol::Symbol( File::Kind kind, uint32_t stringTableOffset, XS::IO::BinaryStream & stream ):
        impl( std::make_unique< IMPL >( kind, stringTableOffset, stream ) )
    {}

    Symbol::Symbol( const Symbol & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    Symbol::Symbol( Symbol && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    Symbol::~Symbol()
    {}

    Symbol & Symbol::operator =( Symbol o )
    {
        swap( *( this ), o );

        return *( this );
    }

    XS::Info Symbol::getInfo() const
    {
        XS::Info i( "Symbol" );

        i.addChild( { "Name",         this->name() } );
        i.addChild( { "Name Index",   XS::ToString::Hex( this->nameIndex() ) } );

        {
            XS::Info type( "Type", XS::ToString::Hex( this->type() ) );

            type.addChild( { "Symbolic Debugging Entry", std::to_string( ( this->type() & 0xE0 ) != 0 ) } );
            type.addChild( { "Private External Symbol",  std::to_string( ( this->type() & 0x10 ) != 0 ) } );
            type.addChild( { "Undefined",                std::to_string( ( this->type() & 0x0E ) == 0x0 ) } );
            type.addChild( { "Absolute",                 std::to_string( ( this->type() & 0x0E ) == 0x2 ) } );
            type.addChild( { "Defined in Section",       std::to_string( ( this->type() & 0x0E ) == 0xE ) } );
            type.addChild( { "Prebound Undefined",       std::to_string( ( this->type() & 0x0E ) == 0xC ) } );
            type.addChild( { "Indirect",                 std::to_string( ( this->type() & 0x0E ) == 0xA ) } );
            type.addChild( { "External Symbol",          std::to_string( ( this->type() & 0x01 ) != 0 ) } );

            i.addChild( type );
        }

        i.addChild( { "Section",      XS::ToString::Hex( this->section() ) } );
        i.addChild( { "Description",  XS::ToString::Hex( this->description() ) } );
        i.addChild( { "Value",        XS::ToString::Hex( this->value() ) } );

        return i;
    }

    std::string Symbol::name() const
    {
        return this->impl->_name;
    }

    uint32_t Symbol::nameIndex() const
    {
        return this->impl->_nameIndex;
    }

    uint8_t Symbol::type() const
    {
        return this->impl->_type;
    }

    uint8_t Symbol::section() const
    {
        return this->impl->_section;
    }

    uint16_t Symbol::description() const
    {
        return this->impl->_description;
    }

    uint64_t Symbol::value() const
    {
        return this->impl->_value;
    }

    void swap( Symbol & o1, Symbol & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    Symbol::IMPL::IMPL( File::Kind kind, uint32_t stringTableOffset, XS::IO::BinaryStream & stream ):
        _nameIndex(   stream.readUInt32() ),
        _type(        stream.readUInt8() ),
        _section(     stream.readUInt8() ),
        _description( stream.readUInt16() ),
        _value(       kind == File::Kind::MachO32 ? stream.readUInt32() : stream.readUInt64() )
    {
        if( this->_nameIndex != 0 )
        {
            size_t offset = stream.tell();

            stream.seek( stringTableOffset + this->_nameIndex, XS::IO::BinaryStream::SeekDirection::Begin );

            this->_name = stream.readNULLTerminatedString();

            stream.seek( offset, XS::IO::BinaryStream::SeekDirection::Begin );
        }
    }

    Symbol::IMPL::IMPL( const IMPL & o ):
        _name( o._name ),
        _nameIndex( o._nameIndex ),
        _type( o._type ),
        _section( o._section ),
        _description( o._description ),
        _value( o._value )
    {}

    Symbol::IMPL::~IMPL()
    {}
}
