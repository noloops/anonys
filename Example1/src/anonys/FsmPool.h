// Generated file, do not edit!
#ifndef EXAMPLE1_FSM_H
#define EXAMPLE1_FSM_H

#include <type_traits>

#include "anonys/FsmCore.h"

#include "impl/terminalsJukebox.h"

namespace anonys
{
	class FsmPool {
	public:
		static constexpr uint16_t Count{ static_cast<uint16_t>(FsmId::Count_)};
		using TerminalsJukebox = anonys_0::Terminals;

		void handleEvent(FsmId fsmId, Event& event);

		void handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId);

		void setTracingService(TracingService* pTracingService = nullptr);

		void setTracingService(FsmId fsmId, TracingService* pTracingService = nullptr);

		void initializeJukebox(TimerService& timerService, terminals::Std& std);

		void start();

	private:
		FsmCore m_fsm[Count]{};

		std::aligned_storage_t<BufferSize::Jukebox, anonys::StdAlign> m_bufferJukebox{};

		TerminalsJukebox m_terminalsJukebox{};

		bool m_started{ false };
	};
}
#endif // EXAMPLE1_FSM_H
