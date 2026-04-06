#ifndef EXAMPLE2_ANONYS_MANUALCONFIG_H
#define EXAMPLE2_ANONYS_MANUALCONFIG_H

#include <cstdint>

#define ANONYS_ASSERT(ok) do { if (!(ok)) { throw false; }} while (false)

namespace anonys
{
	constexpr size_t StdAlign{ 8 };

	struct BufferSize {
		static constexpr size_t Elevator{ 256 };
		static constexpr size_t TrafficLight{ 384 };
		static constexpr size_t Washer{ 512 };
	};
}

#endif // EXAMPLE2_ANONYS_MANUALCONFIG_H
