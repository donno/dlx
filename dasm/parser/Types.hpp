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

      enum Format
      {
        // Returned when the format is not known.
        Unknown,
        // This is followed by Lsgn/Lusn where L is 26-bit (number/label).
        LongImmediate, 
        // This is followed by register, register, Ksgn/Usgn, where K is 16-bit.
        Immediate,
        // This is followed by register, register and another register.
        RegisterToRegister
      };
      
      Format format; 
    };

    struct Register
    {
      char type; // r = integer, f = floating point.
      unsigned short number;
    };
  }
}

#endif
