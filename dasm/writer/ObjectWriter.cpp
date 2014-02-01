//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : ObjectWriter
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides operators and functions for writing DLX machine code.
// COPYRIGHT    : (c) 2014 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
//
//===----------------------------------------------------------------------===//

#include "ObjectWriter.hpp"

dlx::assembly::ObjectWriter::ObjectWriter(std::ostream& writer)
: myWriter(writer),
  myBytesWrittenToLine(0),
  myAddressOfLine(0),
  myStartAddress(0),
  isStartAddressKnown(false)
{
  myWriter << ".abs" << std::endl;
  myWriter << std::hex << std::uppercase;
}

dlx::assembly::ObjectWriter::~ObjectWriter()
{
  if (isStartAddressKnown)
  {
    if (myBytesWrittenToLine != 0)
    {
      myWriter << std::endl;
    }
    myWriter << std::endl << std::endl << std::endl << std::endl << ".start "
             << std::hex << std::uppercase << std::setfill('0') << std::setw(2)
             << myStartAddress << std::endl;
  }
}

void dlx::assembly::ObjectWriter::SetStartAddress(size_t startAddress)
{
  myStartAddress = startAddress;
  isStartAddressKnown = true;
}

void dlx::assembly::ObjectWriter::PreByteWritten()
{
  if (myBytesWrittenToLine == 16)
  {
    myWriter << std::endl;
    myBytesWrittenToLine = 0;
    myAddressOfLine += 16;
  }
  else if (myBytesWrittenToLine > 0)
  {
    myWriter << ' ';
  }

  if (myBytesWrittenToLine == 0)
  {
    myWriter << std::setfill('0') << std::setw(8) << myAddressOfLine << "  ";
  }

  ++myBytesWrittenToLine;
}


//===--------------------------- End of the file --------------------------===//