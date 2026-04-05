#pragma once

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

		Result triggerTimeout();

		void startTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) final;
		void stopTimers(anonys::FsmId fsmId, int16_t depth) final;

	private:
		static constexpr int MaxTimers = 32;

		struct Entry {
			bool active;
			anonys::FsmId fsmId;
			int16_t depth;
			uint16_t eventIdValue;
			uint32_t triggerTimeMs;
			int sequence;
		};

		Entry m_timers[MaxTimers]{};
		uint32_t m_systemTimeMs{ 0 };
		int m_nextSequence{ 0 };
	};
}
