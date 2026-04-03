#ifndef ANONYS_UTILS_H
#define ANONYS_UTILS_H

#include <limits>
#include <new>

#include "AnonysManualConfig.h"

#define ANONYS_ASSERT(ok) do { if (!(ok)) { throw false; }} while (false)

namespace anonys
{
	template <class T>
	constexpr uint16_t getAlignedSize() {
		static_assert(StdAlign >= alignof(T));
		static_assert(StdAlign % alignof(T) == 0);
		constexpr size_t mask{ ~(StdAlign - 1) };
		constexpr size_t size{ (sizeof(T) + StdAlign - 1) & mask };
		static_assert(size <= std::numeric_limits<uint16_t>::max());
		return size;
	}
}

#endif // ANONYS_UTILS_H
