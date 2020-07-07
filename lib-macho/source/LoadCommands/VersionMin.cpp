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
 * @file        VersionMin.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/VersionMin.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class VersionMin::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _version;
                uint32_t _sdk;
        };

        VersionMin::VersionMin( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        VersionMin::VersionMin( const VersionMin & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        VersionMin::VersionMin( VersionMin && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        VersionMin::~VersionMin()
        {}

        VersionMin & VersionMin::operator =( VersionMin o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info VersionMin::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Version", ToString::Version( this->version() ) } );
            i.addChild( { "SDK",     ToString::Version( this->sdk() ) } );
            
            return i;
        }
        
        uint32_t VersionMin::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t VersionMin::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t VersionMin::version() const
        {
            return this->impl->_version;
        }
        
        uint32_t VersionMin::sdk() const
        {
            return this->impl->_sdk;
        }
        
        void swap( VersionMin & o1, VersionMin & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        VersionMin::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command( command ),
            _size(    size ),
            _version( stream.readUInt32() ),
            _sdk(     stream.readUInt32() )
        {
            ( void )kind;
        }
        
        VersionMin::IMPL::IMPL( const IMPL & o ):
            _command( o._command ),
            _size(    o._size ),
            _version( o._version ),
            _sdk(     o._sdk )
        {}

        VersionMin::IMPL::~IMPL()
        {}
    }
}
