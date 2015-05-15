#ifndef DLX_MACHINE_HPP_
#define DLX_MACHINE_HPP_
//===----------------------------------------------------------------------===//
//
//                       DLX Instruction Set Emulator
//
// NAME         : Machine
// NAMESPACE    : dlx::hardware
// PURPOSE      : Provides the representing of the DLX machine.
// COPYRIGHT    : (c) 2015 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : Provides access to the virtual memory of the machine and the
//                registers.
//
//===----------------------------------------------------------------------===//

#include "Instruction.hpp"
#include "Memory.hpp"
#include "Register.hpp"

#include <cstdint>

namespace dlx
{
  namespace hardware
  {
    struct Configuration
    {
      unsigned int startAddress;
      unsigned int endAddress;
    };

    class DLXMachine
    {
      Memory mem;
      Register registers[32];

      // Special purpose registers.
      Register programCounter;         // pc
      Instruction instructionRegister; // ir
      Register processorStatusWord;    // psw
      Register exceptionAddress;       // xar
      Register exceptionBase;          // xbr

    public:
      DLXMachine(const Configuration& configuration);

      // Access the machine's memory.
      Memory& memory() { return mem; }

      Register* Registers() { return registers; }
      //const Register* Registers() const { return registers; }
      const Register* ConstRegisters() const { return registers; }

      // Provides access to the components of the instruction in the
      // instruction register.
      const InstructionRegisterToRegister&
      instruction(const InstructionRegisterToRegister&) const
      { return instructionRegister.formatR; }

      const InstructionImmediate&
      instruction(const InstructionImmediate&) const
      { return instructionRegister.formatI; }

      const InstructionLongImmediate&
      instruction(const InstructionLongImmediate&) const
      { return instructionRegister.formatL; }

      MemoryBlock* block(unsigned int address) { return memory()[address]; }

      unsigned int ProgramCounter() const { return programCounter.value; }
      void SetProgramCounter(unsigned int address)
      { programCounter.value = address; }

      // Execute the next instruction.
      void step();
      // Throws std::out_of_range if the program counter points to an
      // instruction outside the addressable range of memory in the machine.

      // Keep executing until a halt instruction is reached or an error
      // occurs.
      //
      // Throws std::out_of_range, see step() for details.
      void run();
    };
  }
}

#endif
