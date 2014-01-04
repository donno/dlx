//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Instructions
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides the DLX instructions.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
//
//===----------------------------------------------------------------------===//

#include "Instructions.hpp"

static dlx::assembly::instructions::InstructionMap& allInstructions()
{
  static dlx::assembly::instructions::InstructionMap map;
  return map;
}

const dlx::assembly::instructions::InstructionMap&
dlx::assembly::instructions::all()
{
  return allInstructions();
}

dlx::assembly::InstructionDefinition::InstructionDefinition(
  const std::string& mnemonic, int opcode, Instruction::Format format)
: mnemonic(mnemonic), opcode(opcode), format(format)
{
  allInstructions().insert(std::make_pair(mnemonic, this));
}

//===--------------------------- End of the file --------------------------===//