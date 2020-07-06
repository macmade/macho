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
 * @file        PrebindChecksum.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/PrebindChecksum.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class PrebindChecksum::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _checksum;
        };

        PrebindChecksum::PrebindChecksum( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        PrebindChecksum::PrebindChecksum( const PrebindChecksum & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        PrebindChecksum::PrebindChecksum( PrebindChecksum && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        PrebindChecksum::~PrebindChecksum()
        {}

        PrebindChecksum & PrebindChecksum::operator =( PrebindChecksum o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::string PrebindChecksum::description() const
        {
            return ToString::Hex( this->checksum() );
        }
        
        uint32_t PrebindChecksum::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t PrebindChecksum::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t PrebindChecksum::checksum() const
        {
            return this->impl->_checksum;
        }
        
        void swap( PrebindChecksum & o1, PrebindChecksum & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        PrebindChecksum::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            _command(  command ),
            _size(     size ),
            _checksum( stream.readUInt32() )
        {
            ( void )kind;
        }
        
        PrebindChecksum::IMPL::IMPL( const IMPL & o ):
            _command(  o._command ),
            _size(     o._size ),
            _checksum( o._checksum )
        {}

        PrebindChecksum::IMPL::~IMPL()
        {}
    }
}
