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
            
            std::optional< std::string >    _path;
            std::string                     _header;
            uint32_t                        _mappingOffset;
            uint32_t                        _mappingCount;
            uint32_t                        _imageOffset;
            uint32_t                        _imageCount;
            uint32_t                        _baseAddress;
            std::vector< CacheImageInfo >   _images;
            std::vector< CacheMappingInfo > _mappings;
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
        Info mappings( "Mappings" );
        Info images( "Images" );
        
        if( this->impl->_path.has_value() )
        {
            i.value( ToString::Filename( this->impl->_path.value() ) );
        }
        
        i.addChild( { "Header",         this->header() } );
        i.addChild( { "Mapping offset", ToString::Hex( this->mappingOffset() ) } );
        i.addChild( { "Mapping count",  ToString::Hex( this->mappingCount() ) } );
        i.addChild( { "Image offset",   ToString::Hex( this->imageOffset() ) } );
        i.addChild( { "Image count",    ToString::Hex( this->imageCount() ) } );
        i.addChild( { "Base address",   ToString::Hex( this->baseAddress() ) } );
        
        for( const auto & mapping: this->mappings() )
        {
            mappings.addChild( mapping );
        }
        
        for( const auto & image: this->images() )
        {
            images.addChild( image );
        }
        
        if( this->mappings().size() > 0 )
        {
            i.addChild( mappings );
        }
        
        if( this->images().size() > 0 )
        {
            i.addChild( images );
        }
        
        return i;
    }
    
    std::string CacheFile::header() const
    {
        return this->impl->_header;
    }
    
    uint32_t CacheFile::mappingOffset() const
    {
        return this->impl->_mappingOffset;
    }
    
    uint32_t CacheFile::mappingCount() const
    {
        return this->impl->_mappingCount;
    }
    
    uint32_t CacheFile::imageOffset() const
    {
        return this->impl->_imageOffset;
    }
    
    uint32_t CacheFile::imageCount() const
    {
        return this->impl->_imageCount;
    }
    
    uint32_t CacheFile::baseAddress() const
    {
        return this->impl->_baseAddress;
    }
    
    std::vector< CacheImageInfo > CacheFile::images() const
    {
        return this->impl->_images;
    }
    
    std::vector< CacheMappingInfo > CacheFile::mappings() const
    {
        return this->impl->_mappings;
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
        _path(          o._path ),
        _header(        o._header ),
        _mappingOffset( o._mappingOffset ),
        _mappingCount(  o._mappingCount ),
        _imageOffset(   o._imageOffset ),
        _imageCount(    o._imageCount ),
        _baseAddress(   o._baseAddress ),
        _images(        o._images ),
        _mappings(      o._mappings )
    {}

    CacheFile::IMPL::~IMPL( void )
    {}
    
    void CacheFile::IMPL::parse( BinaryStream & stream )
    {
        this->_header        = stream.readString( 16 );
        this->_mappingOffset = stream.readUInt32();
        this->_mappingCount  = stream.readUInt32();
        this->_imageOffset   = stream.readUInt32();
        this->_imageCount    = stream.readUInt32();
        this->_baseAddress   = stream.readUInt32();
        
        stream.seek( this->_imageOffset, BinaryStream::SeekDirection::Begin );
        
        for( uint32_t i = 0; i < this->_imageCount; i++ )
        {
            this->_images.push_back( stream );
        }
        
        stream.seek( this->_mappingOffset, BinaryStream::SeekDirection::Begin );
        
        for( uint32_t i = 0; i < this->_mappingCount; i++ )
        {
            this->_mappings.push_back( stream );
        }
    }
}
