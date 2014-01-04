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
#include <iomanip>
#include <sstream>

void dlx::assembly::Assembler::error(const char* message) const
{
  // TODO: Add line and column.
  std::cerr << myFilename << ":error:" << message << std::endl;
}

void dlx::assembly::Assembler::directive(
  const std::string& directive,
  const std::string& operand)
{
  // Handle an assembly directive.
  if (directive == ".equ")
  {
    // .equ tells the assembler to assign the previous label the value
    // operand.
    mySymbolTable[myPreviousLabel.name] = operand;
  }
  else if (directive == ".start")
  {
    // .start tells the assembler to record where the program should begin
    // execution.
    //
    // This information is stored in symbol table to store under the name
    // #.start which is name that can't be used in the source code.
    const std::string symbolName = '#' + directive;
    const auto position = mySymbolTable.lower_bound(symbolName);
    if (position != mySymbolTable.end() && position->first == symbolName)
    {
      error("Start address redefined");
    }
    else
    {
      mySymbolTable.insert(position, std::make_pair(symbolName, operand));
    }
  }
  else if (directive == ".word")
  {
    // .word tells the assembler to allocate space at the current location for
    // storing a word as well as the value to store in it.

    // TODO: Actually read the operand and store the value.

    myLocationCounter += 4;
  }
  else if (directive == ".space")
  {
    // .space tells the assembler to allocate space at the current location.

    // TODO: Write a better operand parser for directives which returns the
    // number.

    std::locale locale;
    if (std::all_of(operand.cbegin(), operand.cend(),
                    [&](char c) { return std::isdigit(c, locale) != 0; }))
    {
      // Convert numbers to integers then output them as hex.
      std::stringstream stream(operand);
      long long value;
      stream >> value;

      // TODO: This will need to allocate the space in the output object.

      myLocationCounter += value;
    }
    else
    {
      std::cerr << "can't handle this .space directive: " << operand
                << std::endl;
    }
  }
  else
  {
    std::cout << "Directive: " << directive << std::endl;
  }
}

dlx::assembly::Assembler::Assembler(
  const std::string& filename,
  std::istream& source)
: myFilename(filename),
  mySource(source),
  myLexer(source),
  mySymbolTable(),
  myPreviousLabel(),
  myLocationCounter(0)
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
      mySymbolTable[myPreviousLabel.name] =
        std::to_string(myLocationCounter);
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

void dlx::assembly::Assembler::printSymbolTable() const
{
  std::locale locale;

  std::cout << "=======================" << std::endl;
  std::cout << "S Y M B O L   T A B L E" << std::endl;
  std::cout << "=======================" << std::endl;
  std::cout << "Name       | Value" << std::endl;
  for (auto symbol = mySymbolTable.cbegin(); symbol != mySymbolTable.cend();
       ++symbol)
  {
    // Check if symbol is an internal symbol not defined by the programmer which
    // shouln't be shown in the output of this table.
    if (symbol->first.compare(0, 1, "#") == 0) continue;

    std::cout << std::left << std::setfill(' ') << std::setw(10);

    if (std::all_of(symbol->second.cbegin(), symbol->second.cend(),
                    [&](char c) { return std::isdigit(c, locale) != 0; }))
    {
      // Convert numbers to integers then output them as hex.
      std::stringstream stream(symbol->second);
      long long value;
      stream >> value;
      std::cout << symbol->first << " | "
                << std::hex << std::uppercase << value << std::endl;
    }
    else if (symbol->second.compare(0, 3, "16#") == 0)
    {
      // The symbol is already in hex so strip of the prefix.
      //
      // TODO: The hex should probably already be parsed to a decimal number
      // sooner.
      std::cout << symbol->first << " | " << symbol->second.substr(3)
                << std::endl;
    }
    else
    {
      std::cout << symbol->first << " | " << symbol->second << std::endl;
    }
  }
}

//===--------------------------- End of the file --------------------------===//