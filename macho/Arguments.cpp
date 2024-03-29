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
 * @file        Arguments.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include "Arguments.hpp"

class Arguments::IMPL
{
    public:
        
        IMPL( int argc, char ** argv );
        IMPL( const IMPL & o );
        ~IMPL();
        
        bool                       _showHelp;
        bool                       _showInfo;
        bool                       _showLibs;
        bool                       _showSymbols;
        bool                       _showStrings;
        bool                       _showObjcClasses;
        bool                       _showObjcMethods;
        bool                       _showData;
        std::string                _exec;
        std::vector< std::string > _files;
};

Arguments::Arguments( int argc, char ** argv ):
    impl( std::make_unique< IMPL >( argc, argv ) )
{}

Arguments::Arguments( const Arguments & o ):
    impl( std::make_unique< IMPL >( *( o.impl ) ) )
{}

Arguments::Arguments( Arguments && o ) noexcept:
    impl( std::move( o.impl ) )
{}

Arguments::~Arguments()
{}

Arguments & Arguments::operator =( Arguments o )
{
    swap( *( this ), o );
    
    return *( this );
}

XS::Info Arguments::getInfo() const
{
    XS::Info i( "Arguments" );
    XS::Info files( "Files" );
    
    i.addChild( { "Help",                std::to_string( this->showHelp() ) } );
    i.addChild( { "Info",                std::to_string( this->showInfo() ) } );
    i.addChild( { "Libs",                std::to_string( this->showLibs() ) } );
    i.addChild( { "Symbols",             std::to_string( this->showSymbols() ) } );
    i.addChild( { "Strings",             std::to_string( this->showStrings() ) } );
    i.addChild( { "Objective-C classes", std::to_string( this->showObjcClasses() ) } );
    i.addChild( { "Objective-C methods", std::to_string( this->showObjcMethods() ) } );
    i.addChild( { "Data",                std::to_string( this->showData() ) } );

    for( const auto & file: this->files() )
    {
        files.addChild( file );
    }
    
    if( this->files().size() > 0 )
    {
        files.value( std::to_string( this->files().size() ) );
        i.addChild( files );
    }
    
    return i;
}

bool Arguments::showHelp() const
{
    return this->impl->_showHelp;
}

bool Arguments::showInfo() const
{
    return this->impl->_showInfo;
}

bool Arguments::showLibs() const
{
    return this->impl->_showLibs;
}

bool Arguments::showSymbols() const
{
    return this->impl->_showSymbols;
}

bool Arguments::showStrings() const
{
    return this->impl->_showStrings;
}

bool Arguments::showObjcClasses() const
{
    return this->impl->_showObjcClasses;
}

bool Arguments::showObjcMethods() const
{
    return this->impl->_showObjcMethods;
}

bool Arguments::showData() const
{
    return this->impl->_showData;
}

std::string Arguments::exec() const
{
    return this->impl->_exec;
}

std::vector< std::string > Arguments::files() const
{
    return this->impl->_files;
}

void swap( Arguments & o1, Arguments & o2 )
{
    using std::swap;
    
    swap( o1.impl, o2.impl );
}

Arguments::IMPL::IMPL( int argc, char ** argv ):
    _showHelp(        false ),
    _showInfo(        false ),
    _showLibs(        false ),
    _showSymbols(     false ),
    _showStrings(     false ),
    _showObjcClasses( false ),
    _showObjcMethods( false ),
    _showData(        false )
{
    if( argc == 0 || argv == nullptr )
    {
        return;
    }
    
    this->_exec = argv[ 0 ];
    
    for( int i = 1; i < argc; i++ )
    {
        if( argv[ i ] == nullptr )
        {
            continue;
        }
        
        {
            std::string arg( argv[ i ] );
            
            if( arg.size() == 0 )
            {
                continue;
            }
            
                 if( arg == "--help"        ) { this->_showHelp        = true; }
            else if( arg == "--info"        ) { this->_showInfo        = true; }
            else if( arg == "--libs"        ) { this->_showLibs        = true; }
            else if( arg == "--symbols"     ) { this->_showSymbols     = true; }
            else if( arg == "--str"         ) { this->_showStrings     = true; }
            else if( arg == "--objc-class"  ) { this->_showObjcClasses = true; }
            else if( arg == "--objc-method" ) { this->_showObjcMethods = true; }
            else if( arg == "--data"        ) { this->_showData        = true; }
            else if( arg[ 0 ] == '-' )
            {
                for( auto c: arg.substr( 1 ) )
                {
                    if( c == 'h' ) { this->_showHelp        = true; }
                    if( c == 'i' ) { this->_showInfo        = true; }
                    if( c == 'l' ) { this->_showLibs        = true; }
                    if( c == 'f' ) { this->_showSymbols     = true; }
                    if( c == 's' ) { this->_showStrings     = true; }
                    if( c == 'c' ) { this->_showObjcClasses = true; }
                    if( c == 'm' ) { this->_showObjcMethods = true; }
                    if( c == 'd' ) { this->_showData        = true; }
                }
            }
            else
            {
                this->_files.push_back( arg );
            }
        }
    }
}

Arguments::IMPL::IMPL( const IMPL & o ):
    _showHelp(        o._showHelp ),
    _showInfo(        o._showInfo ),
    _showLibs(        o._showLibs ),
    _showSymbols(     o._showSymbols ),
    _showStrings(     o._showStrings ),
    _showObjcClasses( o._showObjcClasses ),
    _showObjcMethods( o._showObjcMethods ),
    _showData(        o._showData ),
    _exec(            o._exec ),
    _files(           o._files )
{}

Arguments::IMPL::~IMPL()
{}
