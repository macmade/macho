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
 * @file        Info.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/Info.hpp>
#include <sstream>

namespace MachO
{
    class Info::IMPL
    {
        public:
            
            IMPL( const std::string & label );
            IMPL( const std::string & label, const std::string & value );
            IMPL( const std::string & label, const std::vector< Info > & children );
            IMPL( const IMPL & o );
            
            std::string         _label;
            std::string         _value;
            std::vector< Info > _children;
    };
    
    Info::Info( const std::string & label ):
        impl( std::make_unique< IMPL >( label ) )
    {}
    
    Info::Info( const std::string & label, const std::string & value ):
        impl( std::make_unique< IMPL >( label, value ) )
    {}
    
    Info::Info( const std::string & label, const std::vector< Info > & children ):
        impl( std::make_unique< IMPL >( label, children ) )
    {}
    
    Info::Info( const Info & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}
    
    Info::Info( Info && o ) noexcept:
        impl( std::move( o.impl ) )
    {}
    
    Info::~Info()
    {}
    
    Info & Info::operator =( Info o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    Info & Info::operator +=( const Info & child )
    {
        this->addChild( child );
        
        return *( this );
    }
    
    void Info::addChild( const Info & child )
    {
        this->impl->_children.push_back( child );
    }
    
    void Info::label( const std::string & label )
    {
        this->impl->_label = label;
    }
    
    void Info::value( const std::string & value )
    {
        this->impl->_value = value;
    }
    
    void Info::value( const std::vector< Info > & children )
    {
        this->impl->_children = children;
    }
    
    std::string Info::label() const
    {
        return this->impl->_label;
    }
    
    std::string Info::value() const
    {
        return this->impl->_value;
    }
    
    std::vector< Info > Info::children() const
    {
        return this->impl->_children;
    }
    
    std::string Info::toString( size_t level, size_t align ) const
    {
        std::stringstream ss;
        std::string       indent( 4 * level, ' ' );
        std::string       label( this->impl->_label );
        
        if( this->impl->_value.length() > 0 || this->impl->_children.size() > 0 )
        {
            label += ":";
            
            align++;
        }
        
        if( this->impl->_value.length() > 0 )
        {
            label += " ";
            
            align++;
            
            if( label.length() < align )
            {
                label += std::string( align - label.length(), ' ' );
            }
        }
        
        ss << indent << label << this->impl->_value;
        
        if( this->impl->_children.size() > 0 )
        {
            ss << std::endl << indent << "{" << std::endl;
            
            align = 0;
            
            for( const auto & child: this->impl->_children )
            {
                align = ( align < child.label().length() ) ? child.label().length() : align;
            }
            
            for( const auto & child: this->impl->_children )
            {
                ss << child.toString( level + 1, align ) << std::endl;
            }
            
            ss << indent << "}";
        }
        
        return ss.str();
    }
    
    void swap( Info & o1, Info & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    std::ostream & operator <<( std::ostream & os, const Info & o )
    {
        os << o.toString();
        
        return os;
    }
    
    Info::IMPL::IMPL( const std::string & label ):
        IMPL( label, "" )
    {}
    
    Info::IMPL::IMPL( const std::string & label, const std::string & value ):
        _label( label ),
        _value( value )
    {}
    
    Info::IMPL::IMPL( const std::string & label, const std::vector< Info > & children ):
        _label( label ),
        _children( children )
    {}
    
    Info::IMPL::IMPL( const IMPL & o ):
        _label(    o._label ),
        _value(    o._value ),
        _children( o._children )
    {}
}
