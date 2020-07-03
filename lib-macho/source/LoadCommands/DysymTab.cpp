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
#include <MachO/Casts.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class DysymTab::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t _command;
                uint32_t _size;
        };

        DysymTab::DysymTab( uint32_t command, uint32_t size, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, stream ) )
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
        
        uint32_t DysymTab::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t DysymTab::size() const
        {
            return this->impl->_size;
        }
        
        void swap( DysymTab & o1, DysymTab & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        DysymTab::IMPL::IMPL( uint32_t command, uint32_t size, BinaryStream & stream ):
            _command( command ),
            _size(    size )
        {
            ( void )stream;
        }
        
        DysymTab::IMPL::IMPL( const IMPL & o ):
            _command( o._command ),
            _size(    o._size )
        {}

        DysymTab::IMPL::~IMPL()
        {}
    }
}