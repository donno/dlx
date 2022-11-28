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

#include "ArgumentParser.hpp"
#include "Assembler.hpp"

#include "parser/Lexer.hpp"
#include "parser/Parser.hpp"
#include "parser/Instructions.hpp"
#include "parser/SymbolTable.hpp"
#include "parser/Types.hpp"

#include "writer/ObjectWriter.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

void assemble(const std::string& filename, bool generateListing)
{
  std::string outputFilename(filename);
  if (outputFilename.find_last_of(".dls") != std::string::npos)
  {
    outputFilename.back() = 'x';
  }
  else
  {
    outputFilename.append(".dlx");
  }

  std::cout << "Assembling " << filename << " to " << outputFilename << std::endl;
  std::ifstream file(filename);
  if (!file)
  {
    // This needs to flag to the main() that there was an error.
    std::cerr << "Failed to read: " << filename << std::endl;
    return;
  }

  std::ofstream output(outputFilename);
  if (!output)
  {
    std::cerr << "Failed to open for write: " << outputFilename << std::endl;
    return;
  }

  dlx::assembly::ObjectWriter writer(output);
  dlx::assembly::Assembler assembler(filename, file, generateListing);
  assembler.assemble(writer);
  assembler.printSymbolTable();
}

bool checkInstructionEncoding(const char* line, const char* expected)
{
  std::istringstream sample(std::string("m:\t") + line + "\n\t.start m\n");
  std::stringstream output;
  dlx::assembly::ObjectWriter writer(output);
  dlx::assembly::Assembler assembler("example", sample, true);
  assembler.assemble(writer);

  std::string outputLine;
  std::getline(output, outputLine);
  if (outputLine != ".abs")
  {
   std::cerr << "Missing .abs" << std::endl;
   return false;
  }

  const std::string addressPrefix("00000000  ");
  std::getline(output, outputLine);
  if (outputLine != addressPrefix + expected)
  {
    if (outputLine.compare(0, addressPrefix.length(), addressPrefix) == 0)
    {
      std::cerr << "Failed to generate the correct machine code for "
                << line << " expected " << expected << " got "
                << outputLine.substr(addressPrefix.length())
                << std::endl;
    }
    else
    {
      std::cerr << "Missing address" << std::endl;
    }
    return false;
  }
  return true;
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
  dlx::util::ArgumentParser arguments;
  // TODO: Add the following option.
  //  -o <filename> The name of the object file or directory for saving objects
  //                if multiple source files are provided.

  // Register arguments.
  const size_t optionListing =
    arguments.addOption(
      'l', "listing",
      "Generates a listing of the program to the terminal.\n"
      "The listing shows how the assembler translated the program\n"
      "and it includes the symbol table.");
  const size_t optionHelp =
    arguments.addOption('h', "help", "Display this help and exit.");
  // The following two options are mutually exclusive:
  const size_t optionAbsolute =
    arguments.addOption('a', "absolute", "Generate absolute machine code.");
  const size_t optionRelocatable =
    arguments.addOption('r', "relocatable",
                        "Generate relocatable machine code.");

  const bool succeeded = arguments.parse(argc, argv);
  if (!succeeded) return 1;

  if (arguments.provided(optionHelp))
  {
    arguments.help(std::cout);
    return 0;
  }

  if (arguments.provided(optionAbsolute) &&
      arguments.provided(optionRelocatable))
  {
    std::cerr << "error: Cannot have -a and -r in same command" << std::endl;
    return 2;
  }

  const bool generateListing = arguments.provided(optionListing);

  if (arguments.size() > 0)
  {
    // Assemble the source files provided on the command line.
    std::for_each(
      arguments.begin(), arguments.end(),
      [=](const std::string& filename)
      { assemble(filename, generateListing); });
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

  // This is a test to make sure: "clr r1" parses to correct machine code.
  {
    const char* const instruction = "clr r1";
    const char* const expected = "20 01 00 00";
    std::cout <<  "Object writer for " << instruction << std::endl;
    if (checkInstructionEncoding(instruction, expected))
    {
      std::cout << "PASSED" << std::endl;
    }
  }

  // This is a test to make sure: "jr r31" parses to the machine code.
  {
    const char* const instruction = "jr r31";
    const char* const expected = "4B E0 00 00";
    std::cout <<  "Object writer for " << instruction << std::endl;
    if (checkInstructionEncoding(instruction, expected))
    {
      std::cout << "PASSED" << std::endl;
    }
  }

  // This is a test to make sure "movi r1,5" parses to the right machine code.
  {
    const char* const instruction = "movi r2,1";
    const char* const expected = "20 02 00 01";
    std::cout <<  "Object writer for " << instruction << std::endl;
    if (checkInstructionEncoding(instruction, expected))
    {
      std::cout << "PASSED" << std::endl;
    }
  }

  // This is a test to make sure "add r1,r2" parses to the right machine code.
  // add r1,r2 should be equivelent to add r1,r1,r2
  {
    const char* const instruction = "add r1,r2";
    const char* const expected = "00 22 08 20";
    std::cout <<  "Object writer for " << instruction << std::endl;
    if (checkInstructionEncoding(instruction, expected))
    {
      std::cout << "PASSED" << std::endl;
    }
  }
  return 0;
}
