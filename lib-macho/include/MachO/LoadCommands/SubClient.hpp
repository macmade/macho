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
 * @header      SubClient.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_LOAD_COMMANDS_SUB_CLIENT_HPP
#define MACHO_LOAD_COMMANDS_SUB_CLIENT_HPP

#include <MachO/LoadCommand.hpp>
#include <MachO/File.hpp>
#include <XS.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class SubClient: public LoadCommand
        {
            public:
                
                SubClient( uint32_t command, uint32_t size, File::Kind kind, XS::IO::BinaryStream & stream  );
                SubClient( const SubClient & o );
                SubClient( SubClient && o ) noexcept;
                ~SubClient() override;
                
                SubClient & operator =( SubClient o );
                
                std::string description() const override;
                
                uint32_t    command() const override;
                uint32_t    size()    const override;
                std::string name()    const;
                
                friend void swap( SubClient & o1, SubClient & o2 );
                
            private:
                
                class IMPL;
                
                std::unique_ptr< IMPL > impl;
        };
    }
}

#endif /* MACHO_LOAD_COMMANDS_SUB_CLIENT_HPP */
