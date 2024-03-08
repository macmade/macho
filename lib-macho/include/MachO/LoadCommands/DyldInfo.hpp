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
 * @header      DyldInfo.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_LOAD_COMMANDS_DYLD_INFO_HPP
#define MACHO_LOAD_COMMANDS_DYLD_INFO_HPP

#include <MachO/LoadCommand.hpp>
#include <MachO/File.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class DyldInfo: public LoadCommand
        {
            public:
                
                DyldInfo( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream );
                DyldInfo( const DyldInfo & o );
                DyldInfo( DyldInfo && o ) noexcept;
                ~DyldInfo() override;
                
                DyldInfo & operator =( DyldInfo o );
                
                XS::Info getInfo() const override;
                
                uint32_t command()           const override;
                uint32_t size()              const override;
                uint32_t rebaseOffset()      const;
                uint32_t rebaseSize()        const;
                uint32_t bindingOffset()     const;
                uint32_t bindingSize()       const;
                uint32_t weakBindingOffset() const;
                uint32_t weakBindingSize()   const;
                uint32_t lazyBindingOffset() const;
                uint32_t lazyBindingSize()   const;
                uint32_t exportOffset()      const;
                uint32_t exportSize()        const;
                
                DataList data() const override;
                
                friend void swap( DyldInfo & o1, DyldInfo & o2 );
                
            private:
                
                class IMPL;
                
                std::unique_ptr< IMPL > impl;
        };
    }
}

#endif /* MACHO_LOAD_COMMANDS_DYLD_INFO_HPP */
