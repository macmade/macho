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
 * @file        SymSeg.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/SymSeg.hpp>
#include <MachO/ToString.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class SymSeg::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
                uint32_t _segmentOffset;
                uint32_t _segmentSize;
        };

        SymSeg::SymSeg( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, kind, stream ) )
        {}
        
        SymSeg::SymSeg( const SymSeg & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        SymSeg::SymSeg( SymSeg && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        SymSeg::~SymSeg()
        {}

        SymSeg & SymSeg::operator =( SymSeg o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        XS::Info SymSeg::getInfo() const
        {
            XS::Info i( LoadCommand::getInfo() );
            
            i.addChild( { "Segment offset", XS::ToString::Hex( this->segmentOffset() ) } );
            i.addChild( { "Segment size",   XS::ToString::Hex( this->segmentSize() ) } );
            
            return i;
        }
        
        uint32_t SymSeg::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t SymSeg::size() const
        {
            return this->impl->_size;
        }
        
        uint32_t SymSeg::segmentOffset() const
        {
            return this->impl->_segmentOffset;
        }
        
        uint32_t SymSeg::segmentSize() const
        {
            return this->impl->_segmentSize;
        }
        
        void swap( SymSeg & o1, SymSeg & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        SymSeg::IMPL::IMPL( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream ):
            _command(       command ),
            _size(          size ),
            _segmentOffset( stream.readUInt32() ),
            _segmentSize(   stream.readUInt32() )
        {
            ( void )kind;
        }
        
        SymSeg::IMPL::IMPL( const IMPL & o ):
            _command(       o._command ),
            _size(          o._size ),
            _segmentOffset( o._segmentOffset ),
            _segmentSize(   o._segmentSize )
        {}

        SymSeg::IMPL::~IMPL()
        {}
    }
}
