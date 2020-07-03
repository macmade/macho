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
 * @file        ToString.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include "ToString.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

std::string ToString::hex( uint8_t u )
{
    std::stringstream ss;
    
    ss << std::hex
       << std::uppercase
       << std::setw( 2 )
       << std::setfill( '0' )
       << u;
    
    return ss.str();
}

std::string ToString::hex( uint16_t u )
{
    std::stringstream ss;
    
    ss << std::hex
       << std::uppercase
       << std::setw( 4 )
       << std::setfill( '0' )
       << u;
    
    return ss.str();
}

std::string ToString::hex( uint32_t u )
{
    std::stringstream ss;
    
    ss << std::hex
       << std::uppercase
       << std::setw( 8 )
       << std::setfill( '0' )
       << u;
    
    return ss.str();
}

std::string ToString::hex( uint64_t u )
{
    std::stringstream ss;
    
    ss << std::hex
       << std::uppercase
       << std::setw( 16 )
       << std::setfill( '0' )
       << u;
    
    return ss.str();
}

std::string ToString::size( uint64_t size )
{
    if( size < 1000 )
    {
        return std::to_string( size ) + " bytes";
    }
    else
    {
        double            s( static_cast< double >( size ) );
        std::stringstream ss;
        
        ss << std::fixed << std::setprecision( 2 );
        
        if( size < 1000 * 1000 )
        {
            ss << s / 1000.0;
            ss << " KB";
        }
        else if( size < 1000 * 1000 * 1000 )
        {
            ss << ( s / 1000.0 ) / 1000.0;
            ss << " MB";
        }
        else
        {
            ss << ( ( s / 1000.0 ) / 1000.0 ) / 1000.0;
            ss << " GB";
        }
        
        return ss.str();
    }
}

std::string ToString::cpu( uint32_t type, uint32_t subType )
{
    std::stringstream ss;
    uint32_t          abi(    type &  0xFF000000 );
    uint32_t          family( type & ~0xFF000000 );
    
    if( family == 1 )
    {
        switch( subType )
        {
            case 0:  ss << "VAX (Generic)"; break;
            case 1:  ss << "VAX-11/780";    break;
            case 2:  ss << "VAX-11/785";    break;
            case 3:  ss << "VAX-11/750";    break;
            case 4:  ss << "VAX-11/730";    break;
            case 5:  ss << "MicroVAX I";    break;
            case 6:  ss << "MicroVAX II";   break;
            case 7:  ss << "VAX 8200";      break;
            case 8:  ss << "VAX 8500";      break;
            case 9:  ss << "VAX 8600";      break;
            case 10: ss << "VAX 8650";      break;
            case 11: ss << "VAX 8800";      break;
            case 12: ss << "MicroVAX III";  break;
            default: ss << "VAX (Unknown)"; break;
        }
    }
    else if( family == 6 )
    {
        switch( subType )
        {
            case 1:  ss << "Motorola 68000 (Generic)"; break;
            case 2:  ss << "Motorola 68040";           break;
            case 3:  ss << "Motorola 68030";           break;
            default: ss << "Motorola 68000 (Unknown)"; break;
        }
    }
    else if( family == 7 )
    {
        if( abi == 0x01000000 )
        {
            switch( subType )
            {
                case 3:   ss << "x86-64 (Generic)";  break;
                case 8:   ss << "x86-64 Haswell";    break;
                default:  ss << "x86-64 (Unknown)";  break;
            }
        }
        else
        {
            switch( subType )
            {
                case 3:   ss << "x86 (Generic)";            break;
                case 4:   ss << "x86 80486";                break;
                case 132: ss << "x86 80486SX";              break;
                case 5:   ss << "x86 80586 (Pentium / P5)"; break;
                case 22:  ss << "x86 Pentium Pro";          break;
                case 54:  ss << "x86 Pentium II M3 ";       break;
                case 86:  ss << "x86 Pentium II M5";        break;
                case 103: ss << "x86 Celeron";              break;
                case 119: ss << "x86 Celeron Mobile";       break;
                case 8:   ss << "x86 Pentium III";          break;
                case 24:  ss << "x86 Pentium III Mobile";   break;
                case 40:  ss << "x86 Pentium III Xeon";     break;
                case 9:   ss << "x86 Pentium M";            break;
                case 10:  ss << "x86 Pentium 4";            break;
                case 26:  ss << "x86 Pentium 4 Mobile";     break;
                case 11:  ss << "x86 Itanium";              break;
                case 27:  ss << "x86 Itanium 2";            break;
                case 12:  ss << "x86 Xeon";                 break;
                case 28:  ss << "x86 Xeon MP";              break;
                default:  ss << "x86 (Unknown)";            break;
            }
        }
    }
    else if( family == 8 )
    {
        switch( subType )
        {
            case 0:  ss << "MIPS (Generic)"; break;
            case 1:  ss << "MIPS R2300";     break;
            case 2:  ss << "MIPS R2600";     break;
            case 3:  ss << "MIPS R2800";     break;
            case 4:  ss << "MIPS R2000a";    break;
            case 5:  ss << "MIPS R2000";     break;
            case 6:  ss << "MIPS R3000a";    break;
            case 7:  ss << "MIPS R3000";     break;
            default: ss << "MIPS (Unknown)"; break;
        }
    }
    else if( family == 10 )
    {
        switch( subType )
        {
            case 0:  ss << "PowerPC MC98000 (Generic)"; break;
            case 1:  ss << "PowerPC MC98601";           break;
            default: ss << "PowerPC MC98000 (Unknown)"; break;
        }
    }
    else if( family == 11 )
    {
        switch( subType )
        {
            case 0:  ss << "HP/PA-7100";      break;
            case 2:  ss << "HP/PA-7100LC";    break;
            default: ss << "HP/PA (Unknown)"; break;
        }
    }
    else if( family == 12 )
    {
        if( abi == 0x01000000 )
        {
            switch( subType & ~0xFF000000 )
            {
                case 0:   ss << "AArch64 (Generic)"; break;
                case 1:   ss << "AArch64 Armv8-A";   break;
                case 2:   ss << "AArch64 Arm64e";    break;
                default:  ss << "AArch64 (Unknown)"; break;
            }
        }
        else if( abi == 0x02000000 )
        {
            switch( subType )
            {
                case 0:   ss << "Arm64-32 (Generic)"; break;
                case 1:   ss << "Arm64-32 Armv8-A";   break;
                default:  ss << "Arm64-32 (Unknown)"; break;
            }
        }
        else
        {
            switch( subType )
            {
                case 0:   ss << "Arm (Generic)"; break;
                default:  ss << "Arm (Unknown)"; break;
            }
        }
    }
    else if( family == 13 )
    {
        switch( subType )
        {
            case 0:  ss << "Motorola 88000 (Generic)"; break;
            case 1:  ss << "Motorola 88100";           break;
            case 2:  ss << "Motorola 88110";           break;
            default: ss << "Motorola 88000 (Unknown)"; break;
        }
    }
    else if( family == 14 )
    {
        ss << "SPARC";
    }
    else if( family == 15 )
    {
        switch( subType )
        {
            case 0:  ss << "80860 (Generic)"; break;
            case 1:  ss << "80860 i860";      break;
            default: ss << "80860 (Unknown)"; break;
        }
    }
    else if( family == 16 )
    {
        ss << "Alpha";
    }
    else if( family == 18 )
    {
        if( abi == 0x01000000 )
        {
            ss << "PowerPC-64 ";
        }
        else
        {
            ss << "PowerPC ";
        }
        
        switch( subType )
        {
            case 0:   ss << "(Generic)";  break;
            case 1:   ss << "601";        break;
            case 2:   ss << "602";        break;
            case 3:   ss << "603";        break;
            case 4:   ss << "603e";       break;
            case 5:   ss << "603ev";      break;
            case 6:   ss << "604";        break;
            case 7:   ss << "604e";       break;
            case 8:   ss << "620";        break;
            case 9:   ss << "750 (G3)";   break;
            case 10:  ss << "7400 (G4)";  break;
            case 11:  ss << "7450 (G4e)"; break;
            case 100: ss << "970 (G5)";   break;
            default:  ss << "(Unknown)";  break;
        }
    }
    else
    {
        ss << "Unknown";
    }
    
    return ss.str();
}

std::string ToString::fileType( uint32_t type )
{
    switch( type )
    {
        case 0x01: return "Object file";
        case 0x02: return "Executable";
        case 0x03: return "Fixed VM shared library";
        case 0x04: return "Core file";
        case 0x05: return "Preloaded executable";
        case 0x06: return "Dynamic library ";
        case 0x07: return "Dynamic link editor";
        case 0x08: return "Bundle";
        case 0x09: return "Shared library stub";
        case 0x0A: return "Debug Symbols";
        case 0x0B: return "Kernel extension";
        case 0x0C: return "File set";
        default:   return "Unknown";
    }
}

std::string ToString::loadCommand( uint32_t command )
{
    switch( command )
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
        
        case ( 0x18 | 0x80000000 ): return "LC_LOAD_WEAK_DYLIB";
        case ( 0x1C | 0x80000000 ): return "LC_RPATH";
        case ( 0x1F | 0x80000000 ): return "LC_REEXPORT_DYLIB";
        case ( 0x22 | 0x80000000 ): return "LC_DYLD_INFO_ONLY";
        case ( 0x23 | 0x80000000 ): return "LC_LOAD_UPWARD_DYLIB";
        case ( 0x28 | 0x80000000 ): return "LC_MAIN";
        case ( 0x33 | 0x80000000 ): return "LC_DYLD_EXPORTS_TRIE";
        case ( 0x34 | 0x80000000 ): return "LC_DYLD_CHAINED_FIXUPS";
        case ( 0x35 | 0x80000000 ): return "LC_FILESET_ENTRY";
        
        default: return "Unknown";
    }
}

std::vector< std::string > ToString::flags( uint32_t value )
{
    std::vector< std::string > flags;
    
    if( ( value & 0x00000001 ) != 0 ) { flags.push_back( "No undefined references" ); }
    if( ( value & 0x00000002 ) != 0 ) { flags.push_back( "Incremental linking" ); }
    if( ( value & 0x00000004 ) != 0 ) { flags.push_back( "Dynamic linker input" ); }
    if( ( value & 0x00000008 ) != 0 ) { flags.push_back( "Bind at load" ); }
    if( ( value & 0x00000010 ) != 0 ) { flags.push_back( "Prebound" ); }
    if( ( value & 0x00000020 ) != 0 ) { flags.push_back( "Split segments" ); }
    if( ( value & 0x00000040 ) != 0 ) { flags.push_back( "Lazy init" ); }
    if( ( value & 0x00000080 ) != 0 ) { flags.push_back( "Two level" ); }
    if( ( value & 0x00000100 ) != 0 ) { flags.push_back( "Force flat" ); }
    if( ( value & 0x00000200 ) != 0 ) { flags.push_back( "No multiple definitions" ); }
    if( ( value & 0x00000400 ) != 0 ) { flags.push_back( "No prebinding notification" ); }
    if( ( value & 0x00000800 ) != 0 ) { flags.push_back( "Can be rebound" ); }
    if( ( value & 0x00001000 ) != 0 ) { flags.push_back( "All modules bound" ); }
    if( ( value & 0x00002000 ) != 0 ) { flags.push_back( "Subsections via symbols" ); }
    if( ( value & 0x00004000 ) != 0 ) { flags.push_back( "Canonical" ); }
    if( ( value & 0x00008000 ) != 0 ) { flags.push_back( "Has weak symbols" ); }
    if( ( value & 0x00010000 ) != 0 ) { flags.push_back( "Uses weak symbols" ); }
    if( ( value & 0x00020000 ) != 0 ) { flags.push_back( "Allows stack execution" ); }
    if( ( value & 0x00040000 ) != 0 ) { flags.push_back( "Root safe" ); }
    if( ( value & 0x00080000 ) != 0 ) { flags.push_back( "SetUID safe" ); }
    if( ( value & 0x00100000 ) != 0 ) { flags.push_back( "No reexported dylibs" ); }
    if( ( value & 0x00200000 ) != 0 ) { flags.push_back( "Position independant" ); }
    if( ( value & 0x00400000 ) != 0 ) { flags.push_back( "Dead strippable" ); }
    if( ( value & 0x00800000 ) != 0 ) { flags.push_back( "Has TLV descriptors" ); }
    if( ( value & 0x01000000 ) != 0 ) { flags.push_back( "No heap execution" ); }
    if( ( value & 0x02000000 ) != 0 ) { flags.push_back( "App extension safe" ); }
    if( ( value & 0x04000000 ) != 0 ) { flags.push_back( "Out of sync symbols" ); }
    if( ( value & 0x08000000 ) != 0 ) { flags.push_back( "Simulator support" ); }
    if( ( value & 0x80000000 ) != 0 ) { flags.push_back( "In shared cache" ); }
    
    return flags;
}
