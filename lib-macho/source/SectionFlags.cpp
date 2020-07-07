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
 * @file        SectionFlags.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/SectionFlags.hpp>
#include <MachO/ToString.hpp>

namespace MachO
{
    XS::Info SectionFlags::getInfo() const
    {
        XS::Info i( "Flags", this->type() );
        
        for( const auto & attribute: this->attributes() )
        {
            i.addChild( attribute );
        }
        
        return i;
    }
    
    std::string SectionFlags::type() const
    {
        uint32_t value( this->value() & 0xFF );
        
        switch( value )
        {
            case 0x00: return "S_REGULAR";
            case 0x01: return "S_ZEROFILL";
            case 0x02: return "S_CSTRING_LITERALS";
            case 0x03: return "S_4BYTE_LITERALS";
            case 0x04: return "S_8BYTE_LITERALS";
            case 0x05: return "S_LITERAL_POINTERS";
            case 0x06: return "S_NON_LAZY_SYMBOL_POINTERS";
            case 0x07: return "S_LAZY_SYMBOL_POINTERS";
            case 0x08: return "S_SYMBOL_STUBS";
            case 0x09: return "S_MOD_INIT_FUNC_POINTERS";
            case 0x0A: return "S_MOD_TERM_FUNC_POINTERS";
            case 0x0B: return "S_COALESCED";
            case 0x0C: return "S_GB_ZEROFILL";
            case 0x0D: return "S_INTERPOSING";
            case 0x0E: return "S_16BYTE_LITERALS";
            case 0x0F: return "S_DTRACE_DOF";
            case 0x10: return "S_LAZY_DYLIB_SYMBOL_POINTERS";
            case 0x11: return "S_THREAD_LOCAL_REGULAR";
            case 0x12: return "S_THREAD_LOCAL_ZEROFILL";
            case 0x13: return "S_THREAD_LOCAL_VARIABLES";
            case 0x14: return "S_THREAD_LOCAL_VARIABLE_POINTERS";
            case 0x15: return "S_THREAD_LOCAL_INIT_FUNCTION_POINTERS";
            case 0x16: return "S_INIT_FUNC_OFFSETS";
            default:   return "Unknown (" + XS::ToString::Hex( value ) + ")";
        }
    }
    
    std::vector< std::string > SectionFlags::attributes() const
    {
        uint32_t                   value( this->value() );
        std::vector< std::string > attributes;
        
        if( ( value & 0x80000000 ) != 0 ) { attributes.push_back( "S_ATTR_PURE_INSTRUCTIONS" ); }
        if( ( value & 0x40000000 ) != 0 ) { attributes.push_back( "S_ATTR_NO_TOC" ); }
        if( ( value & 0x20000000 ) != 0 ) { attributes.push_back( "S_ATTR_STRIP_STATIC_SYMS" ); }
        if( ( value & 0x10000000 ) != 0 ) { attributes.push_back( "S_ATTR_NO_DEAD_STRIP" ); }
        if( ( value & 0x08000000 ) != 0 ) { attributes.push_back( "S_ATTR_LIVE_SUPPORT" ); }
        if( ( value & 0x04000000 ) != 0 ) { attributes.push_back( "S_ATTR_SELF_MODIFYING_CODE" ); }
        if( ( value & 0x02000000 ) != 0 ) { attributes.push_back( "S_ATTR_DEBUG" ); }
        if( ( value & 0x00000400 ) != 0 ) { attributes.push_back( "S_ATTR_SOME_INSTRUCTIONS" ); }
        if( ( value & 0x00000200 ) != 0 ) { attributes.push_back( "S_ATTR_EXT_RELOC" ); }
        if( ( value & 0x00000100 ) != 0 ) { attributes.push_back( "S_ATTR_LOC_RELOC" ); }
        
        return attributes;
    }
}
