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

    brew install --HEAD macmade/tap/macho

### Usage
    
    Usage: macho [OPTIONS] [PATH] ...
    
    Supports regular and Fat Mach-O files as well as dyld cache files.
    Multiple files can be passed at once.
    
    Options:
        
        -h / --help         Shows this help dialog.
        -i / --info         Prints the detailed Mach-O structure.
        -l / --libs         Prints the list of linked libraries.
        -s / --str          Prints the list of strings from __cstring,
                            __oslogstring and __ustring.
        -c / --objc-class   Prints the list of Objective-C classes from
                            __objc_classname.
        -m / --objc-method  Prints the list of Objective-C methods
                            from __objc_methname.
        -d / --data         Prints the file data.

### Example output

    $ macho --info /System/Library/Frameworks/Foundation.framework/Foundation
    
    Mach-O file: Foundation
    {
        CPU:      x86-64 - Generic
        Type:     MH_DYLIB - Dynamically bound shared library
        Flags:    0x02000085
        {
            MH_NOUNDEFS:           No undefined references
            MH_DYLDLINK:           Input for the dynamic linker
            MH_TWOLEVEL:           Using two-level name space bindings
            MH_APP_EXTENSION_SAFE: Can be used in application extensions
        }
        Commands: 33
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
                Flags:       0x00000000
                Sections:    20
                {
                    Section64:
                    {
                        Section:           __text
                        Segment:           __TEXT
                        Address:           0x0000000000001E70
                        Size:              0x0000000000305038
                        Offset:            0x00001E70
                        Alignment:         0x00000004
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_PURE_INSTRUCTIONS
                            S_ATTR_SOME_INSTRUCTIONS
                        }
                    }
                    Section64:
                    {
                        Section:           __stubs
                        Segment:           __TEXT
                        Address:           0x0000000000306EA8
                        Size:              0x00000000000025EC
                        Offset:            0x00306EA8
                        Alignment:         0x00000001
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_SYMBOL_STUBS
                        {
                            S_ATTR_PURE_INSTRUCTIONS
                            S_ATTR_SOME_INSTRUCTIONS
                        }
                    }
                    Section64:
                    {
                        Section:           __stub_helper
                        Segment:           __TEXT
                        Address:           0x0000000000309494
                        Size:              0x0000000000003F44
                        Offset:            0x00309494
                        Alignment:         0x00000002
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_PURE_INSTRUCTIONS
                            S_ATTR_SOME_INSTRUCTIONS
                        }
                    }
                    Section64:
                    {
                        Section:           __const
                        Segment:           __TEXT
                        Address:           0x000000000030D3E0
                        Size:              0x000000000000B0D0
                        Offset:            0x0030D3E0
                        Alignment:         0x00000004
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __cstring
                        Segment:           __TEXT
                        Address:           0x00000000003184B0
                        Size:              0x00000000000402FA
                        Offset:            0x003184B0
                        Alignment:         0x00000004
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_CSTRING_LITERALS
                    }
                    Section64:
                    {
                        Section:           __gcc_except_tab
                        Segment:           __TEXT
                        Address:           0x00000000003587AC
                        Size:              0x000000000000587C
                        Offset:            0x003587AC
                        Alignment:         0x00000002
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __oslogstring
                        Segment:           __TEXT
                        Address:           0x000000000035E030
                        Size:              0x0000000000006AF9
                        Offset:            0x0035E030
                        Alignment:         0x00000004
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_CSTRING_LITERALS
                    }
                    Section64:
                    {
                        Section:           __ustring
                        Segment:           __TEXT
                        Address:           0x0000000000364B2A
                        Size:              0x0000000000000404
                        Offset:            0x00364B2A
                        Alignment:         0x00000001
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __dof_NSXPCList
                        Segment:           __TEXT
                        Address:           0x0000000000364F2E
                        Size:              0x00000000000002E9
                        Offset:            0x00364F2E
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_DTRACE_DOF
                    }
                    Section64:
                    {
                        Section:           __dof_NSXPCList0
                        Segment:           __TEXT
                        Address:           0x0000000000365217
                        Size:              0x000000000000060B
                        Offset:            0x00365217
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_DTRACE_DOF
                    }
                    Section64:
                    {
                        Section:           __dof_NSProgres
                        Segment:           __TEXT
                        Address:           0x0000000000365822
                        Size:              0x000000000000115B
                        Offset:            0x00365822
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_DTRACE_DOF
                    }
                    Section64:
                    {
                        Section:           __dof_NSXPCConn
                        Segment:           __TEXT
                        Address:           0x000000000036697D
                        Size:              0x00000000000021AA
                        Offset:            0x0036697D
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_DTRACE_DOF
                    }
                    Section64:
                    {
                        Section:           __dof_Cocoa_Lay
                        Segment:           __TEXT
                        Address:           0x0000000000368B27
                        Size:              0x0000000000000500
                        Offset:            0x00368B27
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_DTRACE_DOF
                    }
                    Section64:
                    {
                        Section:           __dof_NSXPCProx
                        Segment:           __TEXT
                        Address:           0x0000000000369027
                        Size:              0x000000000000075E
                        Offset:            0x00369027
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_DTRACE_DOF
                    }
                    Section64:
                    {
                        Section:           __dof_NSProcess
                        Segment:           __TEXT
                        Address:           0x0000000000369785
                        Size:              0x0000000000000343
                        Offset:            0x00369785
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_DTRACE_DOF
                    }
                    Section64:
                    {
                        Section:           __unwind_info
                        Segment:           __TEXT
                        Address:           0x0000000000369AC8
                        Size:              0x000000000000BE7C
                        Offset:            0x00369AC8
                        Alignment:         0x00000002
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __eh_frame
                        Segment:           __TEXT
                        Address:           0x0000000000375948
                        Size:              0x0000000000003228
                        Offset:            0x00375948
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_classname
                        Segment:           __TEXT
                        Address:           0x0000000000378B70
                        Size:              0x0000000000006021
                        Offset:            0x00378B70
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_CSTRING_LITERALS
                    }
                    Section64:
                    {
                        Section:           __objc_methname
                        Segment:           __TEXT
                        Address:           0x000000000037EB91
                        Size:              0x000000000003CBE8
                        Offset:            0x0037EB91
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_CSTRING_LITERALS
                    }
                    Section64:
                    {
                        Section:           __objc_methtype
                        Segment:           __TEXT
                        Address:           0x00000000003BB779
                        Size:              0x000000000000A887
                        Offset:            0x003BB779
                        Alignment:         0x00000000
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_CSTRING_LITERALS
                    }
                }
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
                Flags:       0x00000000
                Sections:    26
                {
                    Section64:
                    {
                        Section:           __nl_symbol_ptr
                        Segment:           __DATA
                        Address:           0x00000000003C6000
                        Size:              0x0000000000000008
                        Offset:            0x003C6000
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_NON_LAZY_SYMBOL_POINTERS
                    }
                    Section64:
                    {
                        Section:           __got
                        Segment:           __DATA
                        Address:           0x00000000003C6008
                        Size:              0x0000000000000B80
                        Offset:            0x003C6008
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_NON_LAZY_SYMBOL_POINTERS
                    }
                    Section64:
                    {
                        Section:           __la_symbol_ptr
                        Segment:           __DATA
                        Address:           0x00000000003C6B88
                        Size:              0x0000000000003290
                        Offset:            0x003C6B88
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_LAZY_SYMBOL_POINTERS
                    }
                    Section64:
                    {
                        Section:           __const
                        Segment:           __DATA
                        Address:           0x00000000003C9E20
                        Size:              0x000000000000DD78
                        Offset:            0x003C9E20
                        Alignment:         0x00000004
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __cfstring
                        Segment:           __DATA
                        Address:           0x00000000003D7B98
                        Size:              0x000000000002DE40
                        Offset:            0x003D7B98
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_classlist
                        Segment:           __DATA
                        Address:           0x00000000004059D8
                        Size:              0x00000000000019A0
                        Offset:            0x004059D8
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_NO_DEAD_STRIP
                        }
                    }
                    Section64:
                    {
                        Section:           __objc_nlclslist
                        Segment:           __DATA
                        Address:           0x0000000000407378
                        Size:              0x0000000000000018
                        Offset:            0x00407378
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_NO_DEAD_STRIP
                        }
                    }
                    Section64:
                    {
                        Section:           __objc_catlist
                        Segment:           __DATA
                        Address:           0x0000000000407390
                        Size:              0x00000000000000F0
                        Offset:            0x00407390
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_NO_DEAD_STRIP
                        }
                    }
                    Section64:
                    {
                        Section:           __objc_nlcatlist
                        Segment:           __DATA
                        Address:           0x0000000000407480
                        Size:              0x0000000000000008
                        Offset:            0x00407480
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_NO_DEAD_STRIP
                        }
                    }
                    Section64:
                    {
                        Section:           __objc_protolist
                        Segment:           __DATA
                        Address:           0x0000000000407488
                        Size:              0x0000000000000190
                        Offset:            0x00407488
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_imageinfo
                        Segment:           __DATA
                        Address:           0x0000000000407618
                        Size:              0x0000000000000008
                        Offset:            0x00407618
                        Alignment:         0x00000002
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_const
                        Segment:           __DATA
                        Address:           0x0000000000407620
                        Size:              0x0000000000096820
                        Offset:            0x00407620
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_selrefs
                        Segment:           __DATA
                        Address:           0x000000000049DE40
                        Size:              0x000000000000B4F8
                        Offset:            0x0049DE40
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_LITERAL_POINTERS
                        {
                            S_ATTR_NO_DEAD_STRIP
                        }
                    }
                    Section64:
                    {
                        Section:           __objc_protorefs
                        Segment:           __DATA
                        Address:           0x00000000004A9338
                        Size:              0x00000000000000B0
                        Offset:            0x004A9338
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_classrefs
                        Segment:           __DATA
                        Address:           0x00000000004A93E8
                        Size:              0x0000000000001718
                        Offset:            0x004A93E8
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_NO_DEAD_STRIP
                        }
                    }
                    Section64:
                    {
                        Section:           __objc_superrefs
                        Segment:           __DATA
                        Address:           0x00000000004AAB00
                        Size:              0x0000000000001278
                        Offset:            0x004AAB00
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                        {
                            S_ATTR_NO_DEAD_STRIP
                        }
                    }
                    Section64:
                    {
                        Section:           __objc_ivar
                        Segment:           __DATA
                        Address:           0x00000000004ABD78
                        Size:              0x0000000000004860
                        Offset:            0x004ABD78
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_data
                        Segment:           __DATA
                        Address:           0x00000000004B05D8
                        Size:              0x0000000000010040
                        Offset:            0x004B05D8
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __data
                        Segment:           __DATA
                        Address:           0x00000000004C0620
                        Size:              0x0000000000002968
                        Offset:            0x004C0620
                        Alignment:         0x00000004
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __crash_info
                        Segment:           __DATA
                        Address:           0x00000000004C2F88
                        Size:              0x0000000000000040
                        Offset:            0x004C2F88
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_arraydata
                        Segment:           __DATA
                        Address:           0x00000000004C2FC8
                        Size:              0x00000000000004A0
                        Offset:            0x004C2FC8
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_arrayobj
                        Segment:           __DATA
                        Address:           0x00000000004C3468
                        Size:              0x00000000000001C8
                        Offset:            0x004C3468
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_intobj
                        Segment:           __DATA
                        Address:           0x00000000004C3630
                        Size:              0x00000000000008B8
                        Offset:            0x004C3630
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __objc_dictobj
                        Segment:           __DATA
                        Address:           0x00000000004C3EE8
                        Size:              0x0000000000000028
                        Offset:            0x004C3EE8
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_REGULAR
                    }
                    Section64:
                    {
                        Section:           __common
                        Segment:           __DATA
                        Address:           0x00000000004C3F10
                        Size:              0x0000000000000080
                        Offset:            0x00000000
                        Alignment:         0x00000003
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_ZEROFILL
                    }
                    Section64:
                    {
                        Section:           __bss
                        Segment:           __DATA
                        Address:           0x00000000004C3F90
                        Size:              0x0000000000000FC0
                        Offset:            0x00000000
                        Alignment:         0x00000004
                        Relocation offset: 0x00000000
                        Relocation count:  0x00000000
                        Flags:             S_ZEROFILL
                    }
                }
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
