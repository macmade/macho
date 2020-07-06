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
 * @file        SubLibrary.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/SubLibrary.hpp>
#include <MachO/Casts.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class SubLibrary::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t    _command;
                uint32_t    _size;
                std::string _name;
        };

        SubLibrary::SubLibrary( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        SubLibrary::SubLibrary( const SubLibrary & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        SubLibrary::SubLibrary( SubLibrary && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        SubLibrary::~SubLibrary()
        {}

        SubLibrary & SubLibrary::operator =( SubLibrary o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::string SubLibrary::description() const
        {
            return this->name();
        }
        
        uint32_t SubLibrary::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t SubLibrary::size() const
        {
            return this->impl->_size;
        }
        
        std::string SubLibrary::name() const
        {
            return this->impl->_name;
        }
        
        void swap( SubLibrary & o1, SubLibrary & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        SubLibrary::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream ):
            _command( command ),
            _size(    size )
        {
            size_t   begin(  stream.tell() - 8 );
            uint32_t offset( stream.readUInt32() );
            
            ( void )kind;
            
            stream.seek( numeric_cast< ssize_t >( begin + offset ), BinaryStream::SeekDirection::Begin );
            
            this->_name = stream.readNULLTerminatedString();
        }
        
        SubLibrary::IMPL::IMPL( const IMPL & o ):
            _command( o._command ),
            _size(    o._size ),
            _name(    o._name )
        {}

        SubLibrary::IMPL::~IMPL()
        {}
    }
}
