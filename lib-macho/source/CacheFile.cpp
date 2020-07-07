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
 * @file        CacheFile.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/CacheFile.hpp>
#include <MachO/BinaryFileStream.hpp>
#include <MachO/ToString.hpp>
#include <optional>

namespace MachO
{
    class CacheFile::IMPL
    {
        public:
            
            IMPL( const std::string & path );
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL( void );
            
            void parse( BinaryStream & stream );
            
            std::optional< std::string > _path;
    };

    CacheFile::CacheFile( const std::string & path ):
        impl( std::make_unique< IMPL >( path ) )
    {}
    
    CacheFile::CacheFile( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}

    CacheFile::CacheFile( const CacheFile & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    CacheFile::CacheFile( CacheFile && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    CacheFile::~CacheFile( void )
    {}

    CacheFile & CacheFile::operator =( CacheFile o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    Info CacheFile::getInfo() const
    {
        Info i( "Dyld cache file" );
        
        if( this->impl->_path.has_value() )
        {
            i.value( ToString::Filename( this->impl->_path.value() ) );
        }
        
        return i;
    }
    
    void swap( CacheFile & o1, CacheFile & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }

    CacheFile::IMPL::IMPL( const std::string & path ):
        _path( path )
    {
        BinaryFileStream stream( path );
        
        this->parse( stream );
    }
    
    CacheFile::IMPL::IMPL( BinaryStream & stream )
    {
        this->parse( stream );
    }
    
    CacheFile::IMPL::IMPL( const IMPL & o ):
        _path( o._path )
    {}

    CacheFile::IMPL::~IMPL( void )
    {}
    
    void CacheFile::IMPL::parse( BinaryStream & stream )
    {
        ( void )stream;
    }
}
