//===----------------------------------------------------------------------===//
//
//                            DLX Assembler
//
// NAME         : ArgumentParser
// NAMESPACE    : dlx::util
// PURPOSE      : Provides a facility for registring and parsing arguments.
// COPYRIGHT    : (c) 2014 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
//
//===----------------------------------------------------------------------===//

#include "ArgumentParser.hpp"

#include <algorithm>
#include <iostream>

size_t dlx::util::ArgumentParser::addOption(
  unsigned char flag,
  const char* name,
  const char* help)
{
  // TODO: Provide checks to ensure this doesn't conflict with an existing
  // option. That is to say, that flag and name aren't already taken.
  const Option option = {flag, name, help, false};
  if (myOptions.empty())
  {
    myLongestOptionLength = option.name.size();
  }
  else
  {
    myLongestOptionLength = std::max(option.name.size(), myLongestOptionLength);
  }
  myOptions.push_back(option);
  return myOptions.size() - 1;
}

void dlx::util::ArgumentParser::help(std::ostream& out) const
{
  out << "Usage: " << myProgramName << " [OPTION] [FILE]..." << std::endl;
  // TODO: Add a summary/description here.
  out << std::endl;

  // The column (number of charachters) from the left where the description
  // part of the help starts (option->help).
  const size_t helpColumn = myLongestOptionLength + 9;
  const std::string newLinePadding('\n' + std::string(helpColumn, ' '));

  for (auto option = myOptions.cbegin(), optionEnd = myOptions.cend();
       option != optionEnd; ++option)
  {
    const std::string padding(myLongestOptionLength - option->name.size(), ' ');
    std::string help = option->help;

    // Replace new lines with a new line and the padding to the help column.
    for (size_t pos = 0; (pos = help.find('\n', pos)) != std::string::npos;
         pos += padding.length() + 1)
    {
      help.replace(pos, 1, newLinePadding);
    }

    if (option->flag != '\0')
    {
      out << "  -" << option->flag << ", --" << option->name << ' '
          << padding << help << std::endl;
    }
    else
    {
      out << "      --" << option->name << padding << ' ' << help << std::endl;
    }
  }
}

bool dlx::util::ArgumentParser::parse(int argc, char* argv[])
{
  myProgramName = std::string(argv[0]);

  // Look for options.
  bool error = false;
  for (auto arg = argv + 1; arg != argv + argc; ++arg)
  {
    const std::string argument(*arg);
    if (argument.empty()) continue;

    const size_t length = argument.size();

    // Ignore it as its a positional argument (-) so read from standard-in.
    if (length == 1) continue;

    if (argument[0] == '-')
    {
      if (argument[1] == '-')
      {
        // Long option
        auto option = std::find_if(myOptions.begin(), myOptions.end(),
                     [&](const Option& option) -> bool {
                        return option.name == argument.substr(2);
                     });
        if (option == myOptions.cend())
        {
          std::cerr << "unknown option: " << argument << std::endl;
          error = true;
        }
        else
        {
          option->provided = true;
        }
      }
      else
      {
        // This is a short option, so each character represents an unique
        // option.
        //
        // For each char lookup option. This uses the original char array.
        for (char* cp = *arg + 1; *cp != '\0'; ++cp)
        {
          const char c = *cp;
          auto option = std::find_if(myOptions.begin(), myOptions.end(),
                      [c](const Option& option) -> bool {
                        return option.flag == c;
                     });
          if (option == myOptions.cend())
          {
            std::cerr << "unknown option: " << argument << std::endl;
            error = true;
          }
          else
          {
            option->provided = true;
          }
        }
      }
      continue;
    }
    myPositionalArguments.push_back(argument);
  }

  return !error;
}

bool dlx::util::ArgumentParser::provided(size_t identifier) const
{
  return myOptions[identifier].provided;
}

//===--------------------------- End of the file --------------------------===//