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
 * @file        Dylib.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/Dylib.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class Dylib::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t    _command;
                uint32_t    _size;
                std::string _name;
                uint32_t    _timestamp;
                uint32_t    _currentVersion;
                uint32_t    _compatibilityVersion;
        };

        Dylib::Dylib( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        Dylib::Dylib( const Dylib & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        Dylib::Dylib( Dylib && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        Dylib::~Dylib()
        {}

        Dylib & Dylib::operator =( Dylib o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::string Dylib::description() const
        {
            return XS::ToString::Filename( this->name() );
        }
        
        uint32_t Dylib::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t Dylib::size() const
        {
            return this->impl->_size;
        }
        
        std::string Dylib::name() const
        {
            return this->impl->_name;
        }
        
        uint32_t Dylib::timestamp() const
        {
            return this->impl->_timestamp;
        }
        
        uint32_t Dylib::currentVersion() const
        {
            return this->impl->_currentVersion;
        }
        
        uint32_t Dylib::compatibilityVersion() const
        {
            return this->impl->_compatibilityVersion;
        }
        
        void swap( Dylib & o1, Dylib & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Dylib::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command( command ),
            _size(    size )
        {
            size_t   begin(  stream.tell() - 8 );
            uint32_t offset( stream.readUInt32() );
            
            ( void )kind;
            
            this->_timestamp            = stream.readUInt32();
            this->_currentVersion       = stream.readUInt32();
            this->_compatibilityVersion = stream.readUInt32();
            
            stream.seek( begin + offset, XS::IO::BinaryStream::SeekDirection::Begin );
            
            this->_name = stream.readNULLTerminatedString();
        }
        
        Dylib::IMPL::IMPL( const IMPL & o ):
            _command(              o._command ),
            _size(                 o._size ),
            _name(                 o._name ),
            _timestamp(            o._timestamp ),
            _currentVersion(       o._currentVersion ),
            _compatibilityVersion( o._compatibilityVersion )
        {}

        Dylib::IMPL::~IMPL()
        {}
    }
}
