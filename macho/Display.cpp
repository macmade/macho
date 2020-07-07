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

class Display::IMPL
{
    public:
        
        IMPL( const Arguments & args );
        IMPL( const IMPL & o );
        ~IMPL();
        
        Arguments _args;
};

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

Display::Display( const Arguments & args ):
    impl( std::make_unique< IMPL >( args ) )
{}

Display::Display( const Display & o ):
    impl( std::make_unique< IMPL >( *( o.impl ) ) )
{}

Display::Display( Display && o ) noexcept:
    impl( std::move( o.impl ) )
{}

Display::~Display()
{}

Display & Display::operator =( Display o )
{
    swap( *( this ), o );
    
    return *( this );
}

void Display::operator()( const MachO::FATFile & file ) const
{
    std::cout << file << std::endl;
}

void Display::operator()( const MachO::File & file ) const
{
    std::cout << file << std::endl;
}

void Display::operator()( const MachO::CacheFile & file ) const
{
    std::cout << file << std::endl;
}
    
void swap( Display & o1, Display & o2 )
{
    using std::swap;
    
    swap( o1.impl, o2.impl );
}

Display::IMPL::IMPL( const Arguments & args ):
    _args( args )
{}

Display::IMPL::IMPL( const IMPL & o ):
    _args( o._args )
{}

Display::IMPL::~IMPL()
{}
