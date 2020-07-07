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
 * @header      CacheMappingInfo.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_CACHE_MAPPING_INFO_HPP
#define MACHO_CACHE_MAPPING_INFO_HPP

#include <memory>
#include <algorithm>
#include <string>
#include <XS.hpp>

namespace MachO
{
    class CacheMappingInfo: public XS::Info::Object
    {
        public:
            
            CacheMappingInfo( XS::IO::BinaryStream & stream );
            CacheMappingInfo( const CacheMappingInfo & o );
            CacheMappingInfo( CacheMappingInfo && o ) noexcept;
            ~CacheMappingInfo( void ) override;
            
            CacheMappingInfo & operator =( CacheMappingInfo o );
            
            XS::Info getInfo() const override;
            
            uint64_t address()    const;
            uint64_t size()       const;
            uint64_t fileOffset() const;
            uint32_t maxProt()    const;
            uint32_t initProt()   const;
            
            friend void swap( CacheMappingInfo & o1, CacheMappingInfo & o2 );
            
        private:
            
            class IMPL;
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_CACHE_MAPPING_INFO_HPP */
