#ifndef EXAMPLE1_ANONYS_MANUALCONFIG_H
#define EXAMPLE1_ANONYS_MANUALCONFIG_H

#include <cstdint>

#define ANONYS_ASSERT(ok) do { if (!(ok)) { throw false; }} while (false)

namespace anonys
{
	constexpr size_t StdAlign{ 8 };

	struct BufferSize {
		static constexpr size_t A{ 512 };
	};
}

#endif // EXAMPLE1_ANONYS_MANUALCONFIG_H
