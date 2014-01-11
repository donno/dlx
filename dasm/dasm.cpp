//===----------------------------------------------------------------------===//
//
//                            DLX Assembler
//
// NAME         : dasm
// PURPOSE      : Provides main entry point for assembling DLX assembly.
// COPYRIGHT    : (c) 2013 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// DESCRIPTION  : Presently this is only used to test the parsing.
//
//===----------------------------------------------------------------------===//

#include "Assembler.hpp"

#include "parser/Lexer.hpp"
#include "parser/Parser.hpp"
#include "parser/Instructions.hpp"
#include "parser/SymbolTable.hpp"
#include "parser/Types.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
  // Provides a convenient way of processing command line arguments.
  class ArgumentParser
  {
    std::string myProgramName;
    std::vector<std::string> myPositionalArugments;

    struct Option
    {
      unsigned char flag;
      std::string name;
      std::string help;
      bool provided; // Set if the option appears on the command line.
    };
    std::vector<Option> myOptions;

    typedef std::vector<std::string>::const_iterator const_iterator;
    typedef std::vector<std::string>::size_type size_type;
  public:

    // Output the help to the out stream.
    //void help(std::ostream& out);

    // Parse the command line arguments and returns false if there was an error.
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
    // Consider adding an operator[] for getting the positional arguments as well.

    // Returns true if the option given by identifier was provided by the user.
    //
    // identifier should be a return value for addOption.
    bool provided(size_t identifier) const;
  };
}

size_t ArgumentParser::addOption(
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

bool ArgumentParser::parse(int argc, char* argv[])
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
        std::cout <<  "Long option" << std::endl;
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

bool ArgumentParser::provided(size_t identifier) const
{
  return myOptions[identifier].provided;
}

void assemble(const std::string& filename)
{
  std::cout << "Assembling " << filename << std::endl;
  std::ifstream file(filename);
  if (!file)
  {
    // This needs to flag to the main() that there was an error.
    std::cerr << "Failed to read: " << filename << std::endl;
    return;
  }

  dlx::assembly::Assembler assembler(filename, file);
  assembler.assemble();
  assembler.printSymbolTable();
}

// TODO: Test cases
//
//  "add r1,r2, r3 ; Hello world"
//  "add r1,g2, f3 ; Hello world"
//  "add a1,g2, sag ; Hello world"
//
//   stream >> instruction >> rk >> ri >> rj;
int main(int argc, char* argv[])
{
  ArgumentParser arguments;
  // Register arguments.
  //
  //  -o <filename> The name of the object file or directory for saving objects
  //                if multiple source files are provided.
  const size_t optionListing =
    arguments.addOption(
      'l', "listing",
      "Generates a listing of your program and displays it to the terminal.\n"
      "The listing shows how the assembler translated the program and\n"
      "includes the symbol table.");
  // The following two options are mutally exlusive:
  const size_t optionAbsolute =
    arguments.addOption('a', "absolute", "Generate absoloute machine code.");
  const size_t optionRelocatable =
    arguments.addOption('r', "relocatable",
                        "Generate relocatable machine code.");

  // TODO: Implement the argument registration and usage.
  const bool suceeded = arguments.parse(argc, argv);

  if (!suceeded) return 1;

  if (arguments.provided(optionAbsolute) &&
      arguments.provided(optionRelocatable))
  {
    std::cerr << "error: Cannot have -a and -r in same command" << std::endl;
    return 2;
  }

  if (arguments.size() > 0)
  {
    // Assemble the source files provided on the command line.
    std::for_each(arguments.begin(), arguments.end(), assemble);
    return 0;
  }

  using namespace dlx::assembly;

  // Example of an alternative parser, aimed at being typed and easier to read.
  {
    const std::string line("add r1,r2, r3 ; Hello world");

    Instruction instruction;
    // Determine the format based on the instruction, for now assume register to
    // register.
    Register ri, rj, rk;
    Comment comment;
    // It would be nice to sink the rest into a comment.

    std::istringstream stream(line);
    stream >> instruction >> rk >> ri >> rj >> comment;

    std::cout << rk.number << std::endl;
    std::cout << comment.remark << std::endl;
  }

  // Another example, this time starting with a label.
  {
    const std::string line("start: add r1, r2, r3 ; Hello world");

    Label label;
    Instruction instruction;
    // Determine the format based on the instruction, for now assume register to
    // register.
    Register ri, rj, rk;
    Comment comment;

    std::istringstream stream(line);
    stream >> label >> instruction >> rk >> ri >> rj >> comment;

    std::cout << label.name << std::endl;
    std::cout << rk.number << std::endl;
    std::cout << comment.remark << std::endl;
  }

  // Third example, this time determining how to parse it.
  {
    std::cout << std::endl
              << "Third example, this time determining how to parse it."
              << std::endl;

    Label label;
    Instruction instruction;
    Register ri, rj, rk;
    Comment comment;

    const std::string line("start: add r1, r2, r3 ; Hello world");
    std::istringstream stream(line);

    if (startsWithLabel(stream))
    {
      stream >> label >> instruction >> rk >> ri >> rj >> comment;
      std::cout << "Label: " << label.name << std::endl;
    }
    else
    {
      stream >> instruction >> rk >> ri >> rj >> comment;
      std::cout << "Instruction: " << instruction.mnemonic << std::endl;
    }
  }

  // Test the instructions
  {
    using namespace dlx::assembly::instructions;
    Instruction instruction; Register ri, rj, rk; Comment comment;

    const std::string line("add r1,r2, r3 ; Hello world");
    std::istringstream stream(line);
    stream >> instruction;

    // Determine what to extract next based on the format of the instruction.
    switch (instruction.format)
    {
      case Instruction::LongImmediate:
        // NYI: Support for extracting a Lsgn/Lsgn is not yet supported.
        std::cerr << "Unsupported: extracting an instruction with an immediate"
                  << std::endl;
        break;
      case Instruction::Immediate:
        // NYI: Support for extracting a Ksgn/Ksgn is not yet supported.
        std::cerr << "Unsupported: extracting an instruction with an immediate"
                  << std::endl;
        break;
      case Instruction::RegisterToRegister:
        // This is followed by register, register and another register.
        stream >> rk >> ri >> rj >> comment;

        std::cout
        << "r" << rk.number << " = r" << ri.number
        << " " << instruction.mnemonic << " r" << rj.number
        << " // " << comment.remark
        << std::endl;
        break;
      default:
        std::cerr << "Unknown" << std::endl;
    };
  }
};
