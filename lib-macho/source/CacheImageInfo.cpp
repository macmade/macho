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
 * @file        CacheImageInfo.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/CacheImageInfo.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    class CacheImageInfo::IMPL
    {
        public:
            
            IMPL( XS::IO::BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL( void );
            
            uint64_t    _address;
            uint64_t    _modificationTime;
            uint64_t    _inode;
            std::string _path;
    };

    CacheImageInfo::CacheImageInfo( XS::IO::BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}

    CacheImageInfo::CacheImageInfo( const CacheImageInfo & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    CacheImageInfo::CacheImageInfo( CacheImageInfo && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    CacheImageInfo::~CacheImageInfo( void )
    {}

    CacheImageInfo & CacheImageInfo::operator =( CacheImageInfo o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    XS::Info CacheImageInfo::getInfo() const
    {
        XS::Info i( "Cache image info" );
        
        i.addChild( { "Address",           XS::ToString::Hex( this->address() ) } );
        i.addChild( { "Modification time", XS::ToString::DateTime( this->modificationTime() ) } );
        i.addChild( { "Inode",             XS::ToString::Hex( this->inode() ) } );
        i.addChild( { "Path",              this->path() } );
        
        return i;
    }
    
    uint64_t CacheImageInfo::address() const
    {
        return this->impl->_address;
    }
    
    uint64_t CacheImageInfo::modificationTime() const
    {
        return this->impl->_modificationTime;
    }
    
    uint64_t CacheImageInfo::inode() const
    {
        return this->impl->_inode;
    }
    
    std::string CacheImageInfo::path() const
    {
        return this->impl->_path;
    }
    
    void swap( CacheImageInfo & o1, CacheImageInfo & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }

    CacheImageInfo::IMPL::IMPL( XS::IO::BinaryStream & stream ):
        _address(          stream.readUInt64() ),
        _modificationTime( stream.readUInt64() ),
        _inode(            stream.readUInt64() )
    {
        uint32_t offset( stream.readUInt32() );
        size_t   pos( stream.tell() );
        
        stream.seek( offset, XS::IO::BinaryStream::SeekDirection::Begin );
        
        this->_path = stream.readNULLTerminatedString();
        
        stream.seek( pos, XS::IO::BinaryStream::SeekDirection::Begin );
        stream.readUInt32();
    }

    CacheImageInfo::IMPL::IMPL( const IMPL & o ):
        _address(          o._address ),
        _modificationTime( o._modificationTime ),
        _inode(            o._inode ),
        _path(             o._path )
    {}

    CacheImageInfo::IMPL::~IMPL( void )
    {}
}
