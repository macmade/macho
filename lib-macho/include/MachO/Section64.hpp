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
 * @header      Section64.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_SECTION_64_HPP
#define MACHO_SECTION_64_HPP

#include <memory>
#include <algorithm>
#include <string>
#include <XS.hpp>
#include <MachO/SectionFlags.hpp>

namespace MachO
{
    class Section64: public XS::Info::Object
    {
        public:
            
            Section64( XS::IO::BinaryStream & stream );
            Section64( const Section64 & o );
            Section64( Section64 && o ) noexcept;
            ~Section64( void ) override;
            
            Section64 & operator =( Section64 o );
            
            XS::Info getInfo() const override;
            
            std::string  section()          const;
            std::string  segment()          const;
            uint64_t     address()          const;
            uint64_t     size()             const;
            uint32_t     offset()           const;
            uint32_t     alignment()        const;
            uint32_t     relocationOffset() const;
            uint32_t     relocationCount()  const;
            SectionFlags flags()            const;
            
            friend void swap( Section64 & o1, Section64 & o2 );
            
        private:
            
            class IMPL;
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_SECTION_64_HPP */
