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
 * @file        CacheMappingInfo.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/CacheMappingInfo.hpp>
#include <MachO/ToString.hpp>
#include <MachO/Casts.hpp>

namespace MachO
{
    class CacheMappingInfo::IMPL
    {
        public:
            
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL( void );
            
            uint64_t _address;
            uint64_t _size;
            uint64_t _fileOffset;
            uint32_t _maxProt;
            uint32_t _initProt;
    };

    CacheMappingInfo::CacheMappingInfo( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}

    CacheMappingInfo::CacheMappingInfo( const CacheMappingInfo & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    CacheMappingInfo::CacheMappingInfo( CacheMappingInfo && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    CacheMappingInfo::~CacheMappingInfo( void )
    {}

    CacheMappingInfo & CacheMappingInfo::operator =( CacheMappingInfo o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    Info CacheMappingInfo::getInfo() const
    {
        Info i( "Mapping info" );
        
        i.addChild( { "Address",     ToString::Hex( this->address() ) } );
        i.addChild( { "Size",        ToString::Hex( this->size() ) } );
        i.addChild( { "File offset", ToString::Hex( this->fileOffset() ) } );
        i.addChild( { "Max prot",    ToString::Hex( this->maxProt() ) } );
        i.addChild( { "Init prot",   ToString::Hex( this->initProt() ) } );
        
        return i;
    }
    
    uint64_t CacheMappingInfo::address() const
    {
        return this->impl->_address;
    }
    
    uint64_t CacheMappingInfo::size() const
    {
        return this->impl->_size;
    }
    
    uint64_t CacheMappingInfo::fileOffset() const
    {
        return this->impl->_fileOffset;
    }
    
    uint32_t CacheMappingInfo::maxProt() const
    {
        return this->impl->_maxProt;
    }
    
    uint32_t CacheMappingInfo::initProt() const
    {
        return this->impl->_initProt;
    }
    
    void swap( CacheMappingInfo & o1, CacheMappingInfo & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }

    CacheMappingInfo::IMPL::IMPL( BinaryStream & stream ):
        _address(    stream.readUInt64() ),
        _size(       stream.readUInt64() ),
        _fileOffset( stream.readUInt64() ),
        _maxProt(    stream.readUInt32() ),
        _initProt(   stream.readUInt32() )
    {}

    CacheMappingInfo::IMPL::IMPL( const IMPL & o ):
        _address(    o._address ),
        _size(       o._size ),
        _fileOffset( o._fileOffset ),
        _maxProt(    o._maxProt ),
        _initProt(   o._initProt )
    {}

    CacheMappingInfo::IMPL::~IMPL( void )
    {}
}
