macho
=====

[![Build Status](https://img.shields.io/travis/macmade/macho.svg?branch=master&style=flat)](https://travis-ci.org/macmade/macho)
[![Coverage Status](https://img.shields.io/coveralls/macmade/macho.svg?branch=master&style=flat)](https://coveralls.io/r/macmade/macho?branch=master)
[![Issues](http://img.shields.io/github/issues/macmade/macho.svg?style=flat)](https://github.com/macmade/macho/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)
![License](https://img.shields.io/badge/license-mit-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)  
[![Donate-Patreon](https://img.shields.io/badge/donate-patreon-yellow.svg?style=flat)](https://patreon.com/macmade)
[![Donate-Gratipay](https://img.shields.io/badge/donate-gratipay-yellow.svg?style=flat)](https://www.gratipay.com/macmade)
[![Donate-Paypal](https://img.shields.io/badge/donate-paypal-yellow.svg?style=flat)](https://paypal.me/xslabs)

About
-----

Mach-O file parser.

### Installation

    brew install --HEAD macmade/macho

### Example output

    $ macho /System/Library/Frameworks/Foundation.framework/Foundation
    
    Mach-O file:
    {
        CPU:       x86-64 - Generic
        Type:      MH_DYLIB - Dynamically bound shared library
        Flags:     0x02000085
        {
            MH_NOUNDEFS:           No undefined references
            MH_DYLDLINK:           Input for the dynamic linker
            MH_TWOLEVEL:           Using two-level name space bindings
            MH_APP_EXTENSION_SAFE: Can be used in application extensions
        }
        Commands:  33
        {
            LC_SEGMENT_64:
            {
                Name:        __TEXT
                VM address:  0x0000000000000000
                VM size:     3.96 MB
                File offset: 0x0000000000000000
                File size:   3.96 MB
                Max prot:    0x00000005
                Init prot:   0x00000005
                Sections:    20
                Flags:       0x00000000
            }
            LC_SEGMENT_64:
            {
                Name:        __DATA
                VM address:  0x00000000003C6000
                VM size:     1.04 MB
                File offset: 0x00000000003C6000
                File size:   1.04 MB
                Max prot:    0x00000003
                Init prot:   0x00000003
                Sections:    26
                Flags:       0x00000000
            }
            LC_SEGMENT_64:
            {
                Name:        __LINKEDIT
                VM address:  0x00000000004C5000
                VM size:     2.41 MB
                File offset: 0x00000000004C4000
                File size:   2.41 MB
                Max prot:    0x00000001
                Init prot:   0x00000001
                Sections:    0
                Flags:       0x00000000
            }
            LC_ID_DYLIB:           Foundation
            LC_DYLD_INFO_ONLY:
            {
                Rebase offset:       0x004C4000
                Rebase size:         0x000060A0
                Binding offset:      0x004CA0A0
                Binding size:        0x00003DE0
                Weak binding offset: 0x00000000
                Weak binding size:   0x00000000
                Lazy binding offset: 0x004CDE80
                Lazy binding size:   0x0000C4B0
                Export offset:       0x004DA330
                Export size:         0x000167F0
            }
            LC_SYMTAB:
            {
                Symbol offset: 0x00518DB0
                Symbol size:   0x00008439
                String offset: 0x005A0994
                String size:   0x0015D508
            }
            LC_DYSYMTAB:
            {
                Symbol offset: 0x00000000
                Symbol size:   0x00006FE4
                String offset: 0x00006FE4
                String size:   0x00000B7F
            }
            LC_UUID:               1FA28BAB-7296-3A9-8E1E-E62A7D233DB8
            LC_BUILD_VERSION:
            {
                Platform: macOS
                Min OS:   10.15.0
                SDK:      10.15.4
                Tools:
                {
                    LD: 556.4.0
                }
            }
            LC_BUILD_VERSION:
            {
                Platform: Mac Catalyst
                Min OS:   13.4.0
                SDK:      13.4.0
                Tools:
                {
                    LD: 556.4.0
                }
            }
            LC_SOURCE_VERSION:     1676.105.0.0.0
            LC_SEGMENT_SPLIT_INFO:
            {
                Data offset: 0x004F0B20
                Data size:   0x00022108
            }
            LC_REEXPORT_DYLIB:     libobjc.A.dylib
            LC_REEXPORT_DYLIB:     CoreFoundation
            LC_LOAD_DYLIB:         libauto.dylib
            LC_LOAD_DYLIB:         libfakelink.dylib
            LC_LOAD_DYLIB:         libcompression.dylib
            LC_LOAD_DYLIB:         DiskArbitration
            LC_LOAD_DYLIB:         libarchive.2.dylib
            LC_LOAD_DYLIB:         libDiagnosticMessagesClient.dylib
            LC_LOAD_DYLIB:         libicucore.A.dylib
            LC_LOAD_DYLIB:         libxml2.2.dylib
            LC_LOAD_DYLIB:         libz.1.dylib
            LC_LOAD_DYLIB:         SystemConfiguration
            LC_LOAD_DYLIB:         CoreServices
            LC_LOAD_DYLIB:         liblangid.dylib
            LC_LOAD_DYLIB:         IOKit
            LC_LOAD_DYLIB:         libCRFSuite.dylib
            LC_LOAD_DYLIB:         libSystem.B.dylib
            LC_LOAD_DYLIB:         CFNetwork
            LC_FUNCTION_STARTS:
            {
                Data offset: 0x00512C28
                Data size:   0x00005CC0
            }
            LC_DATA_IN_CODE:
            {
                Data offset: 0x005188E8
                Data size:   0x000004C8
            }
            LC_CODE_SIGNATURE:
            {
                Data offset: 0x006FDEA0
                Data size:   0x00012750
            }
        }
        Libraries:
        {
            /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation
            /usr/lib/libobjc.A.dylib
            /System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
            /usr/lib/libauto.dylib
            /usr/lib/libfakelink.dylib
            /usr/lib/libcompression.dylib
            /System/Library/Frameworks/DiskArbitration.framework/Versions/A/DiskArbitration
            /usr/lib/libarchive.2.dylib
            /usr/lib/libDiagnosticMessagesClient.dylib
            /usr/lib/libicucore.A.dylib
            /usr/lib/libxml2.2.dylib
            /usr/lib/libz.1.dylib
            /System/Library/Frameworks/SystemConfiguration.framework/Versions/A/SystemConfiguration
            /System/Library/Frameworks/CoreServices.framework/Versions/A/CoreServices
            /usr/lib/liblangid.dylib
            /System/Library/Frameworks/IOKit.framework/Versions/A/IOKit
            /usr/lib/libCRFSuite.dylib
            /usr/lib/libSystem.B.dylib
            /System/Library/Frameworks/CFNetwork.framework/Versions/A/CFNetwork
        }
    }

License
-------

Project is released under the terms of the MIT License.

Repository Infos
----------------

    Owner:          Jean-David Gadina - XS-Labs
    Web:            www.xs-labs.com
    Blog:           www.noxeos.com
    Twitter:        @macmade
    GitHub:         github.com/macmade
    LinkedIn:       ch.linkedin.com/in/macmade/
    StackOverflow:  stackoverflow.com/users/182676/macmade
