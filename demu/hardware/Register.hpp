#ifndef DLX_REGISTER_HPP_
#define DLX_REGISTER_HPP_
//===----------------------------------------------------------------------===//
//
//                       DLX Instruction Set Emulator
//
// NAME         : Register
// NAMESPACE    : dlx::hardware
// PURPOSE      : Provides an abstraction of the 32-bit integer register.
// COPYRIGHT    : (c) 2015 Sean Donnellan.
// LICENSE      : The MIT License (see LICENSE.txt)
// AUTHORS      : Sean Donnellan (darkdonno@gmail.com)
// DESCRIPTION  : Provides storage for a 32-bit integer value as well as some
//                operators on values in the registers. These operators emulate
//                the function of the arithmetic logic unit (ALU).
//
//===----------------------------------------------------------------------===//

#include <cstdint>

namespace dlx
{
	namespace hardware
	{
		struct Register
		{
		  inline Register() : value(0) {}
		  inline Register(std::int32_t inital) : value(inital) {}

		  Register& operator=(std::int32_t new_value)
		  { value = new_value; return *this; }

		  Register& operator=(const Register& that)
		  { value = that.value; return *this; }

		  std::int32_t value;
		};

		inline std::int32_t operator+(const Register& reg, std::int32_t value)
		{
			return reg.value + value;
		}

		inline std::int32_t operator+(const Register& lhs, const Register& rhs)
		{
			return lhs.value + rhs.value;
		}

		inline std::int32_t operator-(const Register& reg, std::int32_t value)
		{
			return reg.value - value;
		}

		inline std::int32_t operator-(const Register& lhs, const Register& rhs)
		{
			return lhs.value - rhs.value;
		}

		inline std::int32_t operator&(const Register& lhs, std::int32_t value)
		{
			return lhs.value & value;
		}

		inline std::int32_t operator&(const Register& lhs, const Register& rhs)
		{
			return lhs.value & rhs.value;
		}

		inline std::int32_t operator|(const Register& lhs, std::int32_t value)
		{
			return lhs.value | value;
		}

		inline std::int32_t operator|(const Register& lhs, const Register& rhs)
		{
			return lhs.value | rhs.value;
		}

		inline bool operator==(const Register& reg, std::int32_t value)
		{
			return reg.value == value;
		}

		inline bool operator==(const Register& lhs, const Register& rhs)
		{
			return lhs.value == rhs.value;
		}

		inline bool operator!=(const Register& reg, std::int32_t value)
		{
			return reg.value != value;
		}

		inline bool operator!=(const Register& lhs, const Register& rhs)
		{
			return lhs.value != rhs.value;
		}
	}
}
#endif
