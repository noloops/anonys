#pragma once

#include <cstdint>
#include "LogService.h"

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

	class Countdown {
		int32_t m_value{0};
		LogService& m_log;
	public:
		Countdown(LogService& log) : m_log{log} {}
		void set(int32_t value) { m_value = value; }
		bool decrement() {
			--m_value;
			if (m_value <= 0) {
				m_log.write(Message::CountdownReachedZero);
				return true;
			}
			return false;
		}
		int32_t getValue() const { return m_value; }
	};
}
