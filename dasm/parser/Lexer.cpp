//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Lexer
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides operators and functions for parsing DLX assembly.
// COPYRIGHT    : (c) 2014 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// NOTES        : Notes about the specification.
//
// The start of a line can be a space/tab, a comment character or a letter.
// These are treated as instruction, comment, label respectively.
//
// Label = [a-zA-Z][a-zA-Z0-9]+[:]
// Comment starts with a ; till the end of the line,
// Instruction is can be considered to be the left over cases.
//
// The most complex line is:
// <label> <instruction> <comment>
//
//===----------------------------------------------------------------------===//

#include "Lexer.hpp"

#include <algorithm>
#include <sstream>
#include <iostream>

dlx::assembly::Token dlx::assembly::Lexer::Next()
{
  std::string line;

  if (!myLeftOvers.empty())
  {
    // There were left-overs from the last line that was read.
    line.swap(myLeftOvers);
    myLeftOvers.clear();
  }

  // Ignore blank lines. For a pretty printer it might be good if there was
  // a way to preserve blank lines.
  while (line.empty() && !myStream.eof())
  {
    ++myLine;
    std::getline(myStream, line);
  }

  Token token;
  if (line[0] == ';')
  {
    token.value = std::move(line);
    token.type = Token::Comment;
  }
  else if (line[0] == ' ' || line[0] == '\t')
  {
    token.type = Token::Instruction;

    // Find the first non-whitespace character on the rest of the line.
    //
    // If the first non-whitespace character is a character then there is no
    // instruction. This is likely because the user is trying to line up the
    // comment with the one of the previous line and instruction.
    const auto newStart = line.find_first_not_of(" \t");

    // Find the first comment character on the line as this indicates the
    // end of the instruction.
    const auto currentEnd =
      std::find(line.cbegin() + newStart, line.cend(), ';');

    if (newStart == std::string::npos)
    {
      // The line was nothing but white-space, so return the next token instead.
      token = Next();
    }
    else if (newStart == currentEnd - line.cbegin())
    {
      // There was no instruction on the line but there was a comment so
      // return that instead.
      token.type = Token::Comment;
      token.value.assign(currentEnd, line.cend());
    }
    else if (currentEnd == line.cend())
    {
      token.value = std::move(line);
      myColumn = newStart + 1;
    }
    else
    {
      token.value.assign(line.cbegin(), currentEnd);
      myColumn = newStart + 1;
    }
  }
  else if (std::isalpha(line[0], myLocale))
  {
    token.type = Token::Label;

    // Find first item that is not a space. This denotes the end of the
    // label.
    const auto currentEnd = std::find_if(
      line.cbegin(), line.cend(),
      [&](char c) { return std::isspace(c, myLocale) != 0; });

    if (currentEnd != line.cend())
    {
      // Up until the space is the current token.
      token.value.assign(line.cbegin(), currentEnd);

      // From the space onwards is the next token.
      myLeftOvers.assign(currentEnd, line.cend());
    }
    else
    {
      token.value = std::move(line);
    }
  }
  return token;
}

//===--------------------------- End of the file --------------------------===//