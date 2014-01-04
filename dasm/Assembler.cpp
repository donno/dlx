//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Assembler
// NAMESPACE    : dlx::assembly
// PURPOSE      : Encapsulates the assembling of a DLX source file.
// LICENSE      : The MIT License (see LICENSE.txt)
// COPYRIGHT    : (c) 2014 Sean Donnellan.
//
//===----------------------------------------------------------------------===//

#include "Assembler.hpp"

#include "parser/Lexer.hpp"
#include "parser/Parser.hpp"
#include "parser/SymbolTable.hpp"
#include "parser/Types.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

void dlx::assembly::Assembler::directive(
  const std::string& directive,
  const std::string& operand)
{
  // Handle an assembly directive.
  std::cout << "Directive: " << directive << std::endl;
  if (directive == ".equ")
  {
    // .equ tells the assembler to assign the previous label the value
    // operand.
    std::cout << myPreviousLabel.name << "\tequ\t" << operand << std::endl;
  }
}

dlx::assembly::Assembler::Assembler(std::istream& source)
: mySource(source),
  myLexer(source)
{
}

void dlx::assembly::Assembler::assemble()
{
  while (!mySource.eof())
  {
    const dlx::assembly::Token token = myLexer.Next();
    switch (token.type)
    {
    case dlx::assembly::Token::Comment:
      continue;
    case dlx::assembly::Token::Label:
    {
      // Convert the token into a strongly typed label.
      std::istringstream source(token.value);
      source >> myPreviousLabel;
      std::cout << "Label: " << myPreviousLabel.name << std::endl;
      break;
    }
    case dlx::assembly::Token::Instruction:
    {
      dlx::assembly::Instruction instruction;
      std::istringstream source(token.value);
      source >> instruction;
      if (instruction.format == dlx::assembly::Instruction::Directive)
      {
        std::string operand;
        source >> operand;
        directive(instruction.mnemonic, operand);
      }
      else
      {
        std::cout << "Instruction: " << instruction.mnemonic << std::endl;
      }
      break;
    }
    }
  }
}

//===--------------------------- End of the file --------------------------===//