// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#ifndef EXAMPLE1_TERMINALS_LED_H
#define EXAMPLE1_TERMINALS_LED_H

#include "example.h"
#include <cstdint>

namespace terminals {

	class Led {
	public:
		void startBlinkA() {
			m_mode = Mode::BlinkA;
			m_tick = 0;
		}

		void startBlinkB() {
			m_mode = Mode::BlinkB;
			m_tick = 0;
		}

		void solidOn() {
			m_mode = Mode::On;
			setLed(true);
		}

		void solidOff() {
			m_mode = Mode::Off;
			setLed(false);
		}

		void stop() {
			m_mode = Mode::Off;
			setLed(false);
		}

		// Call every 50 ms from handleTick() to advance blink patterns.
		void tick() {
			++m_tick;
			switch (m_mode) {
			case Mode::BlinkA: {
				// Fingerprint A: on-off-on-on-on-off-off (period 7 ticks = 350 ms)
				uint8_t const phase{ static_cast<uint8_t>(m_tick % 7u) };
				setLed(phase == 0u || phase == 2u || phase == 3u || phase == 4u);
				break;
			}
			case Mode::BlinkB: {
				// Fast toggle: on/off every tick (10 Hz at 50 ms tick rate)
				setLed((m_tick % 2u) == 0u);
				break;
			}
			default:
				break;
			}
		}

	private:
		enum class Mode : uint8_t { Off, On, BlinkA, BlinkB } m_mode{ Mode::Off };
		uint8_t m_tick{ 0 };
	};

}

#endif // EXAMPLE1_TERMINALS_LED_H
