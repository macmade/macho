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
 * @file        DataInfo.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/DataInfo.hpp>
#include <sys/ioctl.h>

namespace MachO
{
    class DataInfo::IMPL
    {
        public:
            
            IMPL( const std::string & label, const std::vector< uint8_t > & data );
            IMPL( const IMPL & o );
            ~IMPL( void );
            
            std::string            _label;
            std::vector< uint8_t > _data;
    };

    DataInfo::DataInfo( const std::string & label, const std::vector< uint8_t > & data ):
        impl( std::make_unique< IMPL >( label, data ) )
    {}

    DataInfo::DataInfo( const DataInfo & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    DataInfo::DataInfo( DataInfo && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    DataInfo::~DataInfo( void )
    {}

    DataInfo & DataInfo::operator =( DataInfo o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    XS::Info DataInfo::getInfo() const
    {
        XS::Info info( this->impl->_label );
        size_t   size( this->impl->_data.size() );
        
        if( size > 0 )
        {
            struct winsize w;
            
            memset( &w, 0, sizeof( w ) );
            ioctl( fileno( stdout ), TIOCGWINSZ, &w );
            
            if( w.ws_col == 0 )
            {
                w.ws_col = 80;
            }
            
            {
                size_t n( ( w.ws_col - 19 ) / 3 );
                size_t i( 0 );
                
                while( i < size )
                {
                    std::stringstream ss;
                    
                    for( size_t j = 0; j < n; j++ )
                    {
                        if( i + j >= size )
                        {
                            ss << "  ";
                        }
                        else
                        {
                            ss << std::hex
                               << std::uppercase
                               << std::setw( 2 )
                               << std::setfill( '0' )
                               << static_cast< uint64_t >( this->impl->_data[ i + j ] );
                        }
                    }
                    
                    ss << " | ";
                    
                    for( size_t j = 0; j < n; j++ )
                    {
                        if( i + j >= size )
                        {
                            break;
                        }
                        
                        if( std::isprint( static_cast< char >( this->impl->_data[ i + j ] ) ) )
                        {
                            ss << static_cast< char >( this->impl->_data[ i + j ] );
                        }
                        else
                        {
                            ss << ".";
                        }
                    }
                    
                    info.addChild( ss.str() );
                    
                    i+= n;
                }
            }
            
            info.value( XS::ToString::Size( this->impl->_data.size() ) );
        }
        else
        {
            info.value( "--" );
        }
        
        return info;
    }
    
    std::string DataInfo::label() const
    {
        return this->impl->_label;
    }
    
    std::vector< uint8_t > DataInfo::data() const
    {
        return this->impl->_data;
    }
    
    void swap( DataInfo & o1, DataInfo & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }

    DataInfo::IMPL::IMPL( const std::string & label, const std::vector< uint8_t > & data ):
        _label( label ),
        _data(  data )
    {}

    DataInfo::IMPL::IMPL( const IMPL & o ):
        _label( o._label ),
        _data(  o._data )
    {}

    DataInfo::IMPL::~IMPL( void )
    {}
}
