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
        
        bool        _showHelp;
        std::string _exec;
        std::string _file;
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

bool Arguments::showHelp() const
{
    return this->impl->_showHelp;
}

std::string Arguments::exec() const
{
    return this->impl->_exec;
}

std::string Arguments::file() const
{
    return this->impl->_file;
}

void swap( Arguments & o1, Arguments & o2 )
{
    using std::swap;
    
    swap( o1.impl, o2.impl );
}

Arguments::IMPL::IMPL( int argc, char ** argv ):
    _showHelp( false )
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
            
            if( arg == "--help" || arg == "-h" )
            {
                this->_showHelp = true;
            }
            else if( this->_file.length() == 0 )
            {
                this->_file = arg;
            }
        }
    }
}

Arguments::IMPL::IMPL( const IMPL & o ):
    _showHelp( o._showHelp ),
    _exec(     o._exec ),
    _file(     o._file )
{}

Arguments::IMPL::~IMPL()
{}
