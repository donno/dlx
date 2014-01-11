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
  myOptions.push_back(option);
  return myOptions.size() - 1;
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
        // This is a short option, so each charachter represents an unique
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
    myPositionalArugments.push_back(argument);
  }

  return !error;
}

bool dlx::util::ArgumentParser::provided(size_t identifier) const
{
  return myOptions[identifier].provided;
}

//===--------------------------- End of the file --------------------------===//