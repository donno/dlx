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
      explicit InstructionDefinition(
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
      const Definition add("add", 0, 32);
      const Definition addi("addi", 8, Instruction::Immediate);
      const Definition addu("addu", 0, 33);
      const Definition addui("addui", 9, Instruction::Immediate);
      const Definition and_("and", 0, 36);
      const Definition andi("andi", 12, Instruction::Immediate);
      const Definition beqz("beqz", 4, Instruction::Immediate);
      const Definition bnez("bnez", 5, Instruction::Immediate);
      const Definition halt("halt", 0, 1);
      const Definition j("j", 2, Instruction::LongImmediate);
      const Definition jal("jal", 3, Instruction::LongImmediate);
      const Definition jalr("jalr", 19, Instruction::Immediate);
      const Definition jr("jr", 18, Instruction::Immediate);
      const Definition lb("lb", 32, Instruction::Immediate);
      const Definition lbu("lbu", 36, Instruction::Immediate);
      const Definition lh("lh", 33, Instruction::Immediate);
      const Definition lhi("lhi", 15, Instruction::Immediate);
      const Definition lhu("lhu", 37, Instruction::Immediate);
      const Definition lw("lw", 35, Instruction::Immediate);
      const Definition movi2s("movi2s", 0, 48);
      const Definition movs2i("movs2i", 0, 49);
      const Definition nop("nop", 0, 0);
      const Definition or_("or", 0, 37);
      const Definition ori("ori", 13, Instruction::Immediate);
      const Definition rfe("rfe", 16, Instruction::LongImmediate);
      const Definition sb("sb", 40, Instruction::Immediate);
      const Definition seq("seq", 0, 40);
      const Definition seqi("seqi", 24, Instruction::Immediate);
      const Definition sequ("sequ", 0, 16);
      const Definition sequi("sequi", 48, Instruction::Immediate);
      const Definition sge("sge", 0, 45);
      const Definition sgei("sgei", 29, Instruction::Immediate);
      const Definition sgeu("sgeu", 0, 21);
      const Definition sgeui("sgeui", 53, Instruction::Immediate);
      const Definition sgt("sgt", 0, 43);
      const Definition sgti("sgti", 27, Instruction::Immediate);
      const Definition sgtu("sgtu", 0, 19);
      const Definition sgtui("sgtui", 51, Instruction::Immediate);
      const Definition sh("sh", 41, Instruction::Immediate);
      const Definition sla("sla", 0, 4);
      const Definition slai("slai", 20, Instruction::Immediate);
      const Definition sle("sle", 0, 44);
      const Definition slei("slei", 28, Instruction::Immediate);
      const Definition sleu("sleu", 0, 20);
      const Definition sleui("sleui", 52, Instruction::Immediate);
      const Definition sll("sll", 0, 4);
      const Definition slli("slli", 20, Instruction::Immediate);
      const Definition slt("slt", 0, 42);
      const Definition slti("slti", 26, Instruction::Immediate);
      const Definition sltu("sltu", 0, 18);
      const Definition sltui("sltui", 50, Instruction::Immediate);
      const Definition sne("sne", 0, 41);
      const Definition snei("snei", 25, Instruction::Immediate);
      const Definition sneu("sneu", 0, 17);
      const Definition sneui("sneui", 49, Instruction::Immediate);
      const Definition sra("sra", 0, 7);
      const Definition srai("srai", 23, Instruction::Immediate);
      const Definition srl("srl", 0, 6);
      const Definition srli("srli", 22, Instruction::Immediate);
      const Definition sub("sub", 0, 34);
      const Definition subi("subi", 10, Instruction::Immediate);
      const Definition subu("subu", 0, 35);
      const Definition subui("subui", 11, Instruction::Immediate);
      const Definition sw("sw", 43, Instruction::Immediate);
      const Definition trap("trap", 17, Instruction::LongImmediate);
      const Definition wait("wait", 0, 2);
      const Definition xor_("xor", 0, 38);
      const Definition xori("xori", 14, Instruction::Immediate);
      const Definition addd("addd", 1, 4);
      const Definition addf("addf", 1, 0);
      const Definition bfpf("bfpf", 7, Instruction::Immediate);
      const Definition bfpt("bfpt", 6, Instruction::Immediate);
      const Definition cvtd2f("cvtd2f", 1, 10);
      const Definition cvtd2i("cvtd2i", 1, 11);
      const Definition cvtf2d("cvtf2d", 1, 8);
      const Definition cvtf2i("cvtf2i", 1, 9);
      const Definition cvti2d("cvti2d", 1, 13);
      const Definition cvti2f("cvti2f", 1, 12);
      const Definition div("div", 1, 15);
      const Definition divd("divd", 1, 7);
      const Definition divf("divf", 1, 3);
      const Definition divu("divu", 1, 23);
      const Definition eqd("eqd", 1, 24);
      const Definition eqf("eqf", 1, 16);
      const Definition ged("ged", 1, 29);
      const Definition gef("gef", 1, 21);
      const Definition gtd("gtd", 1, 27);
      const Definition gtf("gtf", 1, 19);
      const Definition led("led", 1, 28);
      const Definition lef("lef", 1, 20);
      const Definition ltd("ltd", 1, 26);
      const Definition ltf("ltf", 1, 18);
      const Definition movd("movd", 0, 51);
      const Definition movf("movf", 0, 50);
      const Definition movfp2i("movfp2i", 0, 52);
      const Definition movi2fp("movi2fp", 0, 53);
      const Definition mult("mult", 1, 14);
      const Definition multd("multd", 1, 6);
      const Definition multf("multf", 1, 2);
      const Definition multu("multu", 1, 22);
      const Definition ned("ned", 1, 25);
      const Definition nef("nef", 1, 17);
      const Definition sd("sd", 47, Instruction::Immediate);
      const Definition sf("sf", 46, Instruction::Immediate);
      const Definition subd("subd", 1, 5);
      const Definition subf("subf", 1, 1);

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

