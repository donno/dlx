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

#include "parser/Parser.hpp"
#include "parser/Types.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

// TODO: Test cases
//
//  "add r1,r2, r3 ; Hello world"
//  "add r1,g2, f3 ; Hello world"
//  "add a1,g2, sag ; Hello world"
//
//   stream >> instruction >> rk >> ri >> rj;
int main()
{
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

};
