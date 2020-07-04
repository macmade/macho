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
            
            std::string                                      _label;
            std::variant< std::string, std::vector< Info > > _value;
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
        std::vector< Info > v;
        
        try
        {
            v = std::get< 1 >( this->impl->_value );
        }
        catch( ... )
        {}
        
        v.push_back( child );
        
        this->impl->_value = v;
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
        this->impl->_value = children;
    }
    
    std::string Info::label() const
    {
        return this->impl->_label;
    }
    
    std::variant< std::string, std::vector< Info > > Info::value() const
    {
        return this->impl->_value;
    }
    
    std::string Info::toString( size_t level, size_t align ) const
    {
        std::stringstream ss;
        std::string       indent( 4 * level, ' ' );
        
        try
        {
            std::string v( std::get< 0 >( this->impl->_value ) );
            std::string l( this->impl->_label );
            
            l += ":";
            
            align++;
            
            if( l.length() < align )
            {
                l += std::string( align - l.length(), ' ' );
            }
            
            ss << indent << l << " " << v;
        }
        catch( ... )
        {
            try
            {
                std::vector< Info > v( std::get< 1 >( this->impl->_value ) );
                
                ss << indent << this->impl->_label << ": " << std::endl
                   << indent << "{";
                
                if( v.size() > 0 )
                {
                    ss << std::endl;
                }
                
                align = 0;
                
                for( const auto & child: v )
                {
                    align = ( align < child.label().length() ) ? child.label().length() : align;
                }
                
                for( const auto & child: v )
                {
                    ss << child.toString( level + 1, align ) << std::endl;
                }
                
                ss << indent << "}";
            }
            catch( ... )
            {}
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
        _value( children )
    {}
    
    Info::IMPL::IMPL( const IMPL & o ):
        _label( o._label ),
        _value( o._value )
    {}
}
