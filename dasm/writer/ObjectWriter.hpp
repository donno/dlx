#ifndef DLX_WRITER_OBJECT_WRITER_HPP_
#define DLX_WRITER_OBJECT_WRITER_HPP_
//===----------------------------------------------------------------------===//
//
//                            DLX Assembly Parser
//
// NAME         : ObjectWriter
// NAMESPACE    : dlx::assembly
// PURPOSE      : Provides operators and functions for writing DLX machine code.
// COPYRIGHT    : (c) 2014 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : Provides a class for writing out machine code to an objec
//                file.
//
//===----------------------------------------------------------------------===//

#include <type_traits>
#include <iomanip>
#include <ostream>

namespace dlx
{
  namespace assembly
  {
    class ObjectWriter
    {
      std::ostream& myWriter;
      size_t myBytesWrittenToLine;
      size_t myAddressOfLine;
      size_t myStartAddress;
      bool isStartAddressKnown;

    public:
      ObjectWriter(std::ostream& writer);
      ~ObjectWriter();

      template<typename INTEGER_TYPE>
      ObjectWriter& operator <<(INTEGER_TYPE value)
      {
        return Out(value, std::is_integral<INTEGER_TYPE>());
      }

      void SetStartAddress(size_t startAddress);

    private:
      // This should be called before a byte is written to take care of adding
      // an end of line or a space.
      void PreByteWritten();

      template<typename INTEGER_TYPE>
      ObjectWriter& Out(INTEGER_TYPE value, std::true_type)
      {
        // Break down the integer into groups of two hex digits.
        for (size_t i = 8 * (sizeof(value) - 1); i > 0; i -= 8)
        {
          PreByteWritten();
          myWriter << std::setfill('0') << std::setw(2) << ((value >> i) & 0xFF);
        }

        PreByteWritten();
        myWriter << std::setfill('0') << std::setw(2) << (value & 0xFF);
        return *this;
      }
    };
  }
}

#endif
