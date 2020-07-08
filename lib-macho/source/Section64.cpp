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
 * @file        Section64.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/Section64.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    class Section64::IMPL
    {
        public:
            
            IMPL( XS::IO::BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL( void );
            
            std::string            _section;
            std::string            _segment;
            uint64_t               _address;
            uint64_t               _size;
            uint32_t               _offset;
            uint32_t               _alignment;
            uint32_t               _relocationOffset;
            uint32_t               _relocationCount;
            SectionFlags           _flags;
            std::vector< uint8_t > _data;
    };

    Section64::Section64( XS::IO::BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}

    Section64::Section64( const Section64 & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    Section64::Section64( Section64 && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    Section64::~Section64( void )
    {}

    Section64 & Section64::operator =( Section64 o )
    {
        swap( *( this ), o );
        
        return *( this );
    }

    XS::Info Section64::getInfo() const
    {
        XS::Info i( "Section64" );
        
        i.addChild( { "Section",           this->section() } );
        i.addChild( { "Segment",           this->segment() } );
        i.addChild( { "Address",           XS::ToString::Hex( this->address() ) } );
        i.addChild( { "Size",              XS::ToString::Hex( this->size() ) } );
        i.addChild( { "Offset",            XS::ToString::Hex( this->offset() ) } );
        i.addChild( { "Alignment",         XS::ToString::Hex( this->alignment() ) } );
        i.addChild( { "Relocation offset", XS::ToString::Hex( this->relocationOffset() ) } );
        i.addChild( { "Relocation count",  XS::ToString::Hex( this->relocationCount() ) } );
        i.addChild( this->flags() );
        
        return i;
    }
    
    std::string Section64::section() const
    {
        return this->impl->_section;
    }
    
    std::string Section64::segment() const
    {
        return this->impl->_segment;
    }
    
    uint64_t Section64::address() const
    {
        return this->impl->_address;
    }
    
    uint64_t Section64::size() const
    {
        return this->impl->_size;
    }
    
    uint32_t Section64::offset() const
    {
        return this->impl->_offset;
    }
    
    uint32_t Section64::alignment() const
    {
        return this->impl->_alignment;
    }
    
    uint32_t Section64::relocationOffset() const
    {
        return this->impl->_relocationOffset;
    }
    
    uint32_t Section64::relocationCount() const
    {
        return this->impl->_relocationCount;
    }
    
    SectionFlags Section64::flags() const
    {
        return this->impl->_flags;
    }
    
    std::vector< uint8_t > Section64::data() const
    {
        return this->impl->_data;
    }
    
    void swap( Section64 & o1, Section64 & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }

    Section64::IMPL::IMPL( XS::IO::BinaryStream & stream ):
        _section(          stream.readString( 16 ) ),
        _segment(          stream.readString( 16 ) ),
        _address(          stream.readUInt64() ),
        _size(             stream.readUInt64() ),
        _offset(           stream.readUInt32() ),
        _alignment(        stream.readUInt32() ),
        _relocationOffset( stream.readUInt32() ),
        _relocationCount(  stream.readUInt32() ),
        _flags(            stream.readUInt32() )
    {
        stream.readUInt32();
        stream.readUInt32();
        stream.readUInt32();
        
        {
            size_t pos( stream.tell() );
            
            stream.seek( this->_offset, XS::IO::BinaryStream::SeekDirection::Begin );
            
            this->_data = stream.read( this->_size );
            
            stream.seek( pos, XS::IO::BinaryStream::SeekDirection::Begin );
        }
    }

    Section64::IMPL::IMPL( const IMPL & o ):
        _section(          o._section ),
        _segment(          o._segment ),
        _address(          o._address ),
        _size(             o._size ),
        _offset(           o._offset ),
        _alignment(        o._alignment ),
        _relocationOffset( o._relocationOffset ),
        _relocationCount(  o._relocationCount ),
        _flags(            o._flags ),
        _data(             o._data )
    {}

    Section64::IMPL::~IMPL( void )
    {}
}
