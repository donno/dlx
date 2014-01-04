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

#include <map>
#include <string>

namespace dlx
{
  namespace assembly
  {
    struct InstructionDefinition
    {
      // TODO: Convert opcode from a binary literal encoded as decimal to
      // the appropriate value.
      InstructionDefinition(
        const std::string& mnemonic, int opcode, Instruction::Format format);

      const std::string mnemonic;
      const int opcode;
      const Instruction::Format format;
    };

    namespace instructions
    {
      typedef std::map<std::string, InstructionDefinition*> InstructionMap;
      const InstructionMap& all();

      typedef InstructionDefinition Definition;

      // For C++14, the opcode can use binary literals.

      // The instructions which have an op code of 0 or 1 have a modifier which
      // isn't currently being captured here.
      const Definition add("add", 000000, Instruction::RegisterToRegister);
      const Definition addi("addi", 001000, Instruction::Immediate);
      const Definition addu("addu", 000000, Instruction::RegisterToRegister);
      const Definition addui("addui", 001001, Instruction::Immediate);
      const Definition and("and", 000000, Instruction::RegisterToRegister);
      const Definition andi("andi", 001100, Instruction::Immediate);
      const Definition beqz("beqz", 000100, Instruction::Immediate);
      const Definition bnez("bnez", 000101, Instruction::Immediate);
      const Definition halt("halt", 000000, Instruction::RegisterToRegister);
      const Definition j("j", 000010, Instruction::LongImmediate);
      const Definition jal("jal", 000011, Instruction::LongImmediate);
      const Definition jalr("jalr", 010011, Instruction::Immediate);
      const Definition jr("jr", 010010, Instruction::Immediate);
      const Definition lb("lb", 100000, Instruction::Immediate);
      const Definition lbu("lbu", 100100, Instruction::Immediate);
      const Definition lh("lh", 100001, Instruction::Immediate);
      const Definition lhi("lhi", 001111, Instruction::Immediate);
      const Definition lhu("lhu", 100101, Instruction::Immediate);
      const Definition lw("lw", 100011, Instruction::Immediate);
      const Definition movi2s("movi2s", 000000, Instruction::RegisterToRegister);
      const Definition movs2i("movs2i", 000000, Instruction::RegisterToRegister);
      const Definition or("or", 000000, Instruction::RegisterToRegister);
      const Definition ori("ori", 001101, Instruction::Immediate);
      const Definition sb("sb", 101000, Instruction::Immediate);
      const Definition seq("seq", 000000, Instruction::RegisterToRegister);
      const Definition seqi("seqi", 011000, Instruction::Immediate);
      const Definition sequ("sequ", 000000, Instruction::RegisterToRegister);
      const Definition sequi("sequi", 110000, Instruction::Immediate);
      const Definition sge("sge", 000000, Instruction::RegisterToRegister);
      const Definition sgei("sgei", 011101, Instruction::Immediate);
      const Definition sgeu("sgeu", 000000, Instruction::RegisterToRegister);
      const Definition sgeui("sgeui", 110101, Instruction::Immediate);
      const Definition sgt("sgt", 000000, Instruction::RegisterToRegister);
      const Definition sgti("sgti", 011011, Instruction::Immediate);
      const Definition sgtu("sgtu", 000000, Instruction::RegisterToRegister);
      const Definition sgtui("sgtui", 110011, Instruction::Immediate);
      const Definition sh("sh", 101001, Instruction::Immediate);
      const Definition sla("sla", 000000, Instruction::RegisterToRegister);
      const Definition slai("slai", 010100, Instruction::Immediate);
      const Definition sle("sle", 000000, Instruction::RegisterToRegister);
      const Definition slei("slei", 011100, Instruction::Immediate);
      const Definition sleu("sleu", 000000, Instruction::RegisterToRegister);
      const Definition sleui("sleui", 110100, Instruction::Immediate);
      const Definition sll("sll", 000000, Instruction::RegisterToRegister);
      const Definition slli("slli", 010100, Instruction::Immediate);
      const Definition slt("slt", 000000, Instruction::RegisterToRegister);
      const Definition slti("slti", 011010, Instruction::Immediate);
      const Definition sltu("sltu", 000000, Instruction::RegisterToRegister);
      const Definition sltui("sltui", 110010, Instruction::Immediate);
      const Definition sne("sne", 000000, Instruction::RegisterToRegister);
      const Definition snei("snei", 011001, Instruction::Immediate);
      const Definition sneu("sneu", 000000, Instruction::RegisterToRegister);
      const Definition sneui("sneui", 110001, Instruction::Immediate);
      const Definition sra("sra", 000000, Instruction::RegisterToRegister);
      const Definition srai("srai", 010111, Instruction::Immediate);
      const Definition srl("srl", 000000, Instruction::RegisterToRegister);
      const Definition srli("srli", 010110, Instruction::Immediate);
      const Definition sub("sub", 000000, Instruction::RegisterToRegister);
      const Definition subi("subi", 001010, Instruction::Immediate);
      const Definition subu("subu", 000000, Instruction::RegisterToRegister);
      const Definition subui("subui", 001011, Instruction::Immediate);
      const Definition sw("sw", 101011, Instruction::Immediate);
      const Definition trap("trap", 010001, Instruction::LongImmediate);
      const Definition xor("xor", 000000, Instruction::RegisterToRegister);
      const Definition xori("xori", 001110, Instruction::Immediate);

      // The following are pseudo instructions, i.e they are shorthand that map
      // to other instructions.
      //
      // At the moment, there is no Instruction::Format for these.
      const Definition clr("clr", 001000, Instruction::Immediate);
      const Definition bf("bf", 000100, Instruction::Immediate); // beq
      const Definition bt("bt", 000101, Instruction::Immediate); // bnez
    }
  }
}

#endif

