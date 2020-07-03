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
 * @file        File.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/File.hpp>
#include <MachO/BinaryFileStream.hpp>

namespace MachO
{
    class File::IMPL
    {
        public:
            
            IMPL( const std::string & path );
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();
            
            uint16_t readUInt16( BinaryStream & stream );
            uint32_t readUInt32( BinaryStream & stream );
            uint64_t readUInt64( BinaryStream & stream );
            
            void parse( BinaryStream & stream );
            
            Kind       _kind;
            Endianness _endianness;
            uint32_t   _cpuType;
            uint32_t   _cpuSubType;
            uint32_t   _type;
    };

    File::File( const std::string & path ):
        impl( std::make_unique< IMPL >( path ) )
    {}
    
    File::File( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}
    
    File::File( const File & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    File::File( File && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    File::~File()
    {}

    File & File::operator =( File o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    File::Kind File::kind() const
    {
        return this->impl->_kind;
    }
    
    File::Endianness File::endianness() const
    {
        return this->impl->_endianness;
    }
    
    uint32_t File::cpuType() const
    {
        return this->impl->_cpuType;
    }
    
    uint32_t File::cpuSubType() const
    {
        return this->impl->_cpuSubType;
    }
    
    uint32_t File::type() const
    {
        return this->impl->_type;
    }
    
    void swap( File & o1, File & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    File::IMPL::IMPL( const std::string & path )
    {
        BinaryFileStream stream( path );
        
        this->parse( stream );
    }
    
    File::IMPL::IMPL( BinaryStream & stream )
    {
        this->parse( stream );
    }

    File::IMPL::IMPL( const IMPL & o ):
        _kind(       o._kind ),
        _endianness( o._endianness ),
        _cpuType(    o._cpuType ),
        _cpuSubType( o._cpuSubType ),
        _type(       o._type )
    {}

    File::IMPL::~IMPL()
    {}
    
    uint16_t File::IMPL::readUInt16( BinaryStream & stream )
    {
        if( this->_endianness == Endianness::LittleEndian )
        {
            return stream.readLittleEndianUInt16();
        }
        
        return stream.readBigEndianUInt16();
    }
    
    uint32_t File::IMPL::readUInt32( BinaryStream & stream )
    {
        if( this->_endianness == Endianness::LittleEndian )
        {
            return stream.readLittleEndianUInt32();
        }
        
        return stream.readBigEndianUInt32();
    }
    
    uint64_t File::IMPL::readUInt64( BinaryStream & stream )
    {
        if( this->_endianness == Endianness::LittleEndian )
        {
            return stream.readLittleEndianUInt64();
        }
        
        return stream.readBigEndianUInt64();
    }
    
    void File::IMPL::parse( BinaryStream & stream )
    {
        uint32_t magic( stream.readUInt32() );
        
        if( magic == 0xFEEDFACE )
        {
            this->_kind       = Kind::MachO32;
            this->_endianness = Endianness::LittleEndian;
        }
        else if( magic == 0xFEEDFACF )
        {
            this->_kind       = Kind::MachO64;
            this->_endianness = Endianness::LittleEndian;
        }
        else if( magic == 0xCEFAEDFE )
        {
            this->_kind       = Kind::MachO32;
            this->_endianness = Endianness::BigEndian;
        }
        else if( magic == 0xCFFAEDFE )
        {
            this->_kind       = Kind::MachO64;
            this->_endianness = Endianness::BigEndian;
        }
        else
        {
            throw std::runtime_error( "Invalid Mach-O signature" );
        }
        
        this->_cpuType    = this->readUInt32( stream );
        this->_cpuSubType = this->readUInt32( stream );
        this->_type       = this->readUInt32( stream );
    }
}

