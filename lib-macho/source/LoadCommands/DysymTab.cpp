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
 * @file        DysymTab.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/DysymTab.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class DysymTab::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream  );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _localSymbolIndex;
                uint32_t _localSymbolCount;
                uint32_t _externSymbolIndex;
                uint32_t _externSymbolCount;
                uint32_t _undefinedSymbolIndex;
                uint32_t _undefinedSymbolCount;
                uint32_t _contentTableOffset;
                uint32_t _contentTableCount;
                uint32_t _moduleTableOffset;
                uint32_t _moduleTableCount;
                uint32_t _referencedSymbolTableOffset;
                uint32_t _referencedSymbolTableCount;
                uint32_t _indirectSymbolTableOffset;
                uint32_t _indirectSymbolTableCount;
                uint32_t _externalRelocationOffset;
                uint32_t _externalRelocationCount;
                uint32_t _localRelocationOffset;
                uint32_t _localRelocationCount;
        };

        DysymTab::DysymTab( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        DysymTab::DysymTab( const DysymTab & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        DysymTab::DysymTab( DysymTab && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        DysymTab::~DysymTab()
        {}

        DysymTab & DysymTab::operator =( DysymTab o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info DysymTab::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );

            i.addChild( { "Local Symbol Index",             XS::ToString::Hex( this->localSymbolIndex() ) } );
            i.addChild( { "Local Symbol Count",             XS::ToString::Hex( this->localSymbolCount() ) } );
            i.addChild( { "Extern Symbol Index",            XS::ToString::Hex( this->externSymbolIndex() ) } );
            i.addChild( { "Extern Symbol Count",            XS::ToString::Hex( this->externSymbolCount() ) } );
            i.addChild( { "Undefined Symbol Index",         XS::ToString::Hex( this->undefinedSymbolIndex() ) } );
            i.addChild( { "Undefined Symbol Count",         XS::ToString::Hex( this->undefinedSymbolCount() ) } );
            i.addChild( { "Content Table Offset",           XS::ToString::Hex( this->contentTableOffset() ) } );
            i.addChild( { "Content Table Count",            XS::ToString::Hex( this->contentTableCount() ) } );
            i.addChild( { "Module Table Offset",            XS::ToString::Hex( this->moduleTableOffset() ) } );
            i.addChild( { "Module Table Count",             XS::ToString::Hex( this->moduleTableCount() ) } );
            i.addChild( { "Referenced Symbol Table Offset", XS::ToString::Hex( this->referencedSymbolTableOffset() ) } );
            i.addChild( { "Referenced Symbol Table Count",  XS::ToString::Hex( this->referencedSymbolTableCount() ) } );
            i.addChild( { "Indirect Symbol Table Offset",   XS::ToString::Hex( this->indirectSymbolTableOffset() ) } );
            i.addChild( { "Indirect Symbol Table Count",    XS::ToString::Hex( this->indirectSymbolTableCount() ) } );
            i.addChild( { "External Relocation Offset",     XS::ToString::Hex( this->externalRelocationOffset() ) } );
            i.addChild( { "External Relocation Count",      XS::ToString::Hex( this->externalRelocationCount() ) } );
            i.addChild( { "Local Relocation Offset",        XS::ToString::Hex( this->localRelocationOffset() ) } );
            i.addChild( { "Local Relocation Count",         XS::ToString::Hex( this->localRelocationCount() ) } );

            return i;
        }
        
        uint32_t DysymTab::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t DysymTab::size() const
        {
            return this->impl->_size;
        }

        uint32_t DysymTab::localSymbolIndex() const
        {
            return this->impl->_localSymbolIndex;
        }

        uint32_t DysymTab::localSymbolCount() const
        {
            return this->impl->_localSymbolCount;
        }

        uint32_t DysymTab::externSymbolIndex() const
        {
            return this->impl->_externSymbolIndex;
        }

        uint32_t DysymTab::externSymbolCount() const
        {
            return this->impl->_externSymbolCount;
        }

        uint32_t DysymTab::undefinedSymbolIndex() const
        {
            return this->impl->_undefinedSymbolIndex;
        }

        uint32_t DysymTab::undefinedSymbolCount() const
        {
            return this->impl->_undefinedSymbolCount;
        }

        uint32_t DysymTab::contentTableOffset() const
        {
            return this->impl->_contentTableOffset;
        }

        uint32_t DysymTab::contentTableCount() const
        {
            return this->impl->_contentTableCount;
        }

        uint32_t DysymTab::moduleTableOffset() const
        {
            return this->impl->_moduleTableOffset;
        }

        uint32_t DysymTab::moduleTableCount() const
        {
            return this->impl->_moduleTableCount;
        }

        uint32_t DysymTab::referencedSymbolTableOffset() const
        {
            return this->impl->_referencedSymbolTableOffset;
        }

        uint32_t DysymTab::referencedSymbolTableCount() const
        {
            return this->impl->_referencedSymbolTableCount;
        }

        uint32_t DysymTab::indirectSymbolTableOffset() const
        {
            return this->impl->_indirectSymbolTableOffset;
        }

        uint32_t DysymTab::indirectSymbolTableCount() const
        {
            return this->impl->_indirectSymbolTableCount;
        }

        uint32_t DysymTab::externalRelocationOffset() const
        {
            return this->impl->_externalRelocationOffset;
        }

        uint32_t DysymTab::externalRelocationCount() const
        {
            return this->impl->_externalRelocationCount;
        }

        uint32_t DysymTab::localRelocationOffset() const
        {
            return this->impl->_localRelocationOffset;
        }

        uint32_t DysymTab::localRelocationCount() const
        {
            return this->impl->_localRelocationCount;
        }

        void swap( DysymTab & o1, DysymTab & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        DysymTab::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command(                     command ),
            _size(                        size ),
            _localSymbolIndex(            stream.readUInt32() ),
            _localSymbolCount(            stream.readUInt32() ),
            _externSymbolIndex(           stream.readUInt32() ),
            _externSymbolCount(           stream.readUInt32() ),
            _undefinedSymbolIndex(        stream.readUInt32() ),
            _undefinedSymbolCount(        stream.readUInt32() ),
            _contentTableOffset(          stream.readUInt32() ),
            _contentTableCount(           stream.readUInt32() ),
            _moduleTableOffset(           stream.readUInt32() ),
            _moduleTableCount(            stream.readUInt32() ),
            _referencedSymbolTableOffset( stream.readUInt32() ),
            _referencedSymbolTableCount(  stream.readUInt32() ),
            _indirectSymbolTableOffset(   stream.readUInt32() ),
            _indirectSymbolTableCount(    stream.readUInt32() ),
            _externalRelocationOffset(    stream.readUInt32() ),
            _externalRelocationCount(     stream.readUInt32() ),
            _localRelocationOffset(       stream.readUInt32() ),
            _localRelocationCount(        stream.readUInt32() )
        {
            ( void )kind;
        }
        
        DysymTab::IMPL::IMPL( const IMPL & o ):
            _command(                     o._command ),
            _size(                        o._size ),
            _localSymbolIndex(            o._localSymbolIndex ),
            _localSymbolCount(            o._localSymbolCount ),
            _externSymbolIndex(           o._externSymbolIndex ),
            _externSymbolCount(           o._externSymbolCount ),
            _undefinedSymbolIndex(        o._undefinedSymbolIndex ),
            _undefinedSymbolCount(        o._undefinedSymbolCount ),
            _contentTableOffset(          o._contentTableOffset ),
            _contentTableCount(           o._contentTableCount ),
            _moduleTableOffset(           o._moduleTableOffset ),
            _moduleTableCount(            o._moduleTableCount ),
            _referencedSymbolTableOffset( o._referencedSymbolTableOffset ),
            _referencedSymbolTableCount(  o._referencedSymbolTableCount ),
            _indirectSymbolTableOffset(   o._indirectSymbolTableOffset ),
            _indirectSymbolTableCount(    o._indirectSymbolTableCount ),
            _externalRelocationOffset(    o._externalRelocationOffset ),
            _externalRelocationCount(     o._externalRelocationCount ),
            _localRelocationOffset(       o._localRelocationOffset ),
            _localRelocationCount(        o._localRelocationCount )
        {}

        DysymTab::IMPL::~IMPL()
        {}
    }
}
#include <mach-o/loader.h>
