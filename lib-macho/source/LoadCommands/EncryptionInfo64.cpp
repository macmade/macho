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
 * @file        EncryptionInfo64.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/EncryptionInfo64.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class EncryptionInfo64::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _cryptOffset;
                uint32_t _cryptSize;
                uint32_t _cryptID;
        };

        EncryptionInfo64::EncryptionInfo64( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        EncryptionInfo64::EncryptionInfo64( const EncryptionInfo64 & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        EncryptionInfo64::EncryptionInfo64( EncryptionInfo64 && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        EncryptionInfo64::~EncryptionInfo64()
        {}

        EncryptionInfo64 & EncryptionInfo64::operator =( EncryptionInfo64 o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        Info EncryptionInfo64::getInfo() const
        {
            Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Crypt offset", ToString::Hex( this->cryptOffset() ) } );
            i.addChild( { "Crypt size",   ToString::Hex( this->cryptSize() ) } );
            i.addChild( { "Crypt ID",     ToString::Hex( this->cryptID() ) } );
            
            return i;
        }
        
        uint32_t EncryptionInfo64::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t EncryptionInfo64::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t EncryptionInfo64::cryptOffset() const
        {
            return this->impl->_cryptOffset;
        }
        
        uint32_t EncryptionInfo64::cryptSize() const
        {
            return this->impl->_cryptSize;
        }
        
        uint32_t EncryptionInfo64::cryptID() const
        {
            return this->impl->_cryptID;
        }
        
        void swap( EncryptionInfo64 & o1, EncryptionInfo64 & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        EncryptionInfo64::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  ):
            _command( command ),
            _size(    size ),
            _cryptOffset( stream.readUInt32() ),
            _cryptSize(   stream.readUInt32() ),
            _cryptID(     stream.readUInt32() )
        {
            ( void )kind;
            
            stream.readUInt32();
        }
        
        EncryptionInfo64::IMPL::IMPL( const IMPL & o ):
            _command(     o._command ),
            _size(        o._size ),
            _cryptOffset( o._cryptOffset ),
            _cryptSize(   o._cryptSize ),
            _cryptID(     o._cryptID )
        {}

        EncryptionInfo64::IMPL::~IMPL()
        {}
    }
}
