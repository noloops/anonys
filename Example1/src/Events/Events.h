// ANONYS
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

#include <cstdint>

namespace events {
	struct PowerOn {};
	struct PowerOff {};
	struct InsertCoin {};
	struct Play {};
	struct Pause {};
	struct Skip {};
	struct Eject {};
	struct Diagnostic {};
	struct Malfunction {};
	struct Reset {};
	struct AutoPause {};

	class ConfigureAutoPause {
		int32_t m_countdown;
	public:
		explicit ConfigureAutoPause(int32_t countdown) : m_countdown{(countdown < 1) ? 1 : countdown} {}
		int32_t getCountdown() const { return m_countdown; }
	};
}
