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
 * @header      LoadCommand.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_LOAD_COMMAND_HPP
#define MACHO_LOAD_COMMAND_HPP

#include <cstdint>
#include <string>
#include <optional>
#include <vector>
#include <utility>
#include <XS.hpp>

namespace MachO
{
    class LoadCommand: public XS::Info::Object
    {
        public:
            
            using DataList = std::vector< std::pair< std::string, std::vector< uint8_t > > >;
            
            XS::Info getInfo() const override;
            
            virtual uint32_t command() const = 0;
            virtual uint32_t size()    const = 0;
            
            virtual std::string             commandName() const;
            virtual std::string             description() const;
            virtual DataList                data()        const;
            virtual std::vector< XS::Info > dataInfo()    const;
    };
}

#endif /* MACHO_LOAD_COMMAND_HPP */
