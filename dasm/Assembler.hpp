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

#include <cstdint>
#include <map>
#include <string>

namespace dlx
{
  namespace assembly
  {
    class Assembler
    {
      std::string myFilename;
      std::istream& mySource;
      dlx::assembly::Lexer myLexer;
      dlx::assembly::SymbolTable mySymbolTable;
      dlx::assembly::Label myPreviousLabel;
      unsigned long long myLocationCounter;
      bool isListingGenerated;

      void error(const char* message) const;
      void directive(const std::string& directive, const std::string& operand);

      // Evaluates an immediate.
      //
      // This means if was a numeric constant the value is returned.
      // Otherwise if it is a symbol the value is looked up in the symbol table.
      uint16_t evaluate(const Immediate& immediate);
      uint32_t evaluate(const LongImmediate& immediate);

    public:
      Assembler(const std::string& filename, std::istream& source,
                bool outputListing);

      void assemble();

      void printSymbolTable() const;
    };
  }
}

#endif

