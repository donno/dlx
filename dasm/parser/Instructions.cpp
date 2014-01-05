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

#include <cassert>

static int pow10(int power)
{
  assert(power > 0);
  int result = 10;
  for (--power; power > 0; --power)
  {
    result *= 10;
  }
  return result;
}

// Given a number in decimal-encoded binary, i.e, if number is 11 (so eleven
// if treated as decimal), then this function will return 3 (in decimal).
static int convertDecimalEncodedBinary(int number)
{
  int trueNumber = number & 1;
  for (int i = 1; i < 6; ++i)
  {
    trueNumber += (number / pow10(i) == 1) ? (1 << i) : 0;
  }
  return trueNumber;
}

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
: mnemonic(mnemonic), opcode(convertDecimalEncodedBinary(opcode)), modifier(0),
  format(format)
{
  // This construction shouldn't be used for register-to-register instructions.
  assert(format != Instruction::RegisterToRegister);
  allInstructions().insert(std::make_pair(mnemonic, this));
}

dlx::assembly::InstructionDefinition::InstructionDefinition(
  const std::string& mnemonic, int opcode, int modifier)
: mnemonic(mnemonic),
  opcode(convertDecimalEncodedBinary(opcode)),
  modifier(convertDecimalEncodedBinary(modifier)),
  format(Instruction::RegisterToRegister)
{
  allInstructions().insert(std::make_pair(mnemonic, this));
}

//===--------------------------- End of the file --------------------------===//