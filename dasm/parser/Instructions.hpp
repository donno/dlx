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

      // This constructor is for register-to-register instructions.
      InstructionDefinition(
        const std::string& mnemonic, int opcode, int modifier);

      const std::string mnemonic;
      const int opcode;
      const int modifier; // This is only appliable to register-register format.
      const Instruction::Format format;
    };

    namespace instructions
    {
      typedef std::map<std::string, const InstructionDefinition*>
        InstructionMap;
      const InstructionMap& all();

      typedef InstructionDefinition Definition;

      // For C++14, the opcode can use binary literals.

      // The instructions which have an op code of 0 or 1 have a modifier which
      // isn't currently being captured here.
      const Definition add("add", 000000, 100000);
      const Definition addi("addi", 001000, Instruction::Immediate);
      const Definition addu("addu", 000000, 100001);
      const Definition addui("addui", 001001, Instruction::Immediate);
      const Definition and("and", 000000, 100100);
      const Definition andi("andi", 001100, Instruction::Immediate);
      const Definition beqz("beqz", 000100, Instruction::Immediate);
      const Definition bnez("bnez", 000101, Instruction::Immediate);
      const Definition halt("halt", 000000, 000001);
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
      const Definition movi2s("movi2s", 000000, 110000);
      const Definition movs2i("movs2i", 000000, 110001);
      const Definition nop("nop", 000000, 000000);
      const Definition or("or", 000000, 100101);
      const Definition ori("ori", 001101, Instruction::Immediate);
      const Definition rfe("rfe", 010000, Instruction::LongImmediate);
      const Definition sb("sb", 101000, Instruction::Immediate);
      const Definition seq("seq", 000000, 101000);
      const Definition seqi("seqi", 011000, Instruction::Immediate);
      const Definition sequ("sequ", 000000, 010000);
      const Definition sequi("sequi", 110000, Instruction::Immediate);
      const Definition sge("sge", 000000, 101101);
      const Definition sgei("sgei", 011101, Instruction::Immediate);
      const Definition sgeu("sgeu", 000000, 010101);
      const Definition sgeui("sgeui", 110101, Instruction::Immediate);
      const Definition sgt("sgt", 000000, 101011);
      const Definition sgti("sgti", 011011, Instruction::Immediate);
      const Definition sgtu("sgtu", 000000, 010011);
      const Definition sgtui("sgtui", 110011, Instruction::Immediate);
      const Definition sh("sh", 101001, Instruction::Immediate);
      const Definition sla("sla", 000000, 000100);
      const Definition slai("slai", 010100, Instruction::Immediate);
      const Definition sle("sle", 000000, 101100);
      const Definition slei("slei", 011100, Instruction::Immediate);
      const Definition sleu("sleu", 000000, 010100);
      const Definition sleui("sleui", 110100, Instruction::Immediate);
      const Definition sll("sll", 000000, 000100);
      const Definition slli("slli", 010100, Instruction::Immediate);
      const Definition slt("slt", 000000, 101010);
      const Definition slti("slti", 011010, Instruction::Immediate);
      const Definition sltu("sltu", 000000, 010010);
      const Definition sltui("sltui", 110010, Instruction::Immediate);
      const Definition sne("sne", 000000, 101001);
      const Definition snei("snei", 011001, Instruction::Immediate);
      const Definition sneu("sneu", 000000, 010001);
      const Definition sneui("sneui", 110001, Instruction::Immediate);
      const Definition sra("sra", 000000, 000111);
      const Definition srai("srai", 010111, Instruction::Immediate);
      const Definition srl("srl", 000000, 000110);
      const Definition srli("srli", 010110, Instruction::Immediate);
      const Definition sub("sub", 000000, 100010);
      const Definition subi("subi", 001010, Instruction::Immediate);
      const Definition subu("subu", 000000, 100011);
      const Definition subui("subui", 001011, Instruction::Immediate);
      const Definition sw("sw", 101011, Instruction::Immediate);
      const Definition trap("trap", 010001, Instruction::LongImmediate);
      const Definition wait("wait", 000000, 000010);
      const Definition xor("xor", 000000, 100110);
      const Definition xori("xori", 001110, Instruction::Immediate);
      const Definition addd("addd", 000001, 000100);
      const Definition addf("addf", 000001, 000000);
      const Definition bfpf("bfpf", 000111, Instruction::Immediate);
      const Definition bfpt("bfpt", 000110, Instruction::Immediate);
      const Definition cvtd2f("cvtd2f", 000001, 001010);
      const Definition cvtd2i("cvtd2i", 000001, 001011);
      const Definition cvtf2d("cvtf2d", 000001, 001000);
      const Definition cvtf2i("cvtf2i", 000001, 001001);
      const Definition cvti2d("cvti2d", 000001, 001101);
      const Definition cvti2f("cvti2f", 000001, 001100);
      const Definition div("div", 000001, 001111);
      const Definition divd("divd", 000001, 000111);
      const Definition divf("divf", 000001, 000011);
      const Definition divu("divu", 000001, 010111);
      const Definition eqd("eqd", 000001, 011000);
      const Definition eqf("eqf", 000001, 010000);
      const Definition ged("ged", 000001, 011101);
      const Definition gef("gef", 000001, 010101);
      const Definition gtd("gtd", 000001, 011011);
      const Definition gtf("gtf", 000001, 010011);
      const Definition led("led", 000001, 011100);
      const Definition lef("lef", 000001, 010100);
      const Definition ltd("ltd", 000001, 011010);
      const Definition ltf("ltf", 000001, 010010);
      const Definition movd("movd", 000000, 110011);
      const Definition movf("movf", 000000, 110010);
      const Definition movfp2i("movfp2i", 000000, 110100);
      const Definition movi2fp("movi2fp", 000000, 110101);
      const Definition mult("mult", 000001, 001110);
      const Definition multd("multd", 000001, 000110);
      const Definition multf("multf", 000001, 000010);
      const Definition multu("multu", 000001, 010110);
      const Definition ned("ned", 000001, 011001);
      const Definition nef("nef", 000001, 010001);
      const Definition sd("sd", 101111, Instruction::Immediate);
      const Definition sf("sf", 101110, Instruction::Immediate);
      const Definition subd("subd", 000001, 000101);
      const Definition subf("subf", 000001, 000001);

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

