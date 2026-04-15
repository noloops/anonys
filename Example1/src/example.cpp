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
#include "Terminals/EventSender.h"

namespace {

	// ---------------------------------------------------------------------------
	// Timer service backed by 1 ms handleTick() calls.
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
				m_entries[i].depth == depth &&
				m_entries[i].eventId == eventId.id };
				if (!m_entries[i].active || same) {
					m_entries[i].fsmId = fsmId;
					m_entries[i].depth = depth;
					m_entries[i].eventId = eventId.id;
					m_entries[i].remainingTicks = (timeoutMs == 0u) ? 1u : timeoutMs;
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
	terminals::EventSender s_eventSender;
	TickTimerService s_timerService;
	anonys::FsmPool s_fsm;

}  // namespace

void handleStartup() {
	s_fsm.initializeLedJuggler(s_timerService, s_led);
	s_fsm.initializeDebouncer(s_timerService, s_eventSender);
	s_fsm.start();
}

void handleTick(uint32_t sysMs) {
	static uint32_t s_lastTickMs{ 0 };
	while (s_lastTickMs != sysMs) {
		++s_lastTickMs;
		s_timerService.tick(s_fsm);
	}
	int32_t const q{ s_eventSender.consume() };
	if (q == 1) {
		events::Click click{};
		anonys::Event event{ anonys::getEventId<events::Click>(), &click };
		s_fsm.handleEvent(anonys::FsmId::LedJuggler, event);
	}
}

void handleButton(bool pressed) {
	events::ButtonEvent btn{ pressed };
	anonys::Event event{ anonys::getEventId<events::ButtonEvent>(), &btn };
	s_fsm.handleEvent(anonys::FsmId::Debouncer, event);
}
