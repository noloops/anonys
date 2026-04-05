#pragma once

#include <cstdint>

namespace terminals {
	class Counter {
		int32_t m_value{0};
	public:
		int32_t increment() { return ++m_value; }
		int32_t getValue() const { return m_value; }
	};

	class Mixer {
		int32_t m_volume{0};
	public:
		int32_t setVolume(int32_t v) { m_volume = v; return m_volume; }
		int32_t adjust(int32_t delta) { m_volume += delta; return m_volume; }
		int32_t getVolume() const { return m_volume; }
	};
}
