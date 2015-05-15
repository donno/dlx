#ifndef DLX_MEMORY_HPP_
#define DLX_MEMORY_HPP_
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

#include <cstdint>
#include <memory>
#include <vector>

namespace dlx
{
  namespace hardware
  {
    // Represents a contiguous block of memory.
    struct MemoryBlock
    {
      std::uint32_t startAddress;
      std::uint32_t endAddress;
      std::unique_ptr<unsigned char[]> storage;

      static_assert(sizeof(unsigned char) == 1,
                    "An unsigned char is expected to be a single byte.");

      MemoryBlock() : startAddress(0), endAddress(0), storage() {}

      MemoryBlock(MemoryBlock&& that)
      : startAddress(that.startAddress),
        endAddress(that.endAddress),
        storage(std::move(that.storage))
      {
      }

      // Returns true if startAddress <= address < endAddress.
      bool contains(std::uint32_t address) const
      {
        return address >= startAddress && address < endAddress;
      }
    };

    // Represents the memory unit which knows about the indvidual memory
    // blocks. Provides access to the undyling blocks of memory.
    class Memory
    {
      std::vector<MemoryBlock> blocks;

    public:

      Memory(std::uint32_t start, std::uint32_t end);

      // Return the block that contains the given address.
      MemoryBlock* operator[](std::uint32_t address);
    };
  }
}

#endif
