//===----------------------------------------------------------------------===//
//
//                       DLX Instruction Set Emulator
//
// NAME         : Memory
// NAMESPACE    : dlx::hardware
// PURPOSE      : Provides an abstractions over the memory system of a DLX.
// COPYRIGHT    : (c) 2015 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : TODO Document.
//
//===----------------------------------------------------------------------===//

#include "Memory.hpp"

dlx::hardware::MemoryBlock*
dlx::hardware::Memory::operator[](std::uint32_t address)
{
  for (auto block = blocks.begin(); block != blocks.end(); ++block)
  {
    if (block->contains(address)) return &(*block);
  }
  return nullptr;
}

dlx::hardware::Memory::Memory(std::uint32_t start, std::uint32_t end)
: blocks()
{
  MemoryBlock block;
  block.startAddress = start;
  block.endAddress = end;
  blocks.push_back(std::move(block));
  blocks.back().storage.reset(new unsigned char[end - start]());
}

//===--------------------------- End of the file --------------------------===//