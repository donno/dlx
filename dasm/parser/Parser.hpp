#ifndef DLX_PARSER_HPP_
#define DLX_PARSER_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Parser
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides operators and functions for parsing DLX assembly.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : Provides the >> operators for extracting the definition of a
//                label, instruction, register and comment from a character
//                stream.
//
//
//===----------------------------------------------------------------------===//

#include <istream>

namespace dlx
{
  namespace assembly
  {
    struct Comment;
    struct Instruction;
    struct Label;
    struct Register;

    // Determine if there the current line starts with a label.
    bool startsWithLabel(std::istream& source);

    std::istream& operator >>(std::istream& source, Label& label);
    std::istream& operator >>(std::istream& source, Instruction& instruction);
    std::istream& operator >>(std::istream& source, Comment& comment);
    std::istream& operator >>(std::istream& source, Register& register_);
  }
}

#endif
