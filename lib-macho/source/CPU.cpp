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
 * @file        CPU.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/CPU.hpp>

namespace MachO
{
    class CPU::IMPL
    {
        public:
            
            IMPL( uint32_t type, uint32_t subType );
            IMPL( const IMPL & o );
            ~IMPL();
            
            uint32_t _type;
            uint32_t _subType;
    };
    
    CPU::CPU():
        CPU( 0, 0 )
    {}
    
    CPU::CPU( uint32_t type, uint32_t subType ):
        impl( std::make_unique< IMPL >( type, subType ) )
    {}
    
    CPU::CPU( const CPU & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    CPU::CPU( CPU && o ) noexcept:
        impl( std::move( o.impl ) )
    {}

    CPU::~CPU()
    {}

    CPU & CPU::operator =( CPU o )
    {
        swap( *( this ), o );
        
        return *( this );
    }
    
    uint32_t CPU::type() const
    {
        return this->impl->_type;
    }
    
    uint32_t CPU::subType() const
    {
        return this->impl->_subType;
    }
    
    std::string CPU::typeString() const
    {
        uint32_t abi(  this->type() &  0xFF000000 );
        uint32_t type( this->type() & ~0xFF000000 );
        
        switch( type )
        {
            case  1: return "DEC VAX";
            case  6: return "Motorola 68k";
            case  7: return ( abi == 0x01000000 ) ? "x86-64" : "x86";
            case  8: return "MIPS";
            case 10: return "PowerPC MC98000";
            case 11: return "HP/PA";
            case 12: return ( abi == 0x01000000 ) ? "AArch64" : ( abi == 0x02000000 ) ? "Arm64-32" : "Arm";
            case 13: return "Motorola 88k";
            case 14: return "SPARC";
            case 15: return "80860";
            case 16: return "Alpha";
            case 18: return ( abi == 0x01000000 ) ? "PowerPC-64" : "PowerPC";
            default: return "Unknown";
        }
    }
    
    std::string CPU::subTypeString() const
    {
        uint32_t abi(  this->type() &  0xFF000000 );
        uint32_t type( this->type() & ~0xFF000000 );
        
        switch( type )
        {
            case 1:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    case 1:  return "11/780";
                    case 2:  return "11/785";
                    case 3:  return "11/750";
                    case 4:  return "11/730";
                    case 5:  return "MicroVAX I";
                    case 6:  return "MicroVAX II";
                    case 7:  return "8200";
                    case 8:  return "8500";
                    case 9:  return "8600";
                    case 10: return "8650";
                    case 11: return "8800";
                    case 12: return "MicroVAX III";
                    default: return "Unknown";
                }
                
            case 6:
                
                switch( this->subType() )
                {
                    case 1:  return "Generic";
                    case 2:  return "68040";
                    case 3:  return "68030";
                    default: return "Unknown";
                }
            
            case 7:
                
                if( abi == 0x01000000 )
                {
                    switch( this->subType() )
                    {
                        case 3:   return "Generic";
                        case 8:   return "Haswell";
                        default:  return "Unknown";
                    }
                }
                else
                {
                    switch( this->subType() )
                    {
                        case 3:   return "Generic";
                        case 4:   return "80486";
                        case 132: return "80486SX";
                        case 5:   return "80586 (Pentium / P5)";
                        case 22:  return "Pentium Pro";
                        case 54:  return "Pentium II M3 ";
                        case 86:  return "Pentium II M5";
                        case 103: return "Celeron";
                        case 119: return "Celeron Mobile";
                        case 8:   return "Pentium III";
                        case 24:  return "Pentium III Mobile";
                        case 40:  return "Pentium III Xeon";
                        case 9:   return "Pentium M";
                        case 10:  return "Pentium 4";
                        case 26:  return "Pentium 4 Mobile";
                        case 11:  return "Itanium";
                        case 27:  return "Itanium 2";
                        case 12:  return "Xeon";
                        case 28:  return "Xeon MP";
                        default:  return "Unknown";
                    }
                }
                
            case 8:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    case 1:  return "R2300";
                    case 2:  return "R2600";
                    case 3:  return "R2800";
                    case 4:  return "R2000a";
                    case 5:  return "R2000";
                    case 6:  return "R3000a";
                    case 7:  return "R3000";
                    default: return "Unknown";
                }
                
            case 10:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    case 1:  return "MC98601";
                    default: return "Unknown";
                }
                
            case 11:
                
                switch( this->subType() )
                {
                    case 0:  return "7100";
                    case 2:  return "7100LC";
                    default: return "Unknown";
                }
                
            case 12:
                
                if( abi == 0x01000000 )
                {
                    switch( this->subType() & ~0xFF000000 )
                    {
                        case 0:   return "Generic";
                        case 1:   return "Armv8-A";
                        case 2:   return "Arm64e";
                        default:  return "Unknown";
                    }
                }
                else if( abi == 0x02000000 )
                {
                    switch( this->subType() )
                    {
                        case 0:   return "Generic";
                        case 1:   return "Armv8-A";
                        default:  return "Unknown";
                    }
                }
                else
                {
                    switch( this->subType() )
                    {
                        case 0:   return "Generic";
                        default:  return "Unknown";
                    }
                }
                
            case 13:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    case 1:  return "88100";
                    case 2:  return "88110";
                    default: return "Unknown";
                }
                
            case 14:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    default: return "Unknown";
                }
                
            case 15:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    case 1:  return "i860";
                    default: return "Unknown";
                }
                
            case 16:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    default: return "Unknown";
                }
                
            case 18:
                
                switch( this->subType() )
                {
                    case 0:   return "(Generic)";
                    case 1:   return "601";
                    case 2:   return "602";
                    case 3:   return "603";
                    case 4:   return "603e";
                    case 5:   return "603ev";
                    case 6:   return "604";
                    case 7:   return "604e";
                    case 8:   return "620";
                    case 9:   return "750 (G3)";
                    case 10:  return "7400 (G4)";
                    case 11:  return "7450 (G4e)";
                    case 100: return "970 (G5)";
                    default:  return "(Unknown)";
                }
                
            default:
                
                switch( this->subType() )
                {
                    case 0:  return "Generic";
                    default: return "Unknown";
                }
        }
    }
    
    std::string CPU::description() const
    {
        return this->typeString() + " - " + this->subTypeString();
    }
    
    void swap( CPU & o1, CPU & o2 )
    {
        using std::swap;
        
        swap( o1.impl, o2.impl );
    }
    
    CPU::IMPL::IMPL( uint32_t type, uint32_t subType ):
        _type(    type ),
        _subType( subType )
    {}
    
    CPU::IMPL::IMPL( const IMPL & o ):
        _type(        o._type ),
        _subType(     o._subType )
    {}
    
    CPU::IMPL::~IMPL()
    {}
}
