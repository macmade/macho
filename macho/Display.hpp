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
    
    void File( const MachO::File      & file );
    void File( const MachO::FatFile   & file );
    void File( const MachO::CacheFile & file );
    
    void Libs( const MachO::File      & file );
    void Libs( const MachO::FatFile   & file );
    void Libs( const MachO::CacheFile & file );
    
    void Info( const MachO::File      & file );
    void Info( const MachO::FatFile   & file );
    void Info( const MachO::CacheFile & file );
}

#endif /* DISPLAY_HPP */
