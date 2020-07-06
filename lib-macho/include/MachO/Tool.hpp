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
 * @header      Tool.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_TOOL_HPP
#define MACHO_TOOL_HPP

#include <cstdint>
#include <MachO/InfoObject.hpp>

namespace MachO
{
    class Tool: public InfoObject
    {
        public:
            
            Tool();
            Tool( uint32_t tool, uint32_t version );
            Tool( const Tool & o );
            Tool( Tool && o ) noexcept;
            ~Tool() override;
            
            Tool & operator =( Tool o );
            
            Info getInfo() const override;
            
            uint32_t    tool()    const;
            uint32_t    version() const;
            std::string name()    const;
            
            friend void swap( Tool & o1, Tool & o2 );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_TOOL_HPP */
