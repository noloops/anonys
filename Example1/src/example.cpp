// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "example.h"
#include "anonys/FsmPool.h"
#include "anonys/EventId.h"
#include "Events/Events.h"
#include "Terminals/Led.h"

namespace {

	// ---------------------------------------------------------------------------
	// Timer service backed by 50 ms handleTick() calls.
	// ---------------------------------------------------------------------------
	class TickTimerService : public anonys::TimerService {
	public:
		// Called once per handleTick() to advance and fire expired timers.
		void tick(anonys::FsmPool& fsm) {
			for (uint8_t i{ 0 }; i < MaxTimers; ++i) {
				if (!m_entries[i].active) { continue; }
				if (m_entries[i].remainingTicks > 0u) {
					--m_entries[i].remainingTicks;
				}
				if (m_entries[i].remainingTicks == 0u) {
					m_entries[i].active = false;
					fsm.handleTimeoutEvent(
						m_entries[i].fsmId,
						m_entries[i].depth,
						anonys::EventId{ m_entries[i].eventId });
				}
			}
		}

		// anonys::TimerService interface:
		void startTimer(anonys::FsmId fsmId, int16_t depth,
				anonys::EventId eventId, uint32_t timeoutMs) override {
			for (uint8_t i{ 0 }; i < MaxTimers; ++i) {
				bool const same{
					m_entries[i].active &&
					m_entries[i].fsmId == fsmId &&
					m_entries[i].depth == depth };
				if (!m_entries[i].active || same) {
					m_entries[i].fsmId = fsmId;
					m_entries[i].depth = depth;
					m_entries[i].eventId = eventId.id;
					uint32_t const ticks{ (timeoutMs + 49u) / 50u };
					m_entries[i].remainingTicks = (ticks == 0u) ? 1u : ticks;
					m_entries[i].active = true;
					return;
				}
			}
			// No free slot — should never happen with MaxTimers = 8
			ANONYS_ASSERT(false);
		}

		void stopTimers(anonys::FsmId fsmId, int16_t depth) override {
			for (uint8_t i{ 0 }; i < MaxTimers; ++i) {
				if (m_entries[i].active &&
						m_entries[i].fsmId == fsmId &&
						m_entries[i].depth == depth) {
					m_entries[i].active = false;
				}
			}
		}

	private:
		static constexpr uint8_t MaxTimers{ 8 };

		struct Entry {
			anonys::FsmId fsmId{};
			int16_t depth{ 0 };
			uint16_t eventId{ 0 };
			uint32_t remainingTicks{ 0 };
			bool active{ false };
		};

		Entry m_entries[MaxTimers]{};
	};

	terminals::Led s_led;
	TickTimerService s_timerService;
	anonys::FsmPool s_fsm;
	bool s_initialized{ false };

	void init() {
		s_fsm.initializeLedJuggler(s_timerService, s_led);
		s_fsm.start();
		s_initialized = true;
	}

}  // namespace

void handleTick() {
	if (!s_initialized) {
		init();
	}
	s_timerService.tick(s_fsm);
	s_led.tick();
}

void handleClick() {
	if (!s_initialized) {
		return;
	}
	events::Click click{};
	anonys::Event event{ anonys::getEventId<events::Click>(), &click };
	s_fsm.handleEvent(anonys::FsmId::LedJuggler, event);
}
