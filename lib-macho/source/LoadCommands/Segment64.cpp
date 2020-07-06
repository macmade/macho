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
 * @file        Segment64.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/Segment64.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class Segment64::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t    _command;
                uint32_t    _size;
                std::string _name;
                uint64_t    _vmAddress;
                uint64_t    _vmSize;
                uint64_t    _fileOffset;
                uint64_t    _fileSize;
                uint32_t    _maxProtection;
                uint32_t    _initProtection;
                uint32_t    _numberOfSections;
                uint32_t    _flags;
        };

        Segment64::Segment64( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        Segment64::Segment64( const Segment64 & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        Segment64::Segment64( Segment64 && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        Segment64::~Segment64()
        {}

        Segment64 & Segment64::operator =( Segment64 o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        Info Segment64::getInfo() const
        {
            Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Name",        this->name() } );
            i.addChild( { "VM address",  ToString::Hex(  this->vmAddress() ) } );
            i.addChild( { "VM size",     ToString::Size( this->vmSize() ) } );
            i.addChild( { "File offset", ToString::Hex(  this->fileOffset() ) } );
            i.addChild( { "File size",   ToString::Size( this->fileSize() ) } );
            i.addChild( { "Max prot",    ToString::Hex(  this->maxProtection() ) } );
            i.addChild( { "Init prot",   ToString::Hex(  this->initProtection() ) } );
            i.addChild( { "Sections",    std::to_string( this->numberOfSections() ) } );
            i.addChild( { "Flags",       ToString::Hex(  this->flags() ) } );
            
            return i;
        }
        
        uint32_t Segment64::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t Segment64::size() const
        {
            return this->impl->_size;
        }
        
        std::string Segment64::name() const
        {
            return this->impl->_name;
        }
        
        uint64_t Segment64::vmAddress() const
        {
            return this->impl->_vmAddress;
        }
        
        uint64_t Segment64::vmSize() const
        {
            return this->impl->_vmSize;
        }
        
        uint64_t Segment64::fileOffset() const
        {
            return this->impl->_fileOffset;
        }
        
        uint64_t Segment64::fileSize() const
        {
            return this->impl->_fileSize;
        }
        
        uint32_t Segment64::maxProtection() const
        {
            return this->impl->_maxProtection;
        }
        
        uint32_t Segment64::initProtection() const
        {
            return this->impl->_initProtection;
        }
        
        uint32_t Segment64::numberOfSections() const
        {
            return this->impl->_numberOfSections;
        }
        
        uint32_t Segment64::flags() const
        {
            return this->impl->_flags;
        }
        
        void swap( Segment64 & o1, Segment64 & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Segment64::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            _command(          command ),
            _size(             size ),
            _name(             stream.readString( 16 ) ),
            _vmAddress(        stream.readUInt64() ),
            _vmSize(           stream.readUInt64() ),
            _fileOffset(       stream.readUInt64() ),
            _fileSize(         stream.readUInt64() ),
            _maxProtection(    stream.readUInt32() ),
            _initProtection(   stream.readUInt32() ),
            _numberOfSections( stream.readUInt32() ),
            _flags(            stream.readUInt32() )
        {
            ( void )kind;
        }
        
        Segment64::IMPL::IMPL( const IMPL & o ):
            _command(          o._command ),
            _size(             o._size ),
            _name(             o._name ),
            _vmAddress(        o._vmAddress ),
            _vmSize(           o._vmSize ),
            _fileOffset(       o._fileOffset ),
            _fileSize(         o._fileSize ),
            _maxProtection(    o._maxProtection ),
            _initProtection(   o._initProtection ),
            _numberOfSections( o._numberOfSections ),
            _flags(            o._flags )
        {}

        Segment64::IMPL::~IMPL()
        {}
    }
}
