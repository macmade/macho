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
 * @file        DyldInfo.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/DyldInfo.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class DyldInfo::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _rebaseOffset;
                uint32_t _rebaseSize;
                uint32_t _bindingOffset;
                uint32_t _bindingSize;
                uint32_t _weakBindingOffset;
                uint32_t _weakBindingSize;
                uint32_t _lazyBindingOffset;
                uint32_t _lazyBindingSize;
                uint32_t _exportOffset;
                uint32_t _exportSize;
                DataList _data;
        };

        DyldInfo::DyldInfo( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        DyldInfo::DyldInfo( const DyldInfo & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        DyldInfo::DyldInfo( DyldInfo && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        DyldInfo::~DyldInfo()
        {}

        DyldInfo & DyldInfo::operator =( DyldInfo o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info DyldInfo::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Rebase offset",       XS::ToString::Hex( this->rebaseOffset() ) } );
            i.addChild( { "Rebase size",         XS::ToString::Hex( this->rebaseSize() ) } );
            i.addChild( { "Binding offset",      XS::ToString::Hex( this->bindingOffset() ) } );
            i.addChild( { "Binding size",        XS::ToString::Hex( this->bindingSize() ) } );
            i.addChild( { "Weak binding offset", XS::ToString::Hex( this->weakBindingOffset() ) } );
            i.addChild( { "Weak binding size",   XS::ToString::Hex( this->weakBindingSize() ) } );
            i.addChild( { "Lazy binding offset", XS::ToString::Hex( this->lazyBindingOffset() ) } );
            i.addChild( { "Lazy binding size",   XS::ToString::Hex( this->lazyBindingSize() ) } );
            i.addChild( { "Export offset",       XS::ToString::Hex( this->exportOffset() ) } );
            i.addChild( { "Export size",         XS::ToString::Hex( this->exportSize() ) } );
            
            return i;
        }
        
        uint32_t DyldInfo::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t DyldInfo::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t DyldInfo::rebaseOffset() const
        {
            return this->impl->_rebaseOffset;
        }
        
        uint32_t DyldInfo::rebaseSize() const
        {
            return this->impl->_rebaseSize;
        }
        
        uint32_t DyldInfo::bindingOffset() const
        {
            return this->impl->_bindingOffset;
        }
        
        uint32_t DyldInfo::bindingSize() const
        {
            return this->impl->_bindingSize;
        }
        
        uint32_t DyldInfo::weakBindingOffset() const
        {
            return this->impl->_weakBindingOffset;
        }
        
        uint32_t DyldInfo::weakBindingSize() const
        {
            return this->impl->_weakBindingSize;
        }
        
        uint32_t DyldInfo::lazyBindingOffset() const
        {
            return this->impl->_lazyBindingOffset;
        }
        
        uint32_t DyldInfo::lazyBindingSize() const
        {
            return this->impl->_lazyBindingSize;
        }
        
        uint32_t DyldInfo::exportOffset() const
        {
            return this->impl->_exportOffset;
        }
        
        uint32_t DyldInfo::exportSize() const
        {
            return this->impl->_exportSize;
        }
        
        LoadCommand::DataList DyldInfo::data() const
        {
            return this->impl->_data;
        }
        
        void swap( DyldInfo & o1, DyldInfo & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        DyldInfo::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command(           command ),
            _size(              size ),
            _rebaseOffset(      stream.readUInt32() ),
            _rebaseSize(        stream.readUInt32() ),
            _bindingOffset(     stream.readUInt32() ),
            _bindingSize(       stream.readUInt32() ),
            _weakBindingOffset( stream.readUInt32() ),
            _weakBindingSize(   stream.readUInt32() ),
            _lazyBindingOffset( stream.readUInt32() ),
            _lazyBindingSize(   stream.readUInt32() ),
            _exportOffset(      stream.readUInt32() ),
            _exportSize(        stream.readUInt32() )
        {
            size_t pos( stream.tell() );
            
            ( void )kind;
            
            stream.seek( this->_rebaseOffset, XS::IO::BinaryStream::SeekDirection::Begin );
            this->_data.push_back( { "Rebase", stream.read( this->_rebaseSize ) } );
            
            stream.seek( this->_bindingOffset, XS::IO::BinaryStream::SeekDirection::Begin );
            this->_data.push_back( { "Binding", stream.read( this->_bindingSize ) } );
            
            stream.seek( this->_weakBindingOffset, XS::IO::BinaryStream::SeekDirection::Begin );
            this->_data.push_back( { "Weak binding", stream.read( this->_weakBindingSize ) } );
            
            stream.seek( this->_lazyBindingOffset, XS::IO::BinaryStream::SeekDirection::Begin );
            this->_data.push_back( { "Lazy binding", stream.read( this->_lazyBindingSize ) } );
            
            stream.seek( this->_exportOffset, XS::IO::BinaryStream::SeekDirection::Begin );
            this->_data.push_back( { "Export", stream.read( this->_exportSize ) } );
            
            stream.seek( pos, XS::IO::BinaryStream::SeekDirection::Begin );
        }
        
        DyldInfo::IMPL::IMPL( const IMPL & o ):
            _command(           o._command ),
            _size(              o._size ),
            _rebaseOffset(      o._rebaseOffset ),
            _rebaseSize(        o._rebaseSize ),
            _bindingOffset(     o._bindingOffset ),
            _bindingSize(       o._bindingSize ),
            _weakBindingOffset( o._weakBindingOffset ),
            _weakBindingSize(   o._weakBindingSize ),
            _lazyBindingOffset( o._lazyBindingOffset ),
            _lazyBindingSize(   o._lazyBindingSize ),
            _exportOffset(      o._exportOffset ),
            _exportSize(        o._exportSize ),
            _data(              o._data )
        {}

        DyldInfo::IMPL::~IMPL()
        {}
    }
}
