demu
======

A DLX emulator written in C++.

DLX is a RISC processor architecture designed by John L. Hennessy and
David A. Patterson.

Licenses
---------------------
demu is licenses under the terms of "The MIT License".
See LICENSE.txt for details.

Notes
---------------------
At this stage the emulator is very much incomplete. To date only a small number
of instructions have been tested.

Features implemented
* Loading a text-based DLX file which represents the inital memory of a DLX
  machine into the virtual memory.
* Decoding instructions

Features untested
* The majority of the instruction set.

Features not yet implemented
* Instructions for loading/storing from memory.
* Virtual hardware devices such as lights, switches and terminal.
* Floating-point instructions/registers ETC.
* Breakpoints
* Interactive console for stepping through, examining registers etc.

Usage
---------------------

Usage: demu <filename.dlx>
