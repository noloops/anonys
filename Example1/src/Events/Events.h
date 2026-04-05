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