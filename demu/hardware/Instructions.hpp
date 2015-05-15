#ifndef DLX_INSTRUCTIONS_HPP_
#define DLX_INSTRUCTIONS_HPP_
//===----------------------------------------------------------------------===//
//
//                       DLX Instruction Set Emulator
//
// NAME         : Instructions
// NAMESPACE    : dlx::hardware
// PURPOSE      : Provides access to functions for performing the instructions.
// COPYRIGHT    : (c) 2015 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : TODO Document this further.
//
//===----------------------------------------------------------------------===//

namespace dlx
{
  namespace hardware
  {
    class DLXMachine;

    typedef void (*ExecuteInstruction)(DLXMachine*);

    // Provides an array of function pointers index by the opcode, which will
    // perform the specifed instruction in the emulator.
    ExecuteInstruction Instructions[]; // 64

    // Provides an array of function pointers index by the modifier, which will
    // perform the specifed format-R instruction in the emulator.
    //
    // This may not be required as the above table can handle opcode == 0 and
    // have it look-up the modifier and index into another array.
    //
    // It depends on if the indirection needs to be avoided by the caller.
    ExecuteInstruction InstructionsFormatR[];
  }
}

#endif
