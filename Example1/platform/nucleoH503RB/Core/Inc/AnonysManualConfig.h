// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#ifndef EXAMPLE1_ANONYS_MANUALCONFIG_H
#define EXAMPLE1_ANONYS_MANUALCONFIG_H

#include <cstdint>

// Declare Error_Handler without pulling in the full HAL header chain.
#ifdef __cplusplus
extern "C" {
#endif
void Error_Handler(void);
#ifdef __cplusplus
}
#endif

#define ANONYS_ASSERT(ok) do { if (!(ok)) { Error_Handler(); } } while (false)

namespace anonys {

	// Minimum alignment used by getAlignedSize<T>().
	// Must be >= alignof(any Me struct member) used in this project.
	constexpr std::size_t StdAlign{ 8 };

	struct BufferSize {
		static constexpr std::size_t LedJuggler{ 128 };
	};

}

#endif // EXAMPLE1_ANONYS_MANUALCONFIG_H
