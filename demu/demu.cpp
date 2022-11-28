//===----------------------------------------------------------------------===//
//
//                            DLX Emulator
//
// NAME         : demu
// PURPOSE      : Provides main entry point for assembling DLX assembly.
// COPYRIGHT    : (c) 2015 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// DESCRIPTION  : Provides an emulator for the DLX instruction set.
//
//===----------------------------------------------------------------------===//

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "hardware/Instruction.hpp"
#include "hardware/Instructions.hpp"
#include "hardware/Machine.hpp"

#include <cstdint>
#include <limits>
#include <memory>
#include <iomanip>
#include <iostream>
#include <vector>

#include <stdio.h>

std::uint32_t SwapBytes(std::uint32_t word)
{
  // Take into account the different endianness.
  word = (word & 0x0000FFFF) << 16 | (word & 0xFFFF0000) >> 16;
  word = (word & 0x00FF00FF) << 8 | (word & 0xFF00FF00) >> 8;
  return word;
}

dlx::hardware::DLXMachine::DLXMachine(const Configuration& configuration)
: mem(configuration.startAddress, configuration.endAddress),
  programCounter(std::numeric_limits<unsigned int>::max())
{
}

void dlx::hardware::DLXMachine::step()
{
  // Find the memory block for the starting address.
  const MemoryBlock* const block = memory()[programCounter.value];
  if (block == nullptr) 
  {
    throw std::out_of_range("The program counter is pointing to memory "
                            "outside the addressable range.");
  }
  
  std::cout << "Executing " << programCounter.value << " (0x"
            << std::hex << programCounter.value<< ")" << std::endl;

  const unsigned char* const rawBlock = block->storage.get();
  const auto typedBlock =
    reinterpret_cast<const std::uint32_t* const>(rawBlock);
    
  const auto pc =
    (programCounter.value - block->startAddress) / sizeof(std::uint32_t);

  // Look-up the next instruction from memory.  
  instructionRegister.value = SwapBytes(typedBlock[pc]);

  // Increment the program counter.
  programCounter.value += 4;
  
  // Decode the instruction.
  const auto opcode = instructionRegister.formatI.opcode;
  
//  if (opcode == 0 || opcode == 1)
//  {
//    // The instruction is a register-to-register instruction.
//    std::cout << "ri=" << instructionRegister.formatR.ri << std::endl;
//    std::cout << "rj=" << instructionRegister.formatR.rj << std::endl;
//    std::cout << "rk=" << instructionRegister.formatR.rk << std::endl;
//    std::cout << "mod=" << instructionRegister.formatR.modifier << std::endl;
//  }
//  else if (opcode == 2 || opcode == 3 || opcode == 16 || opcode == 17)
//  {
//    // The instruction is a long-immediate instruction.
//    std::cout << "Lsgn=" << instructionRegister.formatL.Lsgn << std::endl;
//  }
//  else
//  {
//    // The instruction is a immediate instruction.
//    std::cout << "ri=" << instructionRegister.formatI.ri << std::endl;
//    std::cout << "rj=" << instructionRegister.formatI.rj << std::endl;
//    std::cout << "Ksgn=" << instructionRegister.formatI.Ksgn << std::endl;
//    std::cout << "Kusn=" << instructionRegister.formatI.Kusn << std::endl;
//  }

//  std::cout << "Instruction: 0x" 
//            << std::hex << std::setw(8) << std::setfill('0')
//            << instructionRegister.value
//            << " opcode=" << std::dec << (int)opcode
//            << std::endl;

  if (Instructions[opcode])
  {
    Instructions[opcode](this);
  }
}

void dlx::hardware::DLXMachine::run()
{
  std::cout << "> Program starting" << std::endl;

  instructionRegister.value = 0;

  // Keep stepping until the halt instruction is raised.
  while (instructionRegister.formatR.opcode != 0 ||
         instructionRegister.formatR.modifier != 1)
  {
    step();
  }
  
  std::cout << " r1=" << registers[1].value
            << " r2=" << registers[2].value
            << " r3=" << registers[3].value
            << " r4=" << registers[4].value
            << std::endl;

  std::cout << "< Program terminated" << std::endl;  
}

#include <fstream>
#include <string>
#include <cctype>

void LoadDlxFile(const char *filename, dlx::hardware::DLXMachine* machine)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
      std::cerr << "error: could not read " << filename << std::endl;
      return;
  }
  
  std::string line;
  std::getline(file, line);
  if (line != std::string(".abs")) {
    std::cerr << "error: invalid file " << filename << ". It must have .abs on "
                 "the first line, instead it had " << line << std::endl;
    return;
  }

  typedef dlx::hardware::MemoryBlock MemoryBlock;

  const auto findBlock = [&machine](unsigned int address) -> MemoryBlock*
  {
    MemoryBlock* const block = machine->memory()[address];
    if (block == nullptr)
    {
      std::cerr << "error: tried loading data outside any of the valid "
                   "memory ranges."
                << std::endl;
    }
    return block;
  };

  MemoryBlock* currentBlock = nullptr;
  while (!file.eof())
  {
    std::getline(file, line);

    if (line.empty()) continue;

    unsigned int address = 0;
    if (sscanf(line.c_str(), "%08X", &address) == 1)
    {
      if (currentBlock == nullptr || !currentBlock->contains(address))
      {
        // Find the block that contains this address.
        currentBlock = findBlock(address);
        if (currentBlock == nullptr) return;
      }

      // Read the data on the line.
      unsigned char* rawStorage = currentBlock->storage.get();
      rawStorage += address - currentBlock->startAddress;
      for (std::size_t i = 8; i < line.length(); ++i)
      {
        const auto c = std::toupper(line[i]);
        if (std::isspace(c)) continue;

        if (!std::isxdigit(c))
        {
          std::cerr << "error: expected a white-space or a hexadecimal digit."
                    << std::endl;
          return;
        }
        else
        {
          // For simplicity assume they are always in pairs.
          // I.e a hexadecimal digit is followed by another one.
          const auto c2 = std::toupper(line[i + 1]);
          ++i;
          if (!std::isxdigit(c2))
          {
            std::cerr << "error: expected a hexadecimal digit." << std::endl;
            return;
          }

          int data;
          if (c >= 'A' && c <= 'F') data = (10 + (c - 'A')) << 4;
          else data = (c - '0') << 4;

          if (c2 >= 'A' && c2 <= 'F') data += (10 + (c2 - 'A'));
          else data += (c2 - '0');

          *rawStorage = static_cast<unsigned char>(data);
          ++rawStorage;
        }
      }
    }
    else if (line.compare(0, 6, ".start") == 0)
    {
      // This line contains the starting address.
      if (sscanf(line.c_str(), ".start %08X", &address) == 1)
      {
        machine->SetProgramCounter(address);
      }
      else
      {
        std::cerr << "error: expected start address but found "
                  << line.substr(6) << std::endl;
      }
    }
    else
    {
      std::cerr << "error: expected address of the form XXXXXX where X is a "
                   "hexdecimal digit or .start XXXXXX" << std::endl;
    }
  }
}

#include <cassert>

void tests()
{
  // Test register operators.
  using namespace dlx::hardware;
  {
    Register a;
    Register b;
    
    std::cout << a.value << " " << b.value << std::endl;

    a = 125;
    if (a.value != 125) std::cerr << "FAILED" << std::endl;
   
    std::cout << a.value << " " << b.value << std::endl;
    
    b = a - 2;
    
    if (b.value != 123) std::cerr << "FAILED" << std::endl;
   
    std::cout << a.value << " " << b.value << std::endl;
    
    a = a - b;

    if (a.value != 2) std::cerr << "FAILED" << std::endl;
   
    std::cout << a.value << " " << b.value << std::endl;
  }
  
  // Execute a simple DLX program that is equivelent to this:
  //
  //   sum = 0
  //   i = 0
  // start:
  //   sum = sum + 3
  //   i = i + 1
  //   if (i < 1000) goto start;
  //   halt. 
  dlx::hardware::Configuration config = {
    0x00000, 0x10000, // dsim new ram dsim.memory.Ram 00000 4000
  };
  dlx::hardware::DLXMachine machine(config);

  const std::uint32_t instructions[] = {
     SwapBytes(0x20010000), // sum = 0   (r1)
     SwapBytes(0x20020000), //   i = 0   (r2)
     SwapBytes(0x20210003), // sum = sum + 3
     SwapBytes(0x20420001), //   i = i + 1
     SwapBytes(0x684303E8), // con = i < 1000 (con = r3)
     SwapBytes(0x1460FFF0), // if con == 1 then goto instruction 3.
     SwapBytes(0x00000001), // halt
   };

  MemoryBlock* block = machine.block(0);
  std::memcpy(block->storage.get(), instructions, sizeof(std::uint32_t) * 7);
  
  machine.SetProgramCounter(0);
  machine.step();
  machine.step();
  
  assert(machine.ConstRegisters()[1] == 0);
  assert(machine.ConstRegisters()[2] == 0);
  
  machine.step();
  
  assert(machine.ConstRegisters()[1] == 3);
  assert(machine.ConstRegisters()[2] == 0);
  
  machine.step();
  
  assert(machine.ConstRegisters()[1] == 3);
  assert(machine.ConstRegisters()[2] == 1);
  
  machine.step();

  assert(machine.ConstRegisters()[1] == 3);
  assert(machine.ConstRegisters()[2] == 1);
  assert(machine.ConstRegisters()[3] == 1);
  
  machine.step(); // if (r3 == 1)...
  
  machine.step(); // sum = sum + 3
  
  assert(machine.ConstRegisters()[1] == 6);
  assert(machine.ConstRegisters()[2] == 1);
  assert(machine.ConstRegisters()[3] == 1);
  
  machine.run(); // keep going until we halt.
}

int main(int argc, const char *argv[])
{
  std::cout << "demu v0.1 by Donno" << std::endl;
  if (argc < 2)
  {
    std::cout << "usage: " << argv[0] << " filename" << std::endl;
    return 0;
  }
 
  //tests();

  dlx::hardware::Configuration config = {
    0x00000, 0x10000, // dsim new ram dsim.memory.Ram 00000 4000
  };

  dlx::hardware::DLXMachine machine(config);

  std::cout << "Loading dlx: " << argv[1] << std::endl;
  LoadDlxFile(argv[1], &machine);
  
  // Execute the program loaded into to machine.
  machine.run();
}
