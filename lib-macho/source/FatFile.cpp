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
 * @file        FatFile.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/FatFile.hpp>
#include <MachO/BinaryFileStream.hpp>
#include <MachO/BinaryDataStream.hpp>
#include <MachO/Casts.hpp>
#include <MachO/ToString.hpp>
#include <optional>

namespace MachO
{
    class FatFile::IMPL
    {
        public:
            
            IMPL( const std::string & path );
            IMPL( BinaryStream & stream );
            IMPL( const IMPL & o );
            ~IMPL();
            
            void parse( BinaryStream & stream );
            
            std::optional< std::string >              _path;
            std::vector< std::pair< FatArch, File > > _archs;
    };

    FatFile::FatFile( const std::string & path ):
        impl( std::make_unique< IMPL >( path ) )
    {}
    
    FatFile::FatFile( BinaryStream & stream ):
        impl( std::make_unique< IMPL >( stream ) )
    {}
    
    FatFile::FatFile( const FatFile & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    FatFile::FatFile( FatFile && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    FatFile::~FatFile()
    {}

    FatFile & FatFile::operator =( FatFile o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
            
    Info FatFile::getInfo() const
    {
        Info i( "Fat Mach-O file" );
        Info archs( "Architectures" );
        
        if( this->impl->_path.has_value() )
        {
            i.value( ToString::Filename( this->impl->_path.value() ) );
        }
        
        for( const auto & p: this->impl->_archs )
        {
            archs.addChild( p.first );
        }
        
        i.addChild( archs );
        
        for( const auto & p: this->impl->_archs )
        {
            i.addChild( p.second );
        }
        
        return i;
    }

    std::vector< std::pair< FatArch, File > > FatFile::architectures() const
    {
        return this->impl->_archs;
    }
    
    void swap( FatFile & o1, FatFile & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    FatFile::IMPL::IMPL( const std::string & path ):
        _path( path )
    {
        BinaryFileStream stream( path );
        
        this->parse( stream );
    }
    
    FatFile::IMPL::IMPL( BinaryStream & stream )
    {
        this->parse( stream );
    }

    FatFile::IMPL::IMPL( const IMPL & o ):
        _path(  o._path ),
        _archs( o._archs )
    {}

    FatFile::IMPL::~IMPL()
    {}
    
    void FatFile::IMPL::parse( BinaryStream & stream )
    {
        uint32_t magic( stream.readBigEndianUInt32() );
        
        if( magic != 0xCAFEBABE )
        {
            throw std::runtime_error( "Invalid Mach-O fat signature: " + ToString::Hex( magic ) );
        }
        
        for( uint32_t i = 0, n = stream.readBigEndianUInt32(); i < n; i++ )
        {
            FatArch arch( stream );
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
