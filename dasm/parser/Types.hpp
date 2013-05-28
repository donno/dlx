#ifndef DLX_TYPES_HPP_
#define DLX_TYPES_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Types
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides the types used for parsing the DLX assembly.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : Provides structes for storing information about the label,
//                comment, instruction and register read from the stream.
//
//
//===----------------------------------------------------------------------===//

#include <string>

namespace dlx
{
  namespace assembly
  {
    struct Label
    {
      std::string name;
    };

    struct Comment
    {
      std::string remark;

      // The character which identifies the remaining of the line as a comment.
      static const char Charachter;
    };

    struct Instruction
    {
      std::string mnemonic;
    };

    struct Register
    {
      char type; // r = integer, f = floating point.
      unsigned short number;
    };
  }
}

#endif
