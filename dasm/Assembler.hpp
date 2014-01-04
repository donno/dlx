#ifndef DLX_ASSEMBLER_HPP_
#define DLX_ASSEMBLER_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Assembler
// NAMESPACE    : dlx::assembly
// PURPOSE      : Encapsulates the assembling of a DLX source file.
// COPYRIGHT    : (c) 2014 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
//
//===----------------------------------------------------------------------===//

#include "parser/Lexer.hpp"
#include "parser/SymbolTable.hpp"
#include "parser/Types.hpp"

#include <fstream>

#include <map>
#include <string>

namespace dlx
{
  namespace assembly
  {
    class Assembler
    {
      std::istream& mySource;
      dlx::assembly::Lexer myLexer;
      dlx::assembly::SymbolTable mySymbolTable;
      dlx::assembly::Label myPreviousLabel;
      unsigned long long myLocationCounter;

      void directive(const std::string& directive, const std::string& operand);

    public:
      Assembler(std::istream& source);

      void assemble();

      void printSymbolTable() const;
    };
  }
}

#endif

