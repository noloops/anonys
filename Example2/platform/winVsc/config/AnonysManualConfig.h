// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

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
