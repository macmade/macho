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
#include <MachO/BinaryDataStream.hpp>
#include <MachO/LoadCommands/Unknown.hpp>
#include <MachO/LoadCommands/LoadDylib.hpp>
#include <MachO/LoadCommands/Segment.hpp>
#include <MachO/LoadCommands/Segment64.hpp>

namespace MachO
{
    class File::IMPL
    {
        public:
            
            IMPL( const std::string & path );
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();
            
            void parse( BinaryStream & stream );
            void parseLoadCommands( uint32_t count, BinaryStream & stream );
            
            Kind       _kind;
            Endianness _endianness;
            uint32_t   _cpuType;
            uint32_t   _cpuSubType;
            uint32_t   _type;
            uint32_t   _flags;
            
            std::vector< std::shared_ptr< LoadCommand > > _loadCommands;
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
    
    uint32_t File::flags() const
    {
        return this->impl->_flags;
    }
    
    std::vector< std::reference_wrapper< LoadCommand > > File::loadCommands() const
    {
        std::vector< std::reference_wrapper< LoadCommand > > commands;
        
        for( const auto & command: this->impl->_loadCommands )
        {
            commands.push_back( *( command ) );
        }
        
        return commands;
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
        _kind(         o._kind ),
        _endianness(   o._endianness ),
        _cpuType(      o._cpuType ),
        _cpuSubType(   o._cpuSubType ),
        _type(         o._type ),
        _flags(        o._flags ),
        _loadCommands( o._loadCommands )
    {}

    File::IMPL::~IMPL()
    {}
    
    void File::IMPL::parse( BinaryStream & stream )
    {
        uint32_t magic( stream.readUInt32() );
        
        if( magic == 0xFEEDFACE )
        {
            this->_kind       = Kind::MachO32;
            this->_endianness = Endianness::LittleEndian;
            
            stream.setPreferredEndianness( BinaryStream::Endianness::LittleEndian );
        }
        else if( magic == 0xFEEDFACF )
        {
            this->_kind       = Kind::MachO64;
            this->_endianness = Endianness::LittleEndian;
            
            stream.setPreferredEndianness( BinaryStream::Endianness::LittleEndian );
        }
        else if( magic == 0xCEFAEDFE )
        {
            this->_kind       = Kind::MachO32;
            this->_endianness = Endianness::BigEndian;
            
            stream.setPreferredEndianness( BinaryStream::Endianness::BigEndian );
        }
        else if( magic == 0xCFFAEDFE )
        {
            this->_kind       = Kind::MachO64;
            this->_endianness = Endianness::BigEndian;
            
            stream.setPreferredEndianness( BinaryStream::Endianness::BigEndian );
        }
        else
        {
            throw std::runtime_error( "Invalid Mach-O signature" );
        }
        
        this->_cpuType    = stream.readUInt32();
        this->_cpuSubType = stream.readUInt32();
        this->_type       = stream.readUInt32();
        
        {
            uint32_t ncmd( stream.readUInt32() );
            uint32_t scmd( stream.readUInt32() );
            
            this->_flags = stream.readUInt32();
            
            if( this->_kind == Kind::MachO64 )
            {
                stream.readUInt32();
            }
            
            {
                BinaryDataStream data( stream.read( scmd ) );
                
                data.setPreferredEndianness( stream.preferredEndianness() );
                this->parseLoadCommands( ncmd, data );
            }
        }
    }
    
    void File::IMPL::parseLoadCommands( uint32_t count, BinaryStream & stream )
    {
        for( uint32_t i = 0; i < count; i++ )
        {
            uint32_t command( stream.readUInt32() );
            uint32_t size(    stream.readUInt32() );
            
            if( size < 8 )
            {
                throw std::runtime_error( "Invalid load command size" );
            }
            
            stream.seek( -8, BinaryStream::SeekDirection::Current );
            
            {
                BinaryDataStream data( stream.read( size ) );
                std::shared_ptr< LoadCommand > cmd;
                
                data.seek( 8, BinaryStream::SeekDirection::Begin );
                data.setPreferredEndianness( stream.preferredEndianness() );
                
                switch( command )
                {
                    case 0x01: this->_loadCommands.push_back( std::make_shared< LoadCommands::Segment   >( command, size, data ) ); break;
                    case 0x0C: this->_loadCommands.push_back( std::make_shared< LoadCommands::LoadDylib >( command, size, data ) ); break;
                    case 0x19: this->_loadCommands.push_back( std::make_shared< LoadCommands::Segment64 >( command, size, data ) ); break;
                    default:   this->_loadCommands.push_back( std::make_shared< LoadCommands::Unknown   >( command, size, data ) ); break;
                }
            }
        }
    }
}

