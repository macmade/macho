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
 * @header      FatFile.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_FAT_FILE_HPP
#define MACHO_FAT_FILE_HPP

#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <optional>
#include <MachO/FatArch.hpp>
#include <MachO/File.hpp>
#include <XS.hpp>

namespace MachO
{
    class FatFile: public XS::Info::Object
    {
        public:
            
            FatFile( const std::string & path );
            FatFile( XS::IO::BinaryStream & stream );
            FatFile( const FatFile & o );
            FatFile( FatFile && o ) noexcept;
            ~FatFile() override;
            
            FatFile & operator =( FatFile o );
            
            XS::Info getInfo() const override;
            
            std::optional< std::string >              path()          const;
            std::vector< std::pair< FatArch, File > > architectures() const;
            
            friend void swap( FatFile & o1, FatFile & o2 );
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* MACHO_FAT_FILE_HPP */
