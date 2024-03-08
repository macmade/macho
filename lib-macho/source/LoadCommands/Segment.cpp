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
 * @file        Segment.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/Segment.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class Segment::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t               _command;
                uint32_t               _size;
                std::string            _name;
                uint32_t               _vmAddress;
                uint32_t               _vmSize;
                uint32_t               _fileOffset;
                uint32_t               _fileSize;
                uint32_t               _maxProtection;
                uint32_t               _initProtection;
                uint32_t               _flags;
                std::vector< Section > _sections;
        };

        Segment::Segment( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        Segment::Segment( const Segment & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        Segment::Segment( Segment && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        Segment::~Segment()
        {}

        Segment & Segment::operator =( Segment o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info Segment::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );
            XS::Info sections( "Sections" );
            
            i.addChild( { "Name",        this->name() } );
            i.addChild( { "VM address",  XS::ToString::Hex(  this->vmAddress() ) } );
            i.addChild( { "VM size",     XS::ToString::Size( this->vmSize() ) } );
            i.addChild( { "File offset", XS::ToString::Hex(  this->fileOffset() ) } );
            i.addChild( { "File size",   XS::ToString::Size( this->fileSize() ) } );
            i.addChild( { "Max prot",    XS::ToString::Hex(  this->maxProtection() ) } );
            i.addChild( { "Init prot",   XS::ToString::Hex(  this->initProtection() ) } );
            i.addChild( { "Flags",       XS::ToString::Hex(  this->flags() ) } );
            
            for( const auto & section: this->sections() )
            {
                sections.addChild( section );
            }
            
            if( this->sections().size() > 0 )
            {
                sections.value( std::to_string( this->sections().size() ) );
                i.addChild( sections );
            }
            
            return i;
        }
        
        uint32_t Segment::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t Segment::size() const
        {
            return this->impl->_size;
        }
        
        std::string Segment::name() const
        {
            return this->impl->_name;
        }
        
        uint32_t Segment::vmAddress() const
        {
            return this->impl->_vmAddress;
        }
        
        uint32_t Segment::vmSize() const
        {
            return this->impl->_vmSize;
        }
        
        uint32_t Segment::fileOffset() const
        {
            return this->impl->_fileOffset;
        }
        
        uint32_t Segment::fileSize() const
        {
            return this->impl->_fileSize;
        }
        
        uint32_t Segment::maxProtection() const
        {
            return this->impl->_maxProtection;
        }
        
        uint32_t Segment::initProtection() const
        {
            return this->impl->_initProtection;
        }
        
        uint32_t Segment::flags() const
        {
            return this->impl->_flags;
        }
        
        std::vector< Section > Segment::sections() const
        {
            return this->impl->_sections;
        }
        
        std::vector< Section > Segment::sections( const std::string & name ) const
        {
            return this->sections( std::initializer_list< std::string > { name } );
        }
        
        std::vector< Section > Segment::sections( const std::initializer_list< std::string > & names ) const
        {
            std::vector< Section > sections;
            
            for( const auto & section: this->impl->_sections )
            {
                for( const auto & name: names )
                {
                    if( section.section() == name )
                    {
                        sections.push_back( section );
                        
                        break;
                    }
                }
            }
            
            return sections;
        }
        
        void swap( Segment & o1, Segment & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Segment::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command(          command ),
            _size(             size ),
            _name(             stream.readString( 16 ) ),
            _vmAddress(        stream.readUInt32() ),
            _vmSize(           stream.readUInt32() ),
            _fileOffset(       stream.readUInt32() ),
            _fileSize(         stream.readUInt32() ),
            _maxProtection(    stream.readUInt32() ),
            _initProtection(   stream.readUInt32() )
        {
            uint32_t sections( stream.readUInt32() );
            
            ( void )kind;
            
            this->_flags = stream.readUInt32();
            
            for( uint32_t i = 0; i < sections; i++ )
            {
                this->_sections.push_back( stream );
            }
        }
        
        Segment::IMPL::IMPL( const IMPL & o ):
            _command(        o._command ),
            _size(           o._size ),
            _name(           o._name ),
            _vmAddress(      o._vmAddress ),
            _vmSize(         o._vmSize ),
            _fileOffset(     o._fileOffset ),
            _fileSize(       o._fileSize ),
            _maxProtection(  o._maxProtection ),
            _initProtection( o._initProtection ),
            _flags(          o._flags ),
            _sections(       o._sections )
        {}

        Segment::IMPL::~IMPL()
        {}
    }
}
