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

MachO::Info Arguments::getInfo() const
{
    MachO::Info i( "Arguments" );
    MachO::Info files( "Files" );
    
    i.addChild( { "Help", std::to_string( this->showHelp() ) } );
    i.addChild( { "Info", std::to_string( this->showInfo() ) } );
    i.addChild( { "Libs", std::to_string( this->showLibs() ) } );
    
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
    _showHelp( false ),
    _showInfo( false ),
    _showLibs( false )
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
            
                 if( arg == "--help" ) { this->_showHelp = true; }
            else if( arg == "--info" ) { this->_showInfo = true; }
            else if( arg == "--libs" ) { this->_showLibs = true; }
            else if( arg[ 0 ] == '-' )
            {
                for( auto c: arg.substr( 1 ) )
                {
                    if( c == 'h' ) { this->_showHelp = true; }
                    if( c == 'i' ) { this->_showInfo = true; }
                    if( c == 'l' ) { this->_showLibs = true; }
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
    _showHelp( o._showHelp ),
    _showInfo( o._showInfo ),
    _showLibs( o._showLibs ),
    _exec(     o._exec ),
    _files(    o._files )
{}

Arguments::IMPL::~IMPL()
{}
