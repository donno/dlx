//===----------------------------------------------------------------------===//
//
//                            DLX Assembler
//
// NAME         : dasm
// PURPOSE      : Provides main entry point for assembling DLX assembly.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// DESCRIPTION  : Presently this is only used to test the parsing.
//
//===----------------------------------------------------------------------===//

#include "Assembler.hpp"

#include "parser/Lexer.hpp"
#include "parser/Parser.hpp"
#include "parser/Instructions.hpp"
#include "parser/SymbolTable.hpp"
#include "parser/Types.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
  // Provides a convenient way of processing command line arguments.
  class ArgumentParser
  {
    std::string myProgramName;
    std::vector<std::string> myPositionalArugments;

    typedef std::vector<std::string>::const_iterator const_iterator;
    typedef std::vector<std::string>::size_type size_type;
  public:
    void parse(int argc, char* argv[]);

    // Get the positional arguments.
    const_iterator begin() const { return myPositionalArugments.begin(); }
    const_iterator end() const { return myPositionalArugments.end(); }
    size_type size() const { return myPositionalArugments.size(); }
    // Consider adding an operator[] for getting the positional arguments as well.
  };
}

void ArgumentParser::parse(int argc, char* argv[])
{
  myProgramName = std::string(argv[0]);
  myPositionalArugments.insert(
    myPositionalArugments.begin(), argv+1, argv + argc);
}

void assemble(const std::string& filename)
{
  std::cout << "Assembling " << filename << std::endl;
  std::ifstream file(filename);
  if (!file)
  {
    // This needs to flag to the main() that there was an error.
    std::cerr << "Failed to read: " << filename << std::endl;
    return;
  }

  dlx::assembly::Assembler assembler(file);
  assembler.assemble();
}

// TODO: Test cases
//
//  "add r1,r2, r3 ; Hello world"
//  "add r1,g2, f3 ; Hello world"
//  "add a1,g2, sag ; Hello world"
//
//   stream >> instruction >> rk >> ri >> rj;
int main(int argc, char* argv[])
{
  ArgumentParser arguments;
  // Register arguments.
  //
  //  -l   Generates a listing of your program and displays it to the terminal.
  //       The listing shows how the assembler translated the program and
  //       includes the symbol table.
  //
  //  -o <filename> The name of the object file or directory for saving objects
  //                if multiple source files are provided.
  //
  // The following two options are mutally exlusive:
  //   -a   Generate absoloute machine code.
  //   -r   Generate relocatable machine code.
  //
  // TODO: Implement the argument registration and usage.
  arguments.parse(argc, argv);

  if (arguments.size() > 0)
  {
    // Assemble the source files provided on the command line.
    std::for_each(arguments.begin(), arguments.end(), assemble);
    return 0;
  }

  using namespace dlx::assembly;

  // Example of an alternative parser, aimed at being typed and easier to read.
  {
    const std::string line("add r1,r2, r3 ; Hello world");

    Instruction instruction;
    // Determine the format based on the instruction, for now assume register to
    // register.
    Register ri, rj, rk;
    Comment comment;
    // It would be nice to sink the rest into a comment.

    std::istringstream stream(line);
    stream >> instruction >> rk >> ri >> rj >> comment;

    std::cout << rk.number << std::endl;
    std::cout << comment.remark << std::endl;
  }

  // Another example, this time starting with a label.
  {
    const std::string line("start: add r1, r2, r3 ; Hello world");

    Label label;
    Instruction instruction;
    // Determine the format based on the instruction, for now assume register to
    // register.
    Register ri, rj, rk;
    Comment comment;

    std::istringstream stream(line);
    stream >> label >> instruction >> rk >> ri >> rj >> comment;

    std::cout << label.name << std::endl;
    std::cout << rk.number << std::endl;
    std::cout << comment.remark << std::endl;
  }

  // Third example, this time determining how to parse it.
  {
    std::cout << std::endl
              << "Third example, this time determining how to parse it."
              << std::endl;

    Label label;
    Instruction instruction;
    Register ri, rj, rk;
    Comment comment;

    const std::string line("start: add r1, r2, r3 ; Hello world");
    std::istringstream stream(line);

    if (startsWithLabel(stream))
    {
      stream >> label >> instruction >> rk >> ri >> rj >> comment;
      std::cout << "Label: " << label.name << std::endl;
    }
    else
    {
      stream >> instruction >> rk >> ri >> rj >> comment;
      std::cout << "Instruction: " << instruction.mnemonic << std::endl;
    }
  }

  // Test the instructions
  {
    using namespace dlx::assembly::instructions;
    Instruction instruction; Register ri, rj, rk; Comment comment;

    const std::string line("add r1,r2, r3 ; Hello world");
    std::istringstream stream(line);
    stream >> instruction;

    // Determine what to extract next based on the format of the instruction.
    switch (instruction.format)
    {
      case Instruction::LongImmediate:
        // NYI: Support for extracting a Lsgn/Lsgn is not yet supported.
        std::cerr << "Not supported: extracting an instruction with an ommedate"
                  << std::endl;
        break;
      case Instruction::Immediate:
        // NYI: Support for extracting a Ksgn/Ksgn is not yet supported.
        std::cerr << "Not supported: extracting an instruction with an ommedate"
                  << std::endl;
        break;
      case Instruction::RegisterToRegister:
        // This is followed by register, register and another register.
        stream >> rk >> ri >> rj >> comment;

        std::cout
        << "r" << rk.number << " = r" << ri.number
        << " " << instruction.mnemonic << " r" << rj.number
        << " // " << comment.remark
        << std::endl;
        break;
      default:
        std::cerr << "Unknown" << std::endl;
    };
  }
};
