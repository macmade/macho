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
 * @file        FileFlags.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/FileFlags.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    XS::Info FileFlags::getInfo() const
    {
        XS::Info i( "Flags" );
        auto     flags( this->flags() );
        
        if( flags.size() > 0 )
        {
            i.value( XS::ToString::Hex( this->value() ) );
            
            for( const auto & p: flags )
            {
                i.addChild( { p.first, p.second } );
            }
        }
        else
        {
            i.value( "--" );
        }
        
        return i;
    }
    
    std::vector< std::pair< std::string, std::string > > FileFlags::flags() const
    {
        std::vector< std::pair< std::string, std::string > > flags;
        uint32_t                                             value( this->value() );
        
        if( ( value & 0x00000001 ) != 0 ) { flags.push_back( { "MH_NOUNDEFS",                      "No undefined references" } ); }
        if( ( value & 0x00000002 ) != 0 ) { flags.push_back( { "MH_INCRLINK",                      "Output of an incremental link" } ); }
        if( ( value & 0x00000004 ) != 0 ) { flags.push_back( { "MH_DYLDLINK",                      "Input for the dynamic linker" } ); }
        if( ( value & 0x00000008 ) != 0 ) { flags.push_back( { "MH_BINDATLOAD",                    "Undefined references are bound by the dynamic linker" } ); }
        if( ( value & 0x00000010 ) != 0 ) { flags.push_back( { "MH_PREBOUND",                      "Dynamic undefined references are prebound" } ); }
        if( ( value & 0x00000020 ) != 0 ) { flags.push_back( { "MH_SPLIT_SEGS",                    "Read-only and read-write segments are split" } ); }
        if( ( value & 0x00000040 ) != 0 ) { flags.push_back( { "MH_LAZY_INIT",                     "The init routine is to be run lazily via catching memory faults" } ); }
        if( ( value & 0x00000080 ) != 0 ) { flags.push_back( { "MH_TWOLEVEL",                      "Using two-level name space bindings" } ); }
        if( ( value & 0x00000100 ) != 0 ) { flags.push_back( { "MH_FORCE_FLAT",                    "Forcing all images to use flat name space bindings" } ); }
        if( ( value & 0x00000200 ) != 0 ) { flags.push_back( { "MH_NOMULTIDEFS",                   "No multiple defintions of symbols in sub-images" } ); }
        if( ( value & 0x00000400 ) != 0 ) { flags.push_back( { "MH_NOFIXPREBINDING",               "No notification to the prebinding agent" } ); }
        if( ( value & 0x00000800 ) != 0 ) { flags.push_back( { "MH_PREBINDABLE",                   "Not prebound - Can have prebindings redone" } ); }
        if( ( value & 0x00001000 ) != 0 ) { flags.push_back( { "MH_ALLMODSBOUND",                  "Binds to all two-level namespace modules of the dependent libraries" } ); } 
        if( ( value & 0x00002000 ) != 0 ) { flags.push_back( { "MH_SUBSECTIONS_VIA_SYMBOLS",       "Safe to divide up the sections for dead code stripping" } ); }
        if( ( value & 0x00004000 ) != 0 ) { flags.push_back( { "MH_CANONICAL",                     "Canonicalized via the unprebind operation" } ); }
        if( ( value & 0x00008000 ) != 0 ) { flags.push_back( { "MH_WEAK_DEFINES",                  "Contains external weak symbols" } ); }
        if( ( value & 0x00010000 ) != 0 ) { flags.push_back( { "MH_BINDS_TO_WEAK",                 "Uses weak symbols" } ); }
        if( ( value & 0x00020000 ) != 0 ) { flags.push_back( { "MH_ALLOW_STACK_EXECUTION",         "Allows stack execution" } ); }
        if( ( value & 0x00040000 ) != 0 ) { flags.push_back( { "MH_ROOT_SAFE",                     "Safe for use in processes with uid zero" } ); }
        if( ( value & 0x00080000 ) != 0 ) { flags.push_back( { "MH_SETUID_SAFE",                   "Safe for use in processes when issetugid() is true" } ); }
        if( ( value & 0x00100000 ) != 0 ) { flags.push_back( { "MH_NO_REEXPORTED_DYLIBS",          "No need to check for re-exported dependent dylibs" } ); }
        if( ( value & 0x00200000 ) != 0 ) { flags.push_back( { "MH_PIE",                           "Main executable is loaded at a random address" } ); }
        if( ( value & 0x00400000 ) != 0 ) { flags.push_back( { "MH_DEAD_STRIPPABLE_DYLIB",         "Don't load if no symbols are being referenced from the dylib" } ); }
        if( ( value & 0x00800000 ) != 0 ) { flags.push_back( { "MH_HAS_TLV_DESCRIPTORS",           "Contains a thread local variables section" } ); }
        if( ( value & 0x00100000 ) != 0 ) { flags.push_back( { "MH_NO_HEAP_EXECUTION",             "Forces a non-executable heap in the main executable" } ); }
        if( ( value & 0x02000000 ) != 0 ) { flags.push_back( { "MH_APP_EXTENSION_SAFE",            "Can be used in application extensions" } ); }
        if( ( value & 0x04000000 ) != 0 ) { flags.push_back( { "MH_NLIST_OUTOFSYNC_WITH_DYLDINFO", "External symbols do not include all the symbols in the dyld info" } ); }
        if( ( value & 0x08000000 ) != 0 ) { flags.push_back( { "MH_SIM_SUPPORT",                   "Allows simulator support" } ); }
        if( ( value & 0x80000000 ) != 0 ) { flags.push_back( { "MH_DYLIB_IN_CACHE",                "Part of the dyld shared cache" } ); }
        
        return flags;
    }
}
