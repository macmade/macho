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
 * @file        FatArch.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/FatArch.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    class FatArch::IMPL
    {
        public:
            
            IMPL( XS::IO::BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();
            
            CPU      _cpu;
            uint32_t _offset;
            uint32_t _size;
            uint32_t _align;
    };
    
    FatArch::FatArch( XS::IO::BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}
    
    FatArch::FatArch( const FatArch & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    FatArch::FatArch( FatArch && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    FatArch::~FatArch()
    {}

    FatArch & FatArch::operator =( FatArch o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    XS::Info FatArch::getInfo() const
    {
        return { this->cpu().description(), XS::ToString::Size( this->size() ) };
    }
    
    CPU FatArch::cpu() const
    {
        return this->impl->_cpu;
    }
    
    uint32_t FatArch::offset() const
    {
        return this->impl->_offset;
    }
    
    uint32_t FatArch::size() const
    {
        return this->impl->_size;
    }
    
    uint32_t FatArch::align() const
    {
        return this->impl->_align;
    }
    
    void swap( FatArch & o1, FatArch & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    FatArch::IMPL::IMPL( XS::IO::BinaryStream & stream ):
        _cpu(    stream.readBigEndianUInt32(), stream.readBigEndianUInt32() ),
        _offset( stream.readBigEndianUInt32() ),
        _size(   stream.readBigEndianUInt32() ),
        _align(  stream.readBigEndianUInt32() )
    {}
    
    FatArch::IMPL::IMPL( const IMPL & o ):
        _cpu(    o._cpu ),
        _offset( o._offset ),
        _size(   o._size ),
        _align(  o._align )
    {}
    
    FatArch::IMPL::~IMPL()
    {}
}
