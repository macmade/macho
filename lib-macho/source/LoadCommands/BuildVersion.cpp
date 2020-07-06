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
 * @file        BuildVersion.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/BuildVersion.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class BuildVersion::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t            _command;
                uint32_t            _size;
                Platform            _platform;
                uint32_t            _minOS;
                uint32_t            _sdk;
                std::vector< Tool > _tools;
        };

        BuildVersion::BuildVersion( uint32_t command, uint32_t size, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, stream ) )
        {}
        
        BuildVersion::BuildVersion( const BuildVersion & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        BuildVersion::BuildVersion( BuildVersion && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        BuildVersion::~BuildVersion()
        {}

        BuildVersion & BuildVersion::operator =( BuildVersion o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        Info BuildVersion::getInfo() const
        {
            Info i( LoadCommand::getInfo() );
            
            i.addChild( this->platform() );
            i.addChild( { "Min OS", ToString::Version( this->minOS() ) } );
            i.addChild( { "SDK",    ToString::Version( this->sdk() ) } );
            
            if( this->impl->_tools.size() > 0 )
            {
                Info tools( "Tools" );
                
                for( const auto & tool: this->impl->_tools )
                {
                    tools.addChild( tool );
                }
                
                i.addChild( tools );
            }
            
            return i;
        }
        
        uint32_t BuildVersion::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t BuildVersion::size() const
        {
            return this->impl->_size;
        }
        
        Platform BuildVersion::platform() const
        {
            return this->impl->_platform;
        }
        
        uint32_t BuildVersion::minOS() const
        {
            return this->impl->_minOS;
        }
        
        uint32_t BuildVersion::sdk() const
        {
            return this->impl->_sdk;
        }
        
        std::vector< Tool > BuildVersion::tools() const
        {
            return this->impl->_tools;
        }
        
        void swap( BuildVersion & o1, BuildVersion & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        BuildVersion::IMPL::IMPL( uint32_t command, uint32_t size, BinaryStream & stream ):
            _command(  command ),
            _size(     size ),
            _platform( stream.readUInt32() ),
            _minOS(    stream.readUInt32() ),
            _sdk(      stream.readUInt32() )
        {
            uint32_t n( stream.readUInt32() );
            
            for( uint32_t i = 0; i < n; i++ )
            {
                this->_tools.push_back( { stream.readUInt32(), stream.readUInt32() } );
            }
        }
        
        BuildVersion::IMPL::IMPL( const IMPL & o ):
            _command(  o._command ),
            _size(     o._size ),
            _platform( o._platform ),
            _minOS(    o._minOS ),
            _sdk(      o._sdk ),
            _tools(    o._tools )
        {}

        BuildVersion::IMPL::~IMPL()
        {}
    }
}
