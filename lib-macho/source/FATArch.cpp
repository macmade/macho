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
 * @file        FATArch.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/FATArch.hpp>

namespace MachO
{
    class FATArch::IMPL
    {
        public:
            
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();
            
            uint32_t _cpuType;
            uint32_t _cpuSubType;
            uint32_t _offset;
            uint32_t _size;
            uint32_t _align;
    };
    
    FATArch::FATArch( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}
    
    FATArch::FATArch( const FATArch & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    FATArch::FATArch( FATArch && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    FATArch::~FATArch()
    {}

    FATArch & FATArch::operator =( FATArch o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    uint32_t FATArch::cpuType() const
    {
        return this->impl->_cpuType;
    }
    
    uint32_t FATArch::cpuSubType() const
    {
        return this->impl->_cpuSubType;
    }
    
    uint32_t FATArch::offset() const
    {
        return this->impl->_offset;
    }
    
    uint32_t FATArch::size() const
    {
        return this->impl->_size;
    }
    
    uint32_t FATArch::align() const
    {
        return this->impl->_align;
    }
    
    void swap( FATArch & o1, FATArch & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    FATArch::IMPL::IMPL( BinaryStream & stream ):
        _cpuType(    stream.readBigEndianUInt32() ),
        _cpuSubType( stream.readBigEndianUInt32() ),
        _offset(     stream.readBigEndianUInt32() ),
        _size(       stream.readBigEndianUInt32() ),
        _align(      stream.readBigEndianUInt32() )
    {}
    
    FATArch::IMPL::IMPL( const IMPL & o ):
        _cpuType(    o._cpuType ),
        _cpuSubType( o._cpuSubType ),
        _offset(     o._offset ),
        _size(       o._size ),
        _align(      o._align )
    {}
    
    FATArch::IMPL::~IMPL()
    {}
}
