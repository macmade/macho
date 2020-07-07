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
 * @file        LoadCommand.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommand.hpp>

namespace MachO
{
    std::string LoadCommand::description() const
    {
        return "";
    }
    
    XS::Info LoadCommand::getInfo() const
    {
        std::string name;
        
        switch( this->command() )
        {
            case 0x01: name = "LC_SEGMENT";                  break;
            case 0x02: name = "LC_SYMTAB";                   break;
            case 0x03: name = "LC_SYMSEG";                   break;
            case 0x04: name = "LC_THREAD";                   break;
            case 0x05: name = "LC_UNIXTHREAD";               break;
            case 0x06: name = "LC_LOADFVMLIB";               break;
            case 0x07: name = "LC_IDFVMLIB";                 break;
            case 0x08: name = "LC_IDENT";                    break;
            case 0x09: name = "LC_FVMFILE";                  break;
            case 0x0A: name = "LC_PREPAGE";                  break;
            case 0x0B: name = "LC_DYSYMTAB";                 break;
            case 0x0C: name = "LC_LOAD_DYLIB";               break;
            case 0x0D: name = "LC_ID_DYLIB";                 break;
            case 0x0E: name = "LC_LOAD_DYLINKER";            break;
            case 0x0F: name = "LC_ID_DYLINKER";              break;
            case 0x10: name = "LC_PREBOUND_DYLIB";           break;
            case 0x11: name = "LC_ROUTINES";                 break;
            case 0x12: name = "LC_SUB_FRAMEWORK";            break;
            case 0x13: name = "LC_SUB_UMBRELLA";             break;
            case 0x14: name = "LC_SUB_CLIENT";               break;
            case 0x15: name = "LC_SUB_LIBRARY";              break;
            case 0x16: name = "LC_TWOLEVEL_HINTS";           break;
            case 0x17: name = "LC_PREBIND_CKSUM";            break;
            case 0x19: name = "LC_SEGMENT_64";               break;
            case 0x1A: name = "LC_ROUTINES_64";              break;
            case 0x1B: name = "LC_UUID";                     break;
            case 0x1D: name = "LC_CODE_SIGNATURE";           break;
            case 0x1E: name = "LC_SEGMENT_SPLIT_INFO";       break;
            case 0x20: name = "LC_LAZY_LOAD_DYLIB";          break;
            case 0x21: name = "LC_ENCRYPTION_INFO";          break;
            case 0x22: name = "LC_DYLD_INFO";                break;
            case 0x24: name = "LC_VERSION_MIN_MACOSX";       break;
            case 0x25: name = "LC_VERSION_MIN_IPHONEOS";     break;
            case 0x26: name = "LC_FUNCTION_STARTS";          break;
            case 0x27: name = "LC_DYLD_ENVIRONMENT";         break;
            case 0x29: name = "LC_DATA_IN_CODE";             break;
            case 0x2A: name = "LC_SOURCE_VERSION";           break;
            case 0x2B: name = "LC_DYLIB_CODE_SIGN_DRS";      break;
            case 0x2C: name = "LC_ENCRYPTION_INFO_64";       break;
            case 0x2D: name = "LC_LINKER_OPTION";            break;
            case 0x2E: name = "LC_LINKER_OPTIMIZATION_HINT"; break;
            case 0x2F: name = "LC_VERSION_MIN_TVOS";         break;
            case 0x30: name = "LC_VERSION_MIN_WATCHOS";      break;
            case 0x31: name = "LC_NOTE";                     break;
            case 0x32: name = "LC_BUILD_VERSION";            break;
            
            case 0x18 | 0x80000000: name = "LC_LOAD_WEAK_DYLIB";     break;
            case 0x1C | 0x80000000: name = "LC_RPATH";               break;
            case 0x1F | 0x80000000: name = "LC_REEXPORT_DYLIB";      break;
            case 0x22 | 0x80000000: name = "LC_DYLD_INFO_ONLY";      break;
            case 0x23 | 0x80000000: name = "LC_LOAD_UPWARD_DYLIB";   break;
            case 0x28 | 0x80000000: name = "LC_MAIN";                break;
            case 0x33 | 0x80000000: name = "LC_DYLD_EXPORTS_TRIE";   break;
            case 0x34 | 0x80000000: name = "LC_DYLD_CHAINED_FIXUPS"; break;
            case 0x35 | 0x80000000: name = "LC_FILESET_ENTRY";       break;

            default: name = "Unknown"; break;
        }
        
        return { name, this->description() };
    }
}
