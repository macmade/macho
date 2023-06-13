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
#include <MachO/DataInfo.hpp>

namespace MachO
{
    std::string LoadCommand::commandName() const
    {
        switch( this->command() )
        {
            case 0x01: return "LC_SEGMENT";
            case 0x02: return "LC_SYMTAB";
            case 0x03: return "LC_SYMSEG";
            case 0x04: return "LC_THREAD";
            case 0x05: return "LC_UNIXTHREAD";
            case 0x06: return "LC_LOADFVMLIB";
            case 0x07: return "LC_IDFVMLIB";
            case 0x08: return "LC_IDENT";
            case 0x09: return "LC_FVMFILE";
            case 0x0A: return "LC_PREPAGE";
            case 0x0B: return "LC_DYSYMTAB";
            case 0x0C: return "LC_LOAD_DYLIB";
            case 0x0D: return "LC_ID_DYLIB";
            case 0x0E: return "LC_LOAD_DYLINKER";
            case 0x0F: return "LC_ID_DYLINKER";
            case 0x10: return "LC_PREBOUND_DYLIB";
            case 0x11: return "LC_ROUTINES";
            case 0x12: return "LC_SUB_FRAMEWORK";
            case 0x13: return "LC_SUB_UMBRELLA";
            case 0x14: return "LC_SUB_CLIENT";
            case 0x15: return "LC_SUB_LIBRARY";
            case 0x16: return "LC_TWOLEVEL_HINTS";
            case 0x17: return "LC_PREBIND_CKSUM";
            case 0x19: return "LC_SEGMENT_64";
            case 0x1A: return "LC_ROUTINES_64";
            case 0x1B: return "LC_UUID";
            case 0x1D: return "LC_CODE_SIGNATURE";
            case 0x1E: return "LC_SEGMENT_SPLIT_INFO";
            case 0x20: return "LC_LAZY_LOAD_DYLIB";
            case 0x21: return "LC_ENCRYPTION_INFO";
            case 0x22: return "LC_DYLD_INFO";
            case 0x24: return "LC_VERSION_MIN_MACOSX";
            case 0x25: return "LC_VERSION_MIN_IPHONEOS";
            case 0x26: return "LC_FUNCTION_STARTS";
            case 0x27: return "LC_DYLD_ENVIRONMENT";
            case 0x29: return "LC_DATA_IN_CODE";
            case 0x2A: return "LC_SOURCE_VERSION";
            case 0x2B: return "LC_DYLIB_CODE_SIGN_DRS";
            case 0x2C: return "LC_ENCRYPTION_INFO_64";
            case 0x2D: return "LC_LINKER_OPTION";
            case 0x2E: return "LC_LINKER_OPTIMIZATION_HINT";
            case 0x2F: return "LC_VERSION_MIN_TVOS";
            case 0x30: return "LC_VERSION_MIN_WATCHOS";
            case 0x31: return "LC_NOTE";
            case 0x32: return "LC_BUILD_VERSION";
            
            case 0x18 | 0x80000000: return "LC_LOAD_WEAK_DYLIB";
            case 0x1C | 0x80000000: return "LC_RPATH";
            case 0x1F | 0x80000000: return "LC_REEXPORT_DYLIB";
            case 0x22 | 0x80000000: return "LC_DYLD_INFO_ONLY";
            case 0x23 | 0x80000000: return "LC_LOAD_UPWARD_DYLIB";
            case 0x28 | 0x80000000: return "LC_MAIN";
            case 0x33 | 0x80000000: return "LC_DYLD_EXPORTS_TRIE";
            case 0x34 | 0x80000000: return "LC_DYLD_CHAINED_FIXUPS";
            case 0x35 | 0x80000000: return "LC_FILESET_ENTRY";

            default: return "Unknown";
        }
    }
    
    std::string LoadCommand::description() const
    {
        return "";
    }
    
    LoadCommand::DataList LoadCommand::data() const
    {
        return {};
    }
    
    std::vector< XS::Info > LoadCommand::dataInfo() const
    {
        std::vector< XS::Info > info;
        
        for( const auto & p: this->data() )
        {
            info.push_back( DataInfo( p.first, p.second ) );
        }
        
        return info;
    }
    
    XS::Info LoadCommand::getInfo() const
    {
        return { this->commandName(), this->description() };
    }
}
