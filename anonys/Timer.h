#ifndef ANONYS_TIMER_H
#define ANONYS_TIMER_H

#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys
{
	class TimerService {
	public:
		virtual ~TimerService() = default;
		virtual void startTimer(FsmId fsmId, int16_t depth, EventId eventId, uint32_t timeoutMs) = 0;
		virtual void stopTimers(FsmId fsmId, int16_t depth) = 0;
	};

	class TimerCore {
	public:
		inline void startTimer(EventId eventId, uint32_t timeoutMs) {
			if (m_pTimerService != nullptr) {
				m_pTimerService->startTimer(m_fsmId, m_curDepth, eventId, timeoutMs);
			}
		}
		inline void stopTimers() {
			if (m_pTimerService != nullptr) {
				m_pTimerService->stopTimers(m_fsmId, m_curDepth);
			}
		}

	protected:
		TimerCore() = default;

		TimerService* m_pTimerService{ nullptr };
		FsmId m_fsmId{};
		int16_t m_curDepth{ -1 };
	};

	class Timer {
	public:
		Timer(TimerCore& timerCore) : m_timerCore{ timerCore } {}

		~Timer() {
			if (m_active) {
				m_timerCore.stopTimers();
			}
		}

		template <typename T>
		inline void start(uint32_t timeoutMs) {
			constexpr EventId eventId{ getTimeoutEventId<T>() };
			m_active = true;
			m_timerCore.startTimer(eventId, timeoutMs);
		}

	private:
		TimerCore& m_timerCore;
		bool m_active{ false };
	};
}

#endif // ANONYS_TIMER_H
