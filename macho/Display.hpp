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
 * @header      Display.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <MachO.hpp>
#include "Arguments.hpp"
#include <stdexcept>
#include <memory>
#include <algorithm>

namespace Display
{
    void Error( const std::exception & e );
    void Help();
    
    XS::Info FileInfo( const MachO::File      & file, const Arguments & args );
    XS::Info FileInfo( const MachO::FatFile   & file, const Arguments & args );
    XS::Info FileInfo( const MachO::CacheFile & file, const Arguments & args );
    
    XS::Info Libs( const MachO::File & file );
    
    void File( const MachO::File      & file, const Arguments & args );
    void File( const MachO::FatFile   & file, const Arguments & args );
    void File( const MachO::CacheFile & file, const Arguments & args );
}

#endif /* DISPLAY_HPP */
