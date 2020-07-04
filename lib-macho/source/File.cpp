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
#include <MachO/InfoObject.hpp>
#include <MachO/ToString.hpp>

#include <MachO/LoadCommands/BuildVersion.hpp>
#include <MachO/LoadCommands/DyldInfo.hpp>
#include <MachO/LoadCommands/Dylib.hpp>
#include <MachO/LoadCommands/Dylinker.hpp>
#include <MachO/LoadCommands/DysymTab.hpp>
#include <MachO/LoadCommands/EncryptionInfo.hpp>
#include <MachO/LoadCommands/EncryptionInfo64.hpp>
#include <MachO/LoadCommands/EntryPoint.hpp>
#include <MachO/LoadCommands/FilesetEntry.hpp>
#include <MachO/LoadCommands/FVMFile.hpp>
#include <MachO/LoadCommands/FVMLib.hpp>
#include <MachO/LoadCommands/Ident.hpp>
#include <MachO/LoadCommands/LinkEditData.hpp>
#include <MachO/LoadCommands/LinkerOption.hpp>
#include <MachO/LoadCommands/Note.hpp>
#include <MachO/LoadCommands/PrebindChecksum.hpp>
#include <MachO/LoadCommands/PreboundDylib.hpp>
#include <MachO/LoadCommands/PrePage.hpp>
#include <MachO/LoadCommands/Routines.hpp>
#include <MachO/LoadCommands/Routines64.hpp>
#include <MachO/LoadCommands/RPath.hpp>
#include <MachO/LoadCommands/Segment.hpp>
#include <MachO/LoadCommands/Segment64.hpp>
#include <MachO/LoadCommands/SourceVersion.hpp>
#include <MachO/LoadCommands/SubClient.hpp>
#include <MachO/LoadCommands/SubFramework.hpp>
#include <MachO/LoadCommands/SubLibrary.hpp>
#include <MachO/LoadCommands/SubUmbrella.hpp>
#include <MachO/LoadCommands/SymSeg.hpp>
#include <MachO/LoadCommands/SymTab.hpp>
#include <MachO/LoadCommands/Thread.hpp>
#include <MachO/LoadCommands/TwoLevelHints.hpp>
#include <MachO/LoadCommands/Unknown.hpp>
#include <MachO/LoadCommands/UUID.hpp>
#include <MachO/LoadCommands/VersionMin.hpp>

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
            CPU        _cpu;
            FileType   _type;
            FileFlags  _flags;
            
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
            
    Info File::getInfo() const
    {
        Info i(        "Mach-O file" );
        Info commands( "Commands" );
        
        for( const auto & command: this->loadCommands() )
        {
            ( void )command;
            
            commands.addChild( { "Command" } );
        }
        
        i.addChild( this->cpu() );
        i.addChild( this->type() );
        i.addChild( this->flags() );
        i.addChild( commands );
        
        return i;
    }
    
    File::Kind File::kind() const
    {
        return this->impl->_kind;
    }
    
    File::Endianness File::endianness() const
    {
        return this->impl->_endianness;
    }
    
    CPU File::cpu() const
    {
        return this->impl->_cpu;
    }
    
    FileType File::type() const
    {
        return this->impl->_type;
    }
    
    FileFlags File::flags() const
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
        _cpu(          o._cpu ),
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
        
        this->_cpu  = { stream.readUInt32(), stream.readUInt32() };
        this->_type = stream.readUInt32();
        
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
                    case 0x01: this->_loadCommands.push_back( std::make_shared< LoadCommands::Segment          >( command, size, data ) ); break;
                    case 0x02: this->_loadCommands.push_back( std::make_shared< LoadCommands::SymTab           >( command, size, data ) ); break;
                    case 0x03: this->_loadCommands.push_back( std::make_shared< LoadCommands::SymSeg           >( command, size, data ) ); break;
                    case 0x04: this->_loadCommands.push_back( std::make_shared< LoadCommands::Thread           >( command, size, data ) ); break;
                    case 0x05: this->_loadCommands.push_back( std::make_shared< LoadCommands::Thread           >( command, size, data ) ); break;
                    case 0x06: this->_loadCommands.push_back( std::make_shared< LoadCommands::FVMLib           >( command, size, data ) ); break;
                    case 0x07: this->_loadCommands.push_back( std::make_shared< LoadCommands::FVMLib           >( command, size, data ) ); break;
                    case 0x08: this->_loadCommands.push_back( std::make_shared< LoadCommands::Ident            >( command, size, data ) ); break;
                    case 0x09: this->_loadCommands.push_back( std::make_shared< LoadCommands::FVMFile          >( command, size, data ) ); break;
                    case 0x0A: this->_loadCommands.push_back( std::make_shared< LoadCommands::PrePage          >( command, size, data ) ); break;
                    case 0x0B: this->_loadCommands.push_back( std::make_shared< LoadCommands::DysymTab         >( command, size, data ) ); break;
                    case 0x0C: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib            >( command, size, data ) ); break;
                    case 0x0D: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib            >( command, size, data ) ); break;
                    case 0x0E: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylinker         >( command, size, data ) ); break;
                    case 0x0F: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylinker         >( command, size, data ) ); break;
                    case 0x10: this->_loadCommands.push_back( std::make_shared< LoadCommands::PreboundDylib    >( command, size, data ) ); break;
                    case 0x11: this->_loadCommands.push_back( std::make_shared< LoadCommands::Routines         >( command, size, data ) ); break;
                    case 0x12: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubFramework     >( command, size, data ) ); break;
                    case 0x13: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubUmbrella      >( command, size, data ) ); break;
                    case 0x14: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubClient        >( command, size, data ) ); break;
                    case 0x15: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubLibrary       >( command, size, data ) ); break;
                    case 0x16: this->_loadCommands.push_back( std::make_shared< LoadCommands::TwoLevelHints    >( command, size, data ) ); break;
                    case 0x17: this->_loadCommands.push_back( std::make_shared< LoadCommands::PrebindChecksum  >( command, size, data ) ); break;
                    case 0x19: this->_loadCommands.push_back( std::make_shared< LoadCommands::Segment64        >( command, size, data ) ); break;
                    case 0x1A: this->_loadCommands.push_back( std::make_shared< LoadCommands::Routines64       >( command, size, data ) ); break;
                    case 0x1B: this->_loadCommands.push_back( std::make_shared< LoadCommands::UUID             >( command, size, data ) ); break;
                    case 0x1D: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, data ) ); break;
                    case 0x1E: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, data ) ); break;
                    case 0x20: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib            >( command, size, data ) ); break;
                    case 0x21: this->_loadCommands.push_back( std::make_shared< LoadCommands::EncryptionInfo   >( command, size, data ) ); break;
                    case 0x22: this->_loadCommands.push_back( std::make_shared< LoadCommands::DyldInfo         >( command, size, data ) ); break;
                    case 0x24: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, data ) ); break;
                    case 0x25: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, data ) ); break;
                    case 0x26: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, data ) ); break;
                    case 0x27: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylinker         >( command, size, data ) ); break;
                    case 0x29: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, data ) ); break;
                    case 0x2A: this->_loadCommands.push_back( std::make_shared< LoadCommands::SourceVersion    >( command, size, data ) ); break;
                    case 0x2B: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, data ) ); break;
                    case 0x2C: this->_loadCommands.push_back( std::make_shared< LoadCommands::EncryptionInfo64 >( command, size, data ) ); break;
                    case 0x2D: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkerOption     >( command, size, data ) ); break;
                    case 0x2E: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, data ) ); break;
                    case 0x2F: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, data ) ); break;
                    case 0x30: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, data ) ); break;
                    case 0x31: this->_loadCommands.push_back( std::make_shared< LoadCommands::Note             >( command, size, data ) ); break;
                    case 0x32: this->_loadCommands.push_back( std::make_shared< LoadCommands::BuildVersion     >( command, size, data ) ); break;
                    
                    case 0x18 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib        >( command, size, data ) ); break;
                    case 0x1C | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::RPath        >( command, size, data ) ); break;
                    case 0x1F | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib        >( command, size, data ) ); break;
                    case 0x22 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::DyldInfo     >( command, size, data ) ); break;
                    case 0x23 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib        > ( command, size, data ) ); break;
                    case 0x28 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::EntryPoint   >( command, size, data ) ); break;
                    case 0x33 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData >( command, size, data ) ); break;
                    case 0x34 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData >( command, size, data ) ); break;
                    case 0x35 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::FilesetEntry >( command, size, data ) ); break;
                    
                    default: this->_loadCommands.push_back( std::make_shared< LoadCommands::Unknown >( command, size, data ) ); break;
                }
            }
        }
    }
}

