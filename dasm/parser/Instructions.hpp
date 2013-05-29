#ifndef DLX_INSTRUCTIONS_HPP_
#define DLX_INSTRUCTIONS_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Instructions
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides the DLX instructions.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : Provides defintions of the instructions, such as the register
//                format (what operands it needs), as well as the encoding.
//
//===----------------------------------------------------------------------===//

#include "Types.hpp"

#include <string>

namespace dlx
{
  namespace assembly
  {
    struct InstructionDef
    {
      const std::string mnemonic;
      const int opcode;
      const Instruction::Format format;
    };
    
    namespace instructions
    {
      const InstructionDef add = {
        "add", 000000, Instruction::RegisterToRegister
        };
    }
  }
}

#endif

