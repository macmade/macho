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
 * @file        Display.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include "Display.hpp"
#include "ToString.hpp"
#include <MachO.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

void Display::error( const std::exception & e )
{
    std::cerr << "Error: " << e.what() << std::endl;
}

void Display::help()
{
    std::cout << "Usage: macho [OPTIONS] [PATH]\n"
                 "\n"
                 "Options:\n"
                 "\n"
                 "    --help    Shows this help dialog."
              << std::endl;
}

void Display::operator()( const MachO::FATFile & file ) const
{
    auto archs( file.architectures() );
    
    if( archs.size() == 0 )
    {
        throw std::runtime_error( "FAT Mach-O file does not contain any architecture" );
    }
    
    std::cout << "Architectures in FAT Mach-O file:\n\n";
    
    for( const auto & p: archs )
    {
        std::cout << "    - "
                  << ToString::cpu( p.second.cpuType(), p.second.cpuSubType() )
                  << " - "
                  << ToString::size( p.first.size() )
                  << " - "
                  << ToString::hex( p.first.cpuType() )
                  << ":"
                  << ToString::hex( p.first.cpuSubType() )
                  << "\n";
    }
    
    std::cout << std::endl;
    
    for( const auto & p: archs )
    {
        this->operator()( p.second );
    }
}

void Display::operator()( const MachO::File & file ) const
{
    std::cout << ToString::cpu( file.cpuType(), file.cpuSubType() )
              << " - "
              << ToString::hex( file.cpuType() )
              << ":"
              << ToString::hex( file.cpuSubType() )
              << ":\n\n"
              << "    - Type:          " << ToString::fileType( file.type() ) << "\n"
              << "    - Load commands: " << file.loadCommands().size()        << "\n"
              << "    - Flags:         0x" << ToString::hex( file.flags() )   << "\n";
    
    if( file.flags() != 0 )
    {
        std::cout << "\n    Flags:\n";
        
        for( const auto & flag: ToString::flags( file.flags() ) )
        {
            std::cout << "        - " << flag << "\n";
        }
    }
    
    if( file.loadCommands().size() != 0 )
    {
        std::vector< MachO::LoadCommands::LoadDylib > dylibs;
        
        std::cout << "\n    Load commands:\n";
        
        for( const auto & ref: file.loadCommands() )
        {
            MachO::LoadCommand & command( ref.get() );
            
            std::cout << "        - "
                      << ToString::loadCommand( command.command() )
                      << " - "
                      << ToString::size( command.size() )
                      << "\n";
            
            try
            {
                MachO::LoadCommands::LoadDylib & dylib( dynamic_cast< MachO::LoadCommands::LoadDylib & >( command ) );
                
                dylibs.push_back( dylib );
            }
            catch( ... )
            {}
        }
        
        if( dylibs.size() > 0 )
        {
            std::cout << "\n    Dynamic libraries:\n";
            
            for( const auto & dylib: dylibs )
            {
                std::cout << "        - \n";
                
                ( void )dylib;
            }
        }
    }
    
    std::cout << std::endl;
}
