#ifndef DLX_SYMBOL_TABLE_HPP_
#define DLX_SYMBOL_TABLE_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : SymbolTable
// NAMESPACE    : dlx::assembly
// PURPOSE      : Stores the symbols seen and their value in the assembler.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
//
//===----------------------------------------------------------------------===//

#include <map>
#include <string>

namespace dlx
{
  namespace assembly
  {
    typedef std::map<std::string, std::string> SymbolTable;

    // class SymbolTable
    // {
    // };
  }
}

#endif

