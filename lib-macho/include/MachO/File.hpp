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
 * @header      File.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_FILE_HPP
#define MACHO_FILE_HPP

#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <MachO/BinaryStream.hpp>
#include <MachO/LoadCommand.hpp>
#include <MachO/InfoObject.hpp>
#include <MachO/CPU.hpp>

namespace MachO
{
    class File: public InfoObject
    {
        public:
            
            enum class Kind
            {
                MachO32,
                MachO64
            };
            
            enum class Endianness
            {
                LittleEndian,
                BigEndian
            };
            
            File( const std::string & path );
            File( BinaryStream & stream );
            File( const File & o );
            File( File && o ) noexcept;
            ~File() override;
            
            File & operator =( File o );
            
            Info getInfo() const override;
            
            Kind       kind()       const;
            Endianness endianness() const;
            CPU        cpu()        const;
            uint32_t   type()       const;
            uint32_t   flags()      const;
            
            std::vector< std::reference_wrapper< LoadCommand > > loadCommands() const;
            
            friend void swap( File & o1, File & o2 );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_FILE_HPP */
