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
 * @file        FileType.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/FileType.hpp>

namespace MachO
{
    XS::Info FileType::getInfo() const
    {
        std::string name(        this->name() );
        std::string description( this->description() );
        
        return { "Type", ( description.length() == 0 ) ? name : name + " - " + description };
    }
    
    std::string FileType::name() const
    {
        switch( this->value() )
        {
            case 0x01: return "MH_OBJECT";
            case 0x02: return "MH_EXECUTE";
            case 0x03: return "MH_FVMLIB";
            case 0x04: return "MH_CORE";
            case 0x05: return "MH_PRELOAD";
            case 0x06: return "MH_DYLIB";
            case 0x07: return "MH_DYLINKER";
            case 0x08: return "MH_BUNDLE";
            case 0x09: return "MH_DYLIB_STUB";
            case 0x0A: return "MH_DSYM";
            case 0x0B: return "MH_KEXT_BUNDLE";
            case 0x0C: return "MH_FILESET";
            default:   return "Unknown";
        }
    }
    
    std::string FileType::description() const
    {
        switch( this->value() )
        {
            case 0x01: return "Relocatable object file";
            case 0x02: return "Demand paged executable file";
            case 0x03: return "Fixed VM shared library file";
            case 0x04: return "Core file";
            case 0x05: return "Preloaded executable file";
            case 0x06: return "Dynamically bound shared library";
            case 0x07: return "Dynamic link editor";
            case 0x08: return "Dynamically bound bundle file";
            case 0x09: return "Shared library stub for static linking only";
            case 0x0A: return "Companion file with only debug";
            case 0x0B: return "x86_64 kernel extension";
            case 0x0C: return "File set with a single linkedit";
            default:   return "";
        }
    }
}
