#ifndef DLX_LEXER_HPP_
#define DLX_LEXER_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Lexer
// NAMESPACE    : dlx::assembly
// PURPOSE      : Converts a sequence of characters into a sequence of tokens
// COPYRIGHT    : (c) 2014 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : Converts a sequence of characters into a sequence of tokens.
//
//                A token is there by a grouping of consequentive charachters
//                that form a certain meaning.
//
//                Comments can optionally be ignored by the lexer so it will
//                just skip over them.
//
// Tokens:
//   * Comment - Represents a remark left by the developer to provide additional
//               insight into what instructions are doing and/or why.
//   * Label - Represents a label that names a symbol or name for a certain
//             address of memory that can be referenced later.
//   * Instruction - Represents an instruction that the machine will execute.
//
//===----------------------------------------------------------------------===//

#include <memory>
#include <istream>
#include <locale>
#include <string>

namespace dlx
{
  namespace assembly
  {
    struct Token
    {
      enum Type { Comment, Label, Instruction };

      // This takes a copy of the token instead of indexing into the original
      // data source.
      std::string value;
      Type type;
    };

    class Lexer
    {
      std::istream& myStream;
      std::locale myLocale;

      // If a line contains more than one token this is set to the left over
      // from the line. This is a side-effect of reading a line at a time.
      std::string myLeftOvers;

    public:
      Lexer(std::istream& stream) : myStream(stream), myLeftOvers() {}

      Token Next();
    };
  }
}

#endif
