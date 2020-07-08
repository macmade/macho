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
#include <cctype>
#include <XS.hpp>

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
                     "    -h / --help     Shows this help dialog.\n"
                     "    -i / --info     Prints a complete info dump.\n"
                     "    -l / --libs     Prints the list of linked libraries.\n"
                     "    -s / --str      Prints the list of strings.\n"
                     "    -c / --objc-cls Prints the list of Objective-C classes."
                  << std::endl;
    }

    XS::Info FileInfo( const MachO::File & file, const Arguments & args )
    {
        XS::Info i( file.getInfo() );
        
        if( args.showInfo() == false )
        {
            i.removeLevel( 2 );
        }
        
        if( args.showLibs() )
        {
            XS::Info libs( "Libraries" );
            
            for( const auto & lib: file.linkedLibraries() )
            {
                libs.addChild( XS::ToString::Filename( lib ) );
            }
            
            libs.value( std::to_string( libs.children().size() ) );
            i.addChild( libs );
        }
        
        if( args.showStrings() )
        {
            XS::Info strings( "Strings" );
            
            for( auto str: file.strings() )
            {
                str = XS::String::ReplaceAll( str, "\r",     "\\r" );
                str = XS::String::ReplaceAll( str, "\n",     "\\n" );
                str = XS::String::ReplaceAll( str, "\u2029", "\uFFFD" );
                
                strings.addChild( "\"" + str + "\"" );
            }
            
            strings.value( std::to_string( strings.children().size() ) );
            i.addChild( strings );
        }
        
        if( args.showObjcClasses() )
        {
            XS::Info classes( "Classes" );
            
            for( auto cls: file.objcClasses() )
            {
                classes.addChild( cls );
            }
            
            classes.value( std::to_string( classes.children().size() ) );
            i.addChild( classes );
        }
        
        return i;
    }
    
    XS::Info FileInfo( const MachO::FatFile & file, const Arguments & args )
    {
        XS::Info                i( file.getInfo() );
        std::vector< XS::Info > children;
        
        if( i.children().size() > 0 )
        {
            children.push_back( i.children()[ 0 ] );
            
            for( const auto & p: file.architectures() )
            {
                children.push_back( FileInfo( p.second, args ) );
            }
            
            i.children( children );
        }
        
        return i;
    }
    
    XS::Info FileInfo( const MachO::CacheFile & file, const Arguments & args )
    {
        XS::Info i( file.getInfo() );
        
        if( args.showInfo() == false )
        {
            i.children( {} );
            
            for( const auto & image: file.images() )
            {
                i.addChild( XS::ToString::Filename( image.path() ) );
            }
        }
        
        return i;
    }
    
    void File( const MachO::File & file, const Arguments & args )
    {
        std::cout << FileInfo( file, args ) << std::endl;
    }
    
    void File( const MachO::FatFile & file, const Arguments & args )
    {
        std::cout << FileInfo( file, args ) << std::endl;
    }
    
    void File( const MachO::CacheFile & file, const Arguments & args )
    {
        std::cout << FileInfo( file, args ) << std::endl;
    }
}
