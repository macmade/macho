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
 * @header      CacheFile.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_CACHE_FILE_HPP
#define MACHO_CACHE_FILE_HPP

#include <memory>
#include <algorithm>
#include <vector>
#include <MachO/BinaryStream.hpp>
#include <MachO/InfoObject.hpp>
#include <MachO/CacheImageInfo.hpp>

namespace MachO
{
    class CacheFile: public InfoObject
    {
        public:
            
            CacheFile( const std::string & path );
            CacheFile( BinaryStream & stream );
            CacheFile( const CacheFile & o );
            CacheFile( CacheFile && o ) noexcept;
            ~CacheFile( void ) override;
            
            CacheFile & operator =( CacheFile o );
            
            Info getInfo() const override;
            
            std::string header()        const;
            uint32_t    mappingOffset() const;
            uint32_t    mappingCount()  const;
            uint32_t    imageOffset()   const;
            uint32_t    imageCount()    const;
            uint32_t    baseAddress()   const;
            
            std::vector< CacheImageInfo > images() const;
            
            friend void swap( CacheFile & o1, CacheFile & o2 );
            
        private:
            
            class IMPL;
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_CACHE_FILE_HPP */
