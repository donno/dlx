dasm
===

A DLX assembler written in C++.

DLX is a RISC processor architecture designed by John L. Hennessy and
David A. Patterson.

Licenses
---------------------
dasm is licenses under the terms of "The MIT License".
See LICENSE.txt for details.

Usage
---------------------

Usage: dasm [OPTION] [FILE]...

  -l, --listing     Generates a listing of the program to the terminal.
                    The listing shows how the assembler translated the program
                    and it includes the symbol table.
  -h, --help        Display this help and exit.
  -a, --absolute    Generate absoloute machine code.
  -r, --relocatable Generate relocatable machine code.

Examples
---------------------

Compiling a DLX source file to absoloute machine code.

$ dasm -a euler1.dls

