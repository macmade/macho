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
 * @file        Tool.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/Tool.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    class Tool::IMPL
    {
        public:
            
            IMPL( uint32_t tool, uint32_t version );
            IMPL( const IMPL & o );
            ~IMPL();
            
            uint32_t _tool;
            uint32_t _version;
    };
    
    Tool::Tool():
        Tool( 0, 0 )
    {}
    
    Tool::Tool( uint32_t tool, uint32_t version ):
        impl( std::make_unique< IMPL >( tool, version ) )
    {}
    
    Tool::Tool( const Tool & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    Tool::Tool( Tool && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    Tool::~Tool()
    {}

    Tool & Tool::operator =( Tool o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    Info Tool::getInfo() const
    {
        return { this->name(), ToString::Version( this->version() ) };
    }
    
    uint32_t Tool::tool() const
    {
        return this->impl->_tool;
    }
    
    uint32_t Tool::version() const
    {
        return this->impl->_version;
    }
    
    std::string Tool::name() const
    {
        switch( this->tool() )
        {
            case 1:  return "Clang";
            case 2:  return "Swift";
            case 3:  return "LD";
            default: return "Unknown";
        }
    }
    
    void swap( Tool & o1, Tool & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    Tool::IMPL::IMPL( uint32_t tool, uint32_t version ):
        _tool(    tool ),
        _version( version )
    {}
    
    Tool::IMPL::IMPL( const IMPL & o ):
        _tool(    o._tool ),
        _version( o._version )
    {}
    
    Tool::IMPL::~IMPL()
    {}
}
