#ifndef DLX_INSTRUCTION_HPP_
#define DLX_INSTRUCTION_HPP_
//===----------------------------------------------------------------------===//
//
//                       DLX Instruction Set Emulator
//
// NAME         : Instruction
// NAMESPACE    : dlx::hardware
// PURPOSE      : Provides an abstractions over a DLX instruction.
// COPYRIGHT    : (c) 2015 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : All instructions are 32-bits in DLX.
//
// There are three different instruction formats:
// * Format R - Register-to-register [opcode | i | j | k | zeroes | modifier]
// * Format I - Immediate            [opcode | i | j |       Ksgn/Kusn      ]
// * Format L - Long-immediate       [opcode |         Lsgn/Lusn            ]
//
// i, j, k represent the index of a register.
// Ksgn/Kusn is a 16-bit signed/unsigned constant.
// Lsgn/Lusn is a 26-bit signed/unsigned constant.
//
//===----------------------------------------------------------------------===//

#include <cstdint>

namespace dlx
{
  namespace hardware
  {
    struct InstructionRegisterToRegister
    {
      std::uint32_t modifier : 6;
      std::uint32_t zero : 5;
      std::uint32_t rk : 5;
      std::uint32_t rj : 5;
      std::uint32_t ri : 5;
      std::uint32_t opcode : 6;
    };

    struct InstructionImmediate
    {
      union
      {
        std::int16_t Ksgn;
        std::uint16_t Kusn;
      };
      std::uint16_t rj : 5;
      std::uint16_t ri : 5;
      std::uint16_t opcode : 6;
    };

    struct InstructionLongImmediate
    {
      std::int32_t Lsgn : 26;
      std::uint32_t opcode : 6;
    };

    struct Instruction
    {
      union
      {
        InstructionRegisterToRegister formatR;
        InstructionImmediate formatI;
        InstructionLongImmediate formatL;
        std::uint32_t value;
      };
    };

    static_assert(sizeof(InstructionRegisterToRegister) == 4,
                  "The encoding of an instruction is always 4-bytes.");
    static_assert(sizeof(InstructionImmediate) == 4,
                  "The encoding of an instruction is always 4-bytes.");
    static_assert(sizeof(InstructionLongImmediate) == 4,
                  "The encoding of an instruction is always 4-bytes.");
    static_assert(sizeof(Instruction) == 4,
                  "The encoding of an instruction is always 4-bytes.");
  }
}

#endif
