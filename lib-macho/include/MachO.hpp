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
 * @header      MachO.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_HPP
#define MACHO_HPP

#include <MachO/BinaryDataStream.hpp>
#include <MachO/BinaryFileStream.hpp>
#include <MachO/BinaryStream.hpp>
#include <MachO/Casts.hpp>
#include <MachO/FATArch.hpp>
#include <MachO/FATFile.hpp>
#include <MachO/File.hpp>
#include <MachO/FileFlags.hpp>
#include <MachO/FileType.hpp>
#include <MachO/Functions.hpp>
#include <MachO/Info.hpp>
#include <MachO/InfoObject.hpp>
#include <MachO/IntegerWrapper.hpp>
#include <MachO/LoadCommand.hpp>
#include <MachO/NList.hpp>
#include <MachO/NList64.hpp>
#include <MachO/Platform.hpp>
#include <MachO/Tool.hpp>
#include <MachO/ToString.hpp>

#include <MachO/LoadCommands/BuildVersion.hpp>
#include <MachO/LoadCommands/DyldInfo.hpp>
#include <MachO/LoadCommands/Dylib.hpp>
#include <MachO/LoadCommands/Dylinker.hpp>
#include <MachO/LoadCommands/DysymTab.hpp>
#include <MachO/LoadCommands/EncryptionInfo.hpp>
#include <MachO/LoadCommands/EncryptionInfo64.hpp>
#include <MachO/LoadCommands/EntryPoint.hpp>
#include <MachO/LoadCommands/FilesetEntry.hpp>
#include <MachO/LoadCommands/FVMFile.hpp>
#include <MachO/LoadCommands/FVMLib.hpp>
#include <MachO/LoadCommands/Ident.hpp>
#include <MachO/LoadCommands/LinkEditData.hpp>
#include <MachO/LoadCommands/LinkerOption.hpp>
#include <MachO/LoadCommands/Note.hpp>
#include <MachO/LoadCommands/PrebindChecksum.hpp>
#include <MachO/LoadCommands/PreboundDylib.hpp>
#include <MachO/LoadCommands/PrePage.hpp>
#include <MachO/LoadCommands/Routines.hpp>
#include <MachO/LoadCommands/Routines64.hpp>
#include <MachO/LoadCommands/RPath.hpp>
#include <MachO/LoadCommands/Segment.hpp>
#include <MachO/LoadCommands/Segment64.hpp>
#include <MachO/LoadCommands/SourceVersion.hpp>
#include <MachO/LoadCommands/SubClient.hpp>
#include <MachO/LoadCommands/SubFramework.hpp>
#include <MachO/LoadCommands/SubLibrary.hpp>
#include <MachO/LoadCommands/SubUmbrella.hpp>
#include <MachO/LoadCommands/SymSeg.hpp>
#include <MachO/LoadCommands/SymTab.hpp>
#include <MachO/LoadCommands/Thread.hpp>
#include <MachO/LoadCommands/TwoLevelHints.hpp>
#include <MachO/LoadCommands/Unknown.hpp>
#include <MachO/LoadCommands/UUID.hpp>
#include <MachO/LoadCommands/VersionMin.hpp>

#endif /* MACHO_HPP */
