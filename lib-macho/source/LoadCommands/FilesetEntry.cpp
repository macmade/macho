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
 * @file        FilesetEntry.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/FilesetEntry.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class FilesetEntry::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t    _command;
                uint32_t    _size;
                uint64_t    _vmAddress;
                uint64_t    _fileOffset;
                std::string _entryID;
        };

        FilesetEntry::FilesetEntry( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        FilesetEntry::FilesetEntry( const FilesetEntry & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        FilesetEntry::FilesetEntry( FilesetEntry && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        FilesetEntry::~FilesetEntry()
        {}

        FilesetEntry & FilesetEntry::operator =( FilesetEntry o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info FilesetEntry::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );
            
            i.addChild( { "VM address",  XS::ToString::Hex( this->vmAddress() ) } );
            i.addChild( { "File offset", XS::ToString::Hex( this->fileOffset() ) } );
            i.addChild( { "Entry ID",    this->entryID() } );
            
            return i;
        }
        
        uint32_t FilesetEntry::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t FilesetEntry::size() const
        {
            return this->impl->_size;
        }
        
        uint64_t FilesetEntry::vmAddress() const
        {
            return this->impl->_vmAddress;
        }
        
        uint64_t FilesetEntry::fileOffset() const
        {
            return this->impl->_fileOffset;
        }
        
        std::string FilesetEntry::entryID() const
        {
            return this->impl->_entryID;
        }
        
        void swap( FilesetEntry & o1, FilesetEntry & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        FilesetEntry::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command(    command ),
            _size(       size ),
            _vmAddress(  stream.readUInt64() ),
            _fileOffset( stream.readUInt64() )
        {
            size_t   begin(  stream.tell() - 8 );
            uint32_t offset( stream.readUInt32() );
            
            ( void )kind;
            
            stream.seek( begin + offset, XS::IO::BinaryStream::SeekDirection::Begin );
            
            this->_entryID = stream.readNULLTerminatedString();
        }
        
        FilesetEntry::IMPL::IMPL( const IMPL & o ):
            _command(    o._command ),
            _size(       o._size ),
            _vmAddress(  o._vmAddress ),
            _fileOffset( o._fileOffset ),
            _entryID(    o._entryID )
        {}

        FilesetEntry::IMPL::~IMPL()
        {}
    }
}
