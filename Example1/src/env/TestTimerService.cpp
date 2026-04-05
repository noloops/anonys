#include "TestTimerService.h"

namespace env {
	void TestTimerService::startTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) {
		for (auto& entry : m_timers) {
			if (!entry.active) {
				entry.active = true;
				entry.fsmId = fsmId;
				entry.depth = depth;
				entry.eventIdValue = eventId.id;
				entry.triggerTimeMs = m_systemTimeMs + timeoutMs;
				entry.sequence = m_nextSequence++;
				return;
			}
		}
	}

	void TestTimerService::stopTimers(anonys::FsmId fsmId, int16_t depth) {
		for (auto& entry : m_timers) {
			if (entry.active && entry.fsmId == fsmId && entry.depth == depth) {
				entry.active = false;
			}
		}
	}

	TestTimerService::Result TestTimerService::triggerTimeout() {
		int bestIdx = -1;
		uint32_t bestTime = 0;
		int bestSeq = 0;

		for (int i = 0; i < MaxTimers; ++i) {
			if (!m_timers[i].active) continue;
			if (bestIdx < 0
				|| m_timers[i].triggerTimeMs < bestTime
				|| (m_timers[i].triggerTimeMs == bestTime && m_timers[i].sequence < bestSeq))
			{
				bestIdx = i;
				bestTime = m_timers[i].triggerTimeMs;
				bestSeq = m_timers[i].sequence;
			}
		}

		if (bestIdx < 0) {
			return { m_systemTimeMs, false, { anonys::FsmId::A, 0, anonys::EventId{0}, 0 } };
		}

		Entry& entry = m_timers[bestIdx];
		if (entry.triggerTimeMs > m_systemTimeMs) {
			m_systemTimeMs = entry.triggerTimeMs;
		}

		Result result{
			m_systemTimeMs,
			true,
			{ entry.fsmId, entry.depth, anonys::EventId{entry.eventIdValue}, entry.triggerTimeMs }
		};

		entry.active = false;
		return result;
	}
}
