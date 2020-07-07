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

namespace Display
{
    void Error( const std::exception & e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    void Help()
    {
        std::cout << "Usage: macho [OPTIONS] [PATH] ...\n"
                     "\n"
                     "Options:\n"
                     "\n"
                     "    -h / --help    Shows this help dialog.\n"
                     "    -i / --info    Prints a complete info dump.\n"
                     "    -l / --libs    Prints the list of linked libraries."
                  << std::endl;
    }

    void File( const MachO::File & file )
    {
        XS::Info i( "Mach-O file", XS::ToString::Filename( file.path().value_or( "" ) ) );
        
        i.addChild( file.cpu() );
        
        std::cout << i << std::endl;
    }
    
    void File( const MachO::FatFile & file )
    {
        XS::Info i( "Fat Mach-O file", XS::ToString::Filename( file.path().value_or( "" ) ) );
        
        for( const auto & p: file.architectures() )
        {
            i.addChild( p.first );
        }
        
        std::cout << i << std::endl;
    }
    
    void File( const MachO::CacheFile & file )
    {
        XS::Info i( "Dyld cache file", XS::ToString::Filename( file.path().value_or( "" ) ) );
        
        for( const auto & image: file.images() )
        {
            i.addChild( XS::ToString::Filename( image.path() ) );
        }
        
        std::cout << i << std::endl;
    }
    
    void Libs( const MachO::File & file )
    {
        XS::Info i( "Mach-O file", XS::ToString::Filename( file.path().value_or( "" ) ) );
        XS::Info libs( "Libraries" );
        
        for( const auto & command: file.loadCommands() )
        {
            try
            {
                MachO::LoadCommands::Dylib & lib( dynamic_cast< MachO::LoadCommands::Dylib & >( command.get() ) );
                
                libs.addChild( XS::ToString::Filename( lib.name() ) );
            }
            catch( ... )
            {}
        }
        
        i.addChild( file.cpu() );
        i.addChild( libs );
        
        std::cout << i << std::endl;
    }
    
    void Libs( const MachO::FatFile & file )
    {
        XS::Info i( "Fat Mach-O file", XS::ToString::Filename( file.path().value_or( "" ) ) );
        
        for( const auto & p: file.architectures() )
        {
            XS::Info libs( "Libraries" );
            
            for( const auto & command: p.second.loadCommands() )
            {
                try
                {
                    MachO::LoadCommands::Dylib & lib( dynamic_cast< MachO::LoadCommands::Dylib & >( command.get() ) );
                    
                    libs.addChild( XS::ToString::Filename( lib.name() ) );
                }
                catch( ... )
                {}
            }
            
            i.addChild( p.first );
            i.addChild( libs );
        }
        
        std::cout << i << std::endl;
    }
    
    void Libs( const MachO::CacheFile & file )
    {
        File( file );
    }

    void Info( const MachO::File & file )
    {
        std::cout << file << std::endl;
    }

    void Info( const MachO::FatFile & file )
    {
        std::cout << file << std::endl;
    }

    void Info( const MachO::CacheFile & file )
    {
        std::cout << file << std::endl;
    }
}
