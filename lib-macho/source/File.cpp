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
#include <MachO/ToString.hpp>
#include <XS.hpp>
#include <set>

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
            IMPL( XS::IO::BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();
            
            void parse( XS::IO::BinaryStream & stream );
            void parseLoadCommands( uint32_t count, XS::IO::BinaryStream & stream );
            
            std::optional< std::string > _path;
            Kind                         _kind;
            Endianness                   _endianness;
            CPU                          _cpu;
            FileType                     _type;
            FileFlags                    _flags;
            
            std::vector< std::shared_ptr< LoadCommand > > _loadCommands;
    };

    File::File( const std::string & path ):
        impl( std::make_unique< IMPL >( path ) )
    {}
    
    File::File( XS::IO::BinaryStream & stream ):
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
            
    XS::Info File::getInfo() const
    {
        XS::Info i(        "Mach-O file" );
        XS::Info commands( "Commands" );
        
        if( this->impl->_path.has_value() )
        {
            i.value( XS::ToString::Filename( this->impl->_path.value() ) );
        }
        
        commands.value( std::to_string( this->loadCommands().size() ) );
        
        for( const auto & command: this->loadCommands() )
        {
            commands.addChild( command.get() );
        }
        
        i.addChild( this->cpu() );
        i.addChild( this->type() );
        i.addChild( this->flags() );
        i.addChild( commands );
        
        return i;
    }
    
    std::optional< std::string > File::path() const
    {
        return this->impl->_path;
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
    
    std::vector< std::string > File::linkedLibraries() const
    {
        std::vector< std::string > libs;
        
        for( const auto & lib: this->loadCommands< LoadCommands::Dylib >() )
        {
            libs.push_back( lib.name() );
        }
        
        return libs;
    }
    
    std::vector< Symbol > File::symbols() const
    {
        std::vector< Symbol > syms;

        for( const auto & symTab: this->loadCommands< LoadCommands::SymTab >() )
        {
            for( const auto & sym: symTab.symbols() )
            {
                syms.push_back( sym );
            }
        }
        
        return syms;
    }
    
    std::vector< std::string > File::strings() const
    {
        std::vector< std::vector< uint8_t > > cstrings;
        std::vector< std::vector< uint8_t > > ustrings;
        
        for( const auto & command: this->loadCommands< LoadCommands::Segment >() )
        {
            for( const auto & section: command.sections( { "__cstring", "__oslogstring" } ) )
            {
                cstrings.push_back( section.data() );
            }
            
            for( const auto & section: command.sections( "__ustring" ) )
            {
                ustrings.push_back( section.data() );
            }
        }
        
        for( const auto & command: this->loadCommands< LoadCommands::Segment64 >() )
        {
            for( const auto & section: command.sections( { "__cstring", "__oslogstring" } ) )
            {
                cstrings.push_back( section.data() );
            }
            
            for( const auto & section: command.sections( "__ustring" ) )
            {
                ustrings.push_back( section.data() );
            }
        }
        
        {
            std::set< std::string > set;
            
            for( const auto & data: cstrings )
            {
                XS::IO::BinaryDataStream s( data );
                
                while( s.hasBytesAvailable() )
                {
                    set.insert( s.readNULLTerminatedString() );
                }
            }
            
            for( const auto & data: ustrings )
            {
                XS::IO::BinaryDataStream s( data );
                
                while( s.hasBytesAvailable() )
                {
                    std::optional< std::string > str( XS::String::FromUTF16( s.readNULLTerminatedUTF16String() ) );
                    
                    if( str.has_value() )
                    {
                        set.insert( str.value() );
                    }
                }
            }
            
            {
                std::vector< std::string > strings( set.begin(), set.end() );
                
                std::sort( strings.begin(), strings.end() );
                
                return strings;
            }
        }
    }
    
    std::vector< std::string > File::objcClasses() const
    {
        std::vector< std::vector< uint8_t > > sections;
        
        for( const auto & command: this->loadCommands< LoadCommands::Segment >() )
        {
            for( const auto & section: command.sections( "__objc_classname" ) )
            {
                sections.push_back( section.data() );
            }
        }
        
        for( const auto & command: this->loadCommands< LoadCommands::Segment64 >() )
        {
            for( const auto & section: command.sections( "__objc_classname" ) )
            {
                sections.push_back( section.data() );
            }
        }
        
        {
            std::vector< std::string > classes;
            
            for( const auto & data: sections )
            {
                XS::IO::BinaryDataStream s( data );
                
                while( s.hasBytesAvailable() )
                {
                    std::string cls( s.readNULLTerminatedString() );
                    std::string name;
                    
                    if( cls.length() == 0 )
                    {
                        continue;
                    }
                    
                    for( auto c: cls )
                    {
                        if( std::isprint( c ) )
                        {
                            name += c;
                        }
                        else
                        {
                            name += "\\x" + XS::ToString::Hex( static_cast< uint8_t >( c ), false );
                        }
                    }
                    
                    classes.push_back( name );
                }
            }
            
            std::sort( classes.begin(), classes.end() );
            
            return classes;
        }
    }
    
    std::vector< std::string > File::objcMethods() const
    {
        std::vector< std::vector< uint8_t > > sections;
        
        for( const auto & command: this->loadCommands< LoadCommands::Segment >() )
        {
            for( const auto & section: command.sections( "__objc_methname" ) )
            {
                sections.push_back( section.data() );
            }
        }
        
        for( const auto & command: this->loadCommands< LoadCommands::Segment64 >() )
        {
            for( const auto & section: command.sections( "__objc_methname" ) )
            {
                sections.push_back( section.data() );
            }
        }
        
        {
            std::vector< std::string > methods;
            
            for( const auto & data: sections )
            {
                XS::IO::BinaryDataStream s( data );
                
                while( s.hasBytesAvailable() )
                {
                    std::string meth( s.readNULLTerminatedString() );
                    std::string name;
                    
                    if( meth.length() == 0 )
                    {
                        continue;
                    }
                    
                    for( auto c: meth )
                    {
                        if( std::isprint( c ) )
                        {
                            name += c;
                        }
                        else
                        {
                            name += "\\x" + XS::ToString::Hex( static_cast< uint8_t >( c ), false );
                        }
                    }
                    
                    methods.push_back( name );
                }
            }
            
            std::sort( methods.begin(), methods.end() );
            
            return methods;
        }
    }
    
    void swap( File & o1, File & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    File::IMPL::IMPL( const std::string & path ):
        _path( path )
    {
        XS::IO::BinaryFileStream stream( path );
        
        this->parse( stream );
    }
    
    File::IMPL::IMPL( XS::IO::BinaryStream & stream )
    {
        this->parse( stream );
    }

    File::IMPL::IMPL( const IMPL & o ):
        _path(         o._path ),
        _kind(         o._kind ),
        _endianness(   o._endianness ),
        _cpu(          o._cpu ),
        _type(         o._type ),
        _flags(        o._flags ),
        _loadCommands( o._loadCommands )
    {}

    File::IMPL::~IMPL()
    {}
    
    void File::IMPL::parse( XS::IO::BinaryStream & stream )
    {
        uint32_t magic( stream.readUInt32() );
        
        if( magic == 0xFEEDFACE )
        {
            this->_kind       = Kind::MachO32;
            this->_endianness = Endianness::LittleEndian;
            
            stream.setPreferredEndianness( XS::IO::BinaryStream::Endianness::LittleEndian );
        }
        else if( magic == 0xFEEDFACF )
        {
            this->_kind       = Kind::MachO64;
            this->_endianness = Endianness::LittleEndian;
            
            stream.setPreferredEndianness( XS::IO::BinaryStream::Endianness::LittleEndian );
        }
        else if( magic == 0xCEFAEDFE )
        {
            this->_kind       = Kind::MachO32;
            this->_endianness = Endianness::BigEndian;
            
            stream.setPreferredEndianness( XS::IO::BinaryStream::Endianness::BigEndian );
        }
        else if( magic == 0xCFFAEDFE )
        {
            this->_kind       = Kind::MachO64;
            this->_endianness = Endianness::BigEndian;
            
            stream.setPreferredEndianness( XS::IO::BinaryStream::Endianness::BigEndian );
        }
        else
        {
            throw std::runtime_error( "Invalid Mach-O signature: " + XS::ToString::Hex( magic ) );
        }
        
        this->_cpu  = { stream.readUInt32(), stream.readUInt32() };
        this->_type = stream.readUInt32();
        
        {
            uint32_t ncmd( stream.readUInt32() );
            
            stream.readUInt32();
            
            this->_flags = stream.readUInt32();
            
            if( this->_kind == Kind::MachO64 )
            {
                stream.readUInt32();
            }
            
            this->parseLoadCommands( ncmd, stream );
        }
    }
    
    void File::IMPL::parseLoadCommands( uint32_t count, XS::IO::BinaryStream & stream )
    {
        for( uint32_t i = 0; i < count; i++ )
        {
            size_t   pos(     stream.tell() );
            uint32_t command( stream.readUInt32() );
            uint32_t size(    stream.readUInt32() );
            
            if( size < 8 )
            {
                throw std::runtime_error( "Invalid load command size" );
            }
            
            {
                std::shared_ptr< LoadCommand > cmd;
                
                switch( command )
                {
                    case 0x01: this->_loadCommands.push_back( std::make_shared< LoadCommands::Segment          >( command, size, this->_kind, stream ) ); break;
                    case 0x02: this->_loadCommands.push_back( std::make_shared< LoadCommands::SymTab           >( command, size, this->_kind, stream ) ); break;
                    case 0x03: this->_loadCommands.push_back( std::make_shared< LoadCommands::SymSeg           >( command, size, this->_kind, stream ) ); break;
                    case 0x04: this->_loadCommands.push_back( std::make_shared< LoadCommands::Thread           >( command, size, this->_kind, stream ) ); break;
                    case 0x05: this->_loadCommands.push_back( std::make_shared< LoadCommands::Thread           >( command, size, this->_kind, stream ) ); break;
                    case 0x06: this->_loadCommands.push_back( std::make_shared< LoadCommands::FVMLib           >( command, size, this->_kind, stream ) ); break;
                    case 0x07: this->_loadCommands.push_back( std::make_shared< LoadCommands::FVMLib           >( command, size, this->_kind, stream ) ); break;
                    case 0x08: this->_loadCommands.push_back( std::make_shared< LoadCommands::Ident            >( command, size, this->_kind, stream ) ); break;
                    case 0x09: this->_loadCommands.push_back( std::make_shared< LoadCommands::FVMFile          >( command, size, this->_kind, stream ) ); break;
                    case 0x0A: this->_loadCommands.push_back( std::make_shared< LoadCommands::PrePage          >( command, size, this->_kind, stream ) ); break;
                    case 0x0B: this->_loadCommands.push_back( std::make_shared< LoadCommands::DysymTab         >( command, size, this->_kind, stream ) ); break;
                    case 0x0C: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib            >( command, size, this->_kind, stream ) ); break;
                    case 0x0D: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib            >( command, size, this->_kind, stream ) ); break;
                    case 0x0E: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylinker         >( command, size, this->_kind, stream ) ); break;
                    case 0x0F: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylinker         >( command, size, this->_kind, stream ) ); break;
                    case 0x10: this->_loadCommands.push_back( std::make_shared< LoadCommands::PreboundDylib    >( command, size, this->_kind, stream ) ); break;
                    case 0x11: this->_loadCommands.push_back( std::make_shared< LoadCommands::Routines         >( command, size, this->_kind, stream ) ); break;
                    case 0x12: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubFramework     >( command, size, this->_kind, stream ) ); break;
                    case 0x13: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubUmbrella      >( command, size, this->_kind, stream ) ); break;
                    case 0x14: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubClient        >( command, size, this->_kind, stream ) ); break;
                    case 0x15: this->_loadCommands.push_back( std::make_shared< LoadCommands::SubLibrary       >( command, size, this->_kind, stream ) ); break;
                    case 0x16: this->_loadCommands.push_back( std::make_shared< LoadCommands::TwoLevelHints    >( command, size, this->_kind, stream ) ); break;
                    case 0x17: this->_loadCommands.push_back( std::make_shared< LoadCommands::PrebindChecksum  >( command, size, this->_kind, stream ) ); break;
                    case 0x19: this->_loadCommands.push_back( std::make_shared< LoadCommands::Segment64        >( command, size, this->_kind, stream ) ); break;
                    case 0x1A: this->_loadCommands.push_back( std::make_shared< LoadCommands::Routines64       >( command, size, this->_kind, stream ) ); break;
                    case 0x1B: this->_loadCommands.push_back( std::make_shared< LoadCommands::UUID             >( command, size, this->_kind, stream ) ); break;
                    case 0x1D: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, this->_kind, stream ) ); break;
                    case 0x1E: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, this->_kind, stream ) ); break;
                    case 0x20: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib            >( command, size, this->_kind, stream ) ); break;
                    case 0x21: this->_loadCommands.push_back( std::make_shared< LoadCommands::EncryptionInfo   >( command, size, this->_kind, stream ) ); break;
                    case 0x22: this->_loadCommands.push_back( std::make_shared< LoadCommands::DyldInfo         >( command, size, this->_kind, stream ) ); break;
                    case 0x24: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, this->_kind, stream ) ); break;
                    case 0x25: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, this->_kind, stream ) ); break;
                    case 0x26: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, this->_kind, stream ) ); break;
                    case 0x27: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylinker         >( command, size, this->_kind, stream ) ); break;
                    case 0x29: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, this->_kind, stream ) ); break;
                    case 0x2A: this->_loadCommands.push_back( std::make_shared< LoadCommands::SourceVersion    >( command, size, this->_kind, stream ) ); break;
                    case 0x2B: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, this->_kind, stream ) ); break;
                    case 0x2C: this->_loadCommands.push_back( std::make_shared< LoadCommands::EncryptionInfo64 >( command, size, this->_kind, stream ) ); break;
                    case 0x2D: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkerOption     >( command, size, this->_kind, stream ) ); break;
                    case 0x2E: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData     >( command, size, this->_kind, stream ) ); break;
                    case 0x2F: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, this->_kind, stream ) ); break;
                    case 0x30: this->_loadCommands.push_back( std::make_shared< LoadCommands::VersionMin       >( command, size, this->_kind, stream ) ); break;
                    case 0x31: this->_loadCommands.push_back( std::make_shared< LoadCommands::Note             >( command, size, this->_kind, stream ) ); break;
                    case 0x32: this->_loadCommands.push_back( std::make_shared< LoadCommands::BuildVersion     >( command, size, this->_kind, stream ) ); break;
                    
                    case 0x18 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib        >( command, size, this->_kind, stream ) ); break;
                    case 0x1C | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::RPath        >( command, size, this->_kind, stream ) ); break;
                    case 0x1F | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib        >( command, size, this->_kind, stream ) ); break;
                    case 0x22 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::DyldInfo     >( command, size, this->_kind, stream ) ); break;
                    case 0x23 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::Dylib        >( command, size, this->_kind, stream ) ); break;
                    case 0x28 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::EntryPoint   >( command, size, this->_kind, stream ) ); break;
                    case 0x33 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData >( command, size, this->_kind, stream ) ); break;
                    case 0x34 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::LinkEditData >( command, size, this->_kind, stream ) ); break;
                    case 0x35 | 0x80000000: this->_loadCommands.push_back( std::make_shared< LoadCommands::FilesetEntry >( command, size, this->_kind, stream ) ); break;
                    
                    default: this->_loadCommands.push_back( std::make_shared< LoadCommands::Unknown >( command, size, this->_kind, stream ) ); break;
                }
            }
            
            stream.seek( pos + size, XS::IO::BinaryStream::SeekDirection::Begin );
        }
    }
}

