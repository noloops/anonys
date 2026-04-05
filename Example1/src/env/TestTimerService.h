#pragma once

#include <list>
#include "anonys/Timer.h"

namespace env {
	class TestTimerService : public anonys::TimerService {
	public:
		struct TimeoutDef {
			anonys::FsmId fsmId;
			int16_t depth;
			anonys::EventId eventId;
			uint32_t timeoutMs;
		};

		struct Result {
			uint32_t systemTimeMs;
			bool valid;
			TimeoutDef timeout;
		};

		Result getNextTimeout();

		void startTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) final;
		void stopTimers(anonys::FsmId fsmId, int16_t depth) final;

	private:
		std::list<Result> m_timeouts;
		uint32_t m_systemTimeMs{ 0 };
	};
}
