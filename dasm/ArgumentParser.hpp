#ifndef DLX_ARGUMENT_PARSER_HPP_
#define DLX_ARGUMENT_PARSER_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : ArgumentParser
// NAMESPACE    : dlx::util
// PURPOSE      : Provides a facility for registring and parsing arguments.
// COPYRIGHT    : (c) 2014 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
//
//===----------------------------------------------------------------------===//

#include <string>
#include <vector>

namespace dlx
{
  namespace util
  {
    class ArgumentParser
    {
      std::string myProgramName;
      std::vector<std::string> myPositionalArugments;
      size_t myLongestOptionLength;

      struct Option
      {
        unsigned char flag;
        std::string name;
        std::string help;
        bool provided; // Set if the option appears on the command line.
      };
      std::vector<Option> myOptions;

    public:
      typedef std::vector<std::string>::const_iterator const_iterator;
      typedef std::vector<std::string>::size_type size_type;

      // Output the help to the out stream.
      void help(std::ostream& out) const;

      // Parse the command line arguments and returns if it suceeded without
      // errors.
      bool parse(int argc, char* argv[]);

      // Add an option to the parser.
      //
      // flag can be '\0' for meaning there is no single charachter (flag) for
      // triggering this option.
      //
      // returns an identifier for determining if its been set.
      size_t addOption(unsigned char flag, const char* name, const char* help);

      // Get the positional arguments.
      const_iterator begin() const { return myPositionalArugments.begin(); }
      const_iterator end() const { return myPositionalArugments.end(); }
      size_type size() const { return myPositionalArugments.size(); }

      // TODO: Consider adding an operator[] for getting the positional
      // arguments as well.

      // Returns true if the option given by identifier was provided by the user.
      //
      // identifier should be a return value for addOption.
      bool provided(size_t identifier) const;
    };
  }
}

#endif

