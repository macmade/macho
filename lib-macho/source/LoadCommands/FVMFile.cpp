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
 * @file        FVMFile.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/FVMFile.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class FVMFile::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t    _command;
                uint32_t    _size;
                std::string _name;
                uint32_t    _headerAddress;
        };

        FVMFile::FVMFile( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        FVMFile::FVMFile( const FVMFile & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        FVMFile::FVMFile( FVMFile && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        FVMFile::~FVMFile()
        {}

        FVMFile & FVMFile::operator =( FVMFile o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info FVMFile::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Name",           this->name() } );
            i.addChild( { "Header address", XS::ToString::Hex( this->headerAddress() ) } );
            
            return i;
        }
        
        uint32_t FVMFile::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t FVMFile::size() const
        {
            return this->impl->_size;
        }
        
        std::string FVMFile::name() const
        {
            return this->impl->_name;
        }
        
        uint32_t FVMFile::headerAddress() const
        {
            return this->impl->_headerAddress;
        }
        
        void swap( FVMFile & o1, FVMFile & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        FVMFile::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command( command ),
            _size(    size )
        {
            size_t   begin(  stream.tell() - 8 );
            uint32_t offset( stream.readUInt32() );
            size_t   pos(    stream.tell() );
            
            ( void )kind;
            
            stream.seek( begin + offset, XS::IO::BinaryStream::SeekDirection::Begin );
            
            this->_name = stream.readNULLTerminatedString();
            
            stream.seek( pos, XS::IO::BinaryStream::SeekDirection::Begin );
            
            this->_headerAddress = stream.readUInt32();
        }
        
        FVMFile::IMPL::IMPL( const IMPL & o ):
            _command(       o._command ),
            _size(          o._size ),
            _name(          o._name ),
            _headerAddress( o._headerAddress )
        {}

        FVMFile::IMPL::~IMPL()
        {}
    }
}
