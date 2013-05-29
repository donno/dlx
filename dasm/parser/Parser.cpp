//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : Parser
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides operators and functions for parsing DLX assembly.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// NOTES        : Notes about the specification.
//
// Types:
//   Ksgn = 16-bit Signed constant
//   Kusn = 16-bit Unsigned constant
//   Lsgn = 26-bit Signed constnat
//   Lusn = 26-bit unsigned constnat
//
// Anywhere those 4 are used below can be a label (i.e a named address/value)
//
// Instruction formats:
// * Long-immediate: <instruction> Lsgn/Lusn
// * Immediate <instruction> <register>, <register>, <Ksgn/Kusgn>
// * Register to Register: <instruction> <register>, <register>, <register>
//   An alternative to this is the shorcuts:
//   <instruction> <register>, <register>  ; For example mv instruction.
//
//===----------------------------------------------------------------------===//

#include "Parser.hpp"

#include "Instructions.hpp"
#include "Types.hpp"

#include <cctype>
#include <ios>
#include <sstream>

// Functions for helping with the implementation of the >> operators.
namespace
{
  void read(std::istream& source, std::string& destination,
            bool ignoreSpaces=true)
  {
    std::ios_base::iostate state = std::ios_base::goodbit;
    bool changed = false;
    const std::istream::sentry ok(source, true);
    if (!ok)
    {
      state |= std::ios_base::failbit;
      source.setstate(state);
      return;
    }

    typedef std::istream::traits_type traits_type;
    const traits_type::int_type delimiter = traits_type::to_int_type(',');
    const traits_type::int_type comment   = traits_type::to_int_type(';');
    const traits_type::int_type space     = traits_type::to_int_type(' ');
    const traits_type::int_type tab       = traits_type::to_int_type('\t');

    for (traits_type::int_type meta = source.rdbuf()->sgetc();;
         meta = source.rdbuf()->snextc())
    {
      if (traits_type::eq_int_type(traits_type::eof(), meta))
      {
        state |= std::ios_base::eofbit;
        break;   // End of file, quit.
      }
      else if (traits_type::eq_int_type(meta, delimiter) ||
               traits_type::eq_int_type(meta, comment))
      {
        // :TODO:
        // A comment we might want to leave it in the stream and just break,
        // so the next time someone source they get the comment charachter.

        // Got a delimiter, discard it and quit
        changed = true;
        source.rdbuf()->sbumpc();
        break;
      }
      else if (destination.max_size() <= destination.size())
      {
        // string too large, quit
        state |= std::ios_base::failbit;
        break;
      }
      else if (traits_type::eq_int_type(meta, space) ||
               traits_type::eq_int_type(meta, tab))
      {
        // Ignore spaces or tabs.
        changed = true;
      }
      else
      {
        // got a character, add it to string
        destination += traits_type::to_char_type(meta);
        changed = true;
      }
    }
    if (!changed)
      state |= std::ios_base::failbit;
    source.setstate(state);
  }
}

static dlx::assembly::Instruction::Format formatFromMnemonic(
  const std::string& mnemonic)
{
  // TODO: Do this a better way, propbably by having a constructor which builds
  // a map of mnemonic to formats or least the instances of the class.
  using namespace dlx::assembly::instructions;
  if (mnemonic == add.mnemonic)
  {
    return add.format;
  }
  else
  {
    return dlx::assembly::Instruction::Immediate;
  }
  
}

bool dlx::assembly::startsWithLabel(std::istream& source)
{
  // If the next character is is an alpha character, it is likely a label.
  return std::isalpha(source.peek());
}

std::istream& dlx::assembly::operator >>(
  std::istream& source, dlx::assembly::Label& label)
{
  source >> label.name;
  return source;
}

std::istream& dlx::assembly::operator >>(
  std::istream& source, dlx::assembly::Instruction& instruction)
{
  source >> instruction.mnemonic;
  instruction.format = formatFromMnemonic(instruction.mnemonic);  
  return source;
}

std::istream& dlx::assembly::operator >>(
  std::istream& source, dlx::assembly::Comment& comment)
{
  std::getline(source, comment.remark, Comment::Charachter);
  // Remove inital whitespace after the comma.
  const auto newStart = comment.remark.find_first_not_of(" \t");
  if (newStart != std::string::npos)
  {
    comment.remark = comment.remark.substr(newStart);
  }
  return source;
}

std::istream& dlx::assembly::operator >>(
  std::istream& source, dlx::assembly::Register& register_)
{
  std::string word;
  read(source, word);

  std::istringstream ss(word);
  ss >> register_.type;
  ss >> register_.number;

  return source;
}

//===--------------------------- End of the file --------------------------===//