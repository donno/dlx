//===----------------------------------------------------------------------===//
//
//                       DLX Instruction Set Emulator
//
// NAME         : Instructions
// NAMESPACE    : dlx::hardware
// PURPOSE      : Provides access to functions for performing the instructions.
// COPYRIGHT    : (c) 2015 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : TODO Document.
//
//===----------------------------------------------------------------------===//

#include "Instructions.hpp"

#include "Machine.hpp"
#include "Instruction.hpp"

#include <iostream>

// Disable the warning about unused variables until all the instructions are
// implemented.
#ifdef _MSC_VER
#pragma warning(disable : 4100)
#pragma warning(disable : 4189)
#endif

static void HandleFormatRInstructions(dlx::hardware::DLXMachine* machine)
{
  const auto instruction =
    machine->instruction(dlx::hardware::InstructionRegisterToRegister());
  std::cout << "Executing a format R instruction modifer="
            <<  instruction.modifier
            << std::endl;
  if (dlx::hardware::InstructionsFormatR[instruction.modifier])
  {
    dlx::hardware::InstructionsFormatR[instruction.modifier](machine);
  }
  else
  {
    std::cerr << "Unimplemented instruction." << std::endl;
  }
}

static void HandleFormatFInstructions(dlx::hardware::DLXMachine*)
{
  std::cerr << "Floating point instructions are not supported." << std::endl;
}

static void HandleIllegalInstruction(dlx::hardware::DLXMachine*)
{
  std::cerr << "There is no instruction for this given opcode, making this an "
               "illegal instruction." << std::endl;
}

namespace dlx
{
	namespace instructions
	{
		template<typename Format>
		struct Base
		{
		  typedef Format format_type;

		  // Reurns the instruction ecoding for the given instruction as read
		  // from the machine.
		  static format_type Instruction(hardware::DLXMachine* machine);
		};

    struct add : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct addi : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct addu : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct addui : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct and : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct andi : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct beqz : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct bnez : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct halt : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct j : Base<hardware::InstructionLongImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct jal : Base<hardware::InstructionLongImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct jalr : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct jr : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct lb : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct lbu : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct lh : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct lhi : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct lhu : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct lw : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct movi2s : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct movs2i : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct nop : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct or : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct ori : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct rfe : Base<hardware::InstructionLongImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sb : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct seq : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct seqi : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sequ : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sequi : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sge : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sgei : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sgeu : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sgeui : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sgt : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sgti : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sgtu : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sgtui : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sh : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sla : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct slai : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sle : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct slei : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sleu : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sleui : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sll : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct slli : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct slt : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct slti : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sltu : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sltui : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sne : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct snei : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sneu : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sneui : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sra : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct srai : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct srl : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct srli : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sub : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct subi : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct subu : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct subui : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct sw : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct trap : Base<hardware::InstructionLongImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct wait : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct xor : Base<hardware::InstructionRegisterToRegister>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };

	  struct xori : Base<hardware::InstructionImmediate>
	  {
	    static void execute(hardware::DLXMachine* machine);
	  };
	}
}

template<typename Format>
Format dlx::instructions::Base<Format>::Instruction(hardware::DLXMachine* machine)
{
  return machine->instruction(Format());
}

// Provides implementations for the instructions here.
void dlx::instructions::add::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing add" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri] +
    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::addi::execute(hardware::DLXMachine* machine)
{
  const auto instruction = Instruction(machine);
  std::cout << "Performing addi r" << instruction.rj
            << " = r" << instruction.ri << " + " << instruction.Ksgn
            << std::endl;
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri] + instruction.Ksgn;
}

void dlx::instructions::addu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing addu" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri] +
    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::addui::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing addui" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri] + instruction.Ksgn;
}

void dlx::instructions::and::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing and" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri] &
    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::andi::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing andi" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri] & instruction.Ksgn;
}

void dlx::instructions::beqz::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing beqz" << std::endl;
  // if ri == 0 then pc = pc + SignExt(Ksgn)
  const auto instruction = Instruction(machine);
  if (machine->ConstRegisters()[instruction.ri].value ==0)
  {
    machine->SetProgramCounter(machine->ProgramCounter() + instruction.Ksgn);
  }
}

void dlx::instructions::bnez::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing bnez" << std::endl;
  // if ri != 0 then pc = pc + SignExt(Ksgn)
  const auto instruction = Instruction(machine);
  if (machine->ConstRegisters()[instruction.ri].value !=0)
  {
    machine->SetProgramCounter(machine->ProgramCounter() + instruction.Ksgn);
  }
}

void dlx::instructions::halt::execute(hardware::DLXMachine*)
{
  std::cout << "Halting..." << std::endl;
}

void dlx::instructions::j::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing j" << std::endl;
  const auto instruction = Instruction(machine);
}

void dlx::instructions::jal::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing jal" << std::endl;
  // r31 = pc; pc = pc + SignExt(Lsgn)
  const auto instruction = Instruction(machine);
  machine->Registers()[31] = machine->ProgramCounter();
  machine->SetProgramCounter(machine->ProgramCounter() + instruction.Lsgn);
}

void dlx::instructions::jalr::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing jalr" << std::endl;
  const auto instruction = Instruction(machine);
}

void dlx::instructions::jr::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing jr" << std::endl;
  // pc = ri
  const auto instruction = Instruction(machine);
  machine->SetProgramCounter(machine->ConstRegisters()[instruction.ri].value);
}

void dlx::instructions::lb::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing lb" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::lbu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing lbu" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::lh::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing lh" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::lhi::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing lhi" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::lhu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing lhu" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::lw::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing lw" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::movi2s::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing movi2s" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rk] =
//    machine->ConstRegisters()[instruction.ri] OP
//    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::movs2i::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing movs2i" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rk] =
//    machine->ConstRegisters()[instruction.ri] OP
//    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::nop::execute(hardware::DLXMachine*)
{
}

void dlx::instructions::or::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing or" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri] |
    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::ori::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing ori" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri] | instruction.Ksgn;
}

void dlx::instructions::rfe::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing rfe" << std::endl;
  const auto instruction = Instruction(machine);

}

void dlx::instructions::sb::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sb" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::seq::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing seq" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    (machine->ConstRegisters()[instruction.ri] ==
     machine->ConstRegisters()[instruction.rj]) ? 1 : 0;
}

void dlx::instructions::seqi::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing seqi" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    (machine->ConstRegisters()[instruction.ri] == instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sequ::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sequ" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    (machine->ConstRegisters()[instruction.ri] ==
     machine->ConstRegisters()[instruction.rj]) ? 1 : 0;
}

void dlx::instructions::sequi::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sequi" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] =
    (riValue == instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sge::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sge" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue <= rjValue) ? 0 : 1;
}

void dlx::instructions::sgei::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sgei" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] =
    (riValue >= instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sgeu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sgeu" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue >= rjValue) ? 1 : 0;
}

void dlx::instructions::sgeui::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sgeui" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] =
    (riValue >= instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sgt::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sgt" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue > rjValue) ? 1 : 0;
}

void dlx::instructions::sgti::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sgti" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] = (riValue > instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sgtu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sgtu" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue > rjValue) ? 1 : 0;
}

void dlx::instructions::sgtui::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sgtui" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] = (riValue > instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sh::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sh" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::sla::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sla" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = riValue << rjValue;
}

void dlx::instructions::slai::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing slai" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri].value << instruction.Ksgn;
}

void dlx::instructions::sle::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sle" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue <= rjValue) ? 1 : 0;
}

void dlx::instructions::slei::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing slei" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] =
    (riValue <= instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sleu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sleu" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue <= rjValue) ? 1 : 0;
}

void dlx::instructions::sleui::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sleui" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] =
    (riValue <= instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sll::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sll" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = riValue << rjValue;
}

void dlx::instructions::slli::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing slli" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] = riValue << instruction.Kusn;
}

void dlx::instructions::slt::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing slt" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue < rjValue) ? 1 : 0;
}

void dlx::instructions::slti::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing slti" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  std::cout << std::dec << "slti (" << riValue << " < " << instruction.Ksgn << ")"
            << std::endl;
  machine->Registers()[instruction.rj] =
    (riValue < instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sltu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sltu" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  const auto rjValue = machine->ConstRegisters()[instruction.rj].value;
  machine->Registers()[instruction.rk] = (riValue < rjValue) ? 1 : 0;
}

void dlx::instructions::sltui::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sltui" << std::endl;
  const auto instruction = Instruction(machine);
  const auto riValue = machine->ConstRegisters()[instruction.ri].value;
  machine->Registers()[instruction.rj] = (riValue < instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sne::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sne" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    (machine->ConstRegisters()[instruction.ri] !=
     machine->ConstRegisters()[instruction.rj]) ? 1 : 0;
}

void dlx::instructions::snei::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing snei" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    (machine->ConstRegisters()[instruction.ri] != instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sneu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sneu" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri] !=
    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::sneui::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sneui" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    (machine->ConstRegisters()[instruction.ri] != instruction.Ksgn) ? 1 : 0;
}

void dlx::instructions::sra::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sra" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri].value >>
    machine->ConstRegisters()[instruction.rj].value;
}

void dlx::instructions::srai::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing srai" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri].value >> instruction.Ksgn;
}

void dlx::instructions::srl::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing srl" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri].value >>
    machine->ConstRegisters()[instruction.rj].value;
}

void dlx::instructions::srli::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing srli" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri].value >> instruction.Ksgn;
}

void dlx::instructions::sub::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sub" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk].value =
    machine->ConstRegisters()[instruction.ri] -
    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::subi::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing subi" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri] - instruction.Ksgn;
}

void dlx::instructions::subu::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing subu" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri] -
    machine->ConstRegisters()[instruction.rj];
}

void dlx::instructions::subui::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing subui" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri] - instruction.Ksgn;
}

void dlx::instructions::sw::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing sw" << std::endl;
  const auto instruction = Instruction(machine);
//  machine->Registers()[instruction.rj] =
//    machine->ConstRegisters()[instruction.ri] OP instruction.Ksgn;
}

void dlx::instructions::trap::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing trap" << std::endl;
  const auto instruction = Instruction(machine);

}

void dlx::instructions::wait::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing wait" << std::endl;
  const auto instruction = Instruction(machine);
}

void dlx::instructions::xor::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing xor" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rk] =
    machine->ConstRegisters()[instruction.ri].value ^
    machine->ConstRegisters()[instruction.rj].value;
}

void dlx::instructions::xori::execute(hardware::DLXMachine* machine)
{
  std::cout << "Performing xori" << std::endl;
  const auto instruction = Instruction(machine);
  machine->Registers()[instruction.rj] =
    machine->ConstRegisters()[instruction.ri].value ^ instruction.Ksgn;
}

// Define an array pointing to the execute function for the instructions.
dlx::hardware::ExecuteInstruction dlx::hardware::Instructions[] = {
  HandleFormatRInstructions,
  HandleFormatFInstructions,
  dlx::instructions::j::execute,
  dlx::instructions::jal::execute,
  dlx::instructions::beqz::execute,
  dlx::instructions::bnez::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  dlx::instructions::addi::execute,
  dlx::instructions::addui::execute,
  dlx::instructions::subi::execute,
  dlx::instructions::subui::execute,
  dlx::instructions::andi::execute,
  dlx::instructions::ori::execute,
  dlx::instructions::xori::execute,
  dlx::instructions::lhi::execute,
  dlx::instructions::rfe::execute,
  dlx::instructions::trap::execute,
  dlx::instructions::jr::execute,
  dlx::instructions::jalr::execute,
  dlx::instructions::slai::execute,
  HandleIllegalInstruction,
  dlx::instructions::srli::execute,
  dlx::instructions::srai::execute,
  dlx::instructions::seqi::execute,
  dlx::instructions::snei::execute,
  dlx::instructions::slti::execute,
  dlx::instructions::sgti::execute,
  dlx::instructions::slei::execute,
  dlx::instructions::sgei::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  dlx::instructions::lb::execute,
  dlx::instructions::lh::execute,
  HandleIllegalInstruction,
  dlx::instructions::lw::execute,
  dlx::instructions::lbu::execute,
  dlx::instructions::lhu::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  dlx::instructions::sb::execute,
  dlx::instructions::sh::execute,
  HandleIllegalInstruction,
  dlx::instructions::sw::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  dlx::instructions::sequi::execute,
  dlx::instructions::sneui::execute,
  dlx::instructions::sltui::execute,
  dlx::instructions::sgtui::execute,
  dlx::instructions::sleui::execute,
  dlx::instructions::sgeui::execute,
};

dlx::hardware::ExecuteInstruction dlx::hardware::InstructionsFormatR[] = {
  dlx::instructions::nop::execute,
  dlx::instructions::halt::execute,
  dlx::instructions::wait::execute,
  HandleIllegalInstruction,
  dlx::instructions::sll::execute,
  HandleIllegalInstruction,
  dlx::instructions::srl::execute,
  dlx::instructions::sra::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  dlx::instructions::sequ::execute,
  dlx::instructions::sneu::execute,
  dlx::instructions::sltu::execute,
  dlx::instructions::sgtu::execute,
  dlx::instructions::sleu::execute,
  dlx::instructions::sgeu::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  dlx::instructions::add::execute,
  dlx::instructions::addu::execute,
  dlx::instructions::sub::execute,
  dlx::instructions::subu::execute,
  dlx::instructions::and::execute,
  dlx::instructions::or::execute,
  dlx::instructions::xor::execute,
  HandleIllegalInstruction,
  dlx::instructions::seq::execute,
  dlx::instructions::sne::execute,
  dlx::instructions::slt::execute,
  dlx::instructions::sgt::execute,
  dlx::instructions::sle::execute,
  dlx::instructions::sge::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  dlx::instructions::movi2s::execute,
  dlx::instructions::movs2i::execute,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
  HandleIllegalInstruction,
};

//===--------------------------- End of the file --------------------------===//