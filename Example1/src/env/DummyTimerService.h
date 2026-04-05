#pragma once

#include "anonys/Timer.h"

namespace env {
	class DummyTimerService : public anonys::TimerService {
	public:
		void startTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) final {
		}
		void stopTimers(anonys::FsmId fsmId, int16_t depth) final {
		}
	};
}
