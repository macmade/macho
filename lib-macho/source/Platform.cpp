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
 * @file        Platform.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/Platform.hpp>

namespace MachO
{
    XS::Info Platform::getInfo() const
    {
        std::string platform;
        
        switch( this->value() )
        {
            case  1: platform = "macOS";             break;
            case  2: platform = "iOS";               break;
            case  3: platform = "tvOS";              break;
            case  4: platform = "watchOS";           break;
            case  5: platform = "BridgeOS";          break;
            case  6: platform = "Mac Catalyst";      break;
            case  7: platform = "iOS Simulator";     break;
            case  8: platform = "tvOS Simulator";    break;
            case  9: platform = "watchOS Simulator"; break;
            case 10: platform = "DriverKit";         break;
            default: platform = "Unknown";           break;
        }
        
        return { "Platform", platform };
    }
}
