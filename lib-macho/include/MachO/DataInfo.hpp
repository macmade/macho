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
 * @header      DataInfo.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_DATA_INFO_HPP
#define MACHO_DATA_INFO_HPP

#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>
#include <XS.hpp>

namespace MachO
{
    class DataInfo: public XS::Info::Object
    {
        public:
            
            DataInfo( const std::string & label, const std::vector< uint8_t > & data );
            DataInfo( const DataInfo & o );
            DataInfo( DataInfo && o ) noexcept;
            ~DataInfo( void ) override;
            
            DataInfo & operator =( DataInfo o );
            
            XS::Info getInfo() const override;
            
            std::string            label() const;
            std::vector< uint8_t > data()  const;
            
            friend void swap( DataInfo & o1, DataInfo & o2 );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_DATA_INFO_HPP */
