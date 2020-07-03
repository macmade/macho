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
 * @file        FATFile.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/FATFile.hpp>
#include <MachO/BinaryFileStream.hpp>
#include <MachO/BinaryDataStream.hpp>
#include <MachO/Casts.hpp>

namespace MachO
{
    class FATFile::IMPL
    {
        public:
            
            IMPL( const std::string & path );
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();
            
            void parse( BinaryStream & stream );
            
            std::vector< std::pair< FATArch, File > > _archs;
    };

    FATFile::FATFile( const std::string & path ):
        impl( std::make_unique< IMPL >( path ) )
    {}
    
    FATFile::FATFile( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}
    
    FATFile::FATFile( const FATFile & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    FATFile::FATFile( FATFile && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    FATFile::~FATFile()
    {}

    FATFile & FATFile::operator =( FATFile o )
    {
        swap( *( this ), o );
        
        return *( this );
    }

    std::vector< std::pair< FATArch, File > > FATFile::architectures() const
    {
        return this->impl->_archs;
    }
    
    void swap( FATFile & o1, FATFile & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    FATFile::IMPL::IMPL( const std::string & path )
    {
        BinaryFileStream stream( path );
        
        this->parse( stream );
    }
    
    FATFile::IMPL::IMPL( BinaryStream & stream )
    {
        this->parse( stream );
    }

    FATFile::IMPL::IMPL( const IMPL & o ):
        _archs( o._archs )
    {}

    FATFile::IMPL::~IMPL()
    {}
    
    void FATFile::IMPL::parse( BinaryStream & stream )
    {
        if( stream.readBigEndianUInt32() != 0xCAFEBABE )
        {
            throw std::runtime_error( "Invalid Mach-O FAT signature" );
        }
        
        for( uint32_t i = 0, n = stream.readBigEndianUInt32(); i < n; i++ )
        {
            FATArch arch( stream );
            size_t  pos(  stream.tell() );
            
            stream.seek( arch.offset(), BinaryStream::SeekDirection::Begin );
            
            {
                BinaryDataStream data( stream.read( arch.size() ) );
                
                this->_archs.push_back( { arch, data } );
            }
            
            stream.seek( numeric_cast< ssize_t >( pos ), BinaryStream::SeekDirection::Begin );
        }
    }
}
