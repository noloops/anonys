#ifndef EXAMPLE1_FSM_H
#define EXAMPLE1_FSM_H

// Generated file, do not edit!

#include <type_traits>

#include "anonys/FsmBase.h"

#include "impl/terminalsA.h"

namespace anonys
{
	class Fsm { // TODO rename
	public:
		static constexpr uint16_t Count{ static_cast<uint16_t>(FsmId::Count_)};
		using TerminalsA = anonys_1::Terminals;

		void handleEvent(FsmId fsmId, Event& event);

		void start();

		void initializeA(terminals::Std& std);
	private:
		FsmBase m_fsm[Count]{};

		std::aligned_storage_t<BufferSize::A, anonys::StdAlign> m_bufferA{};

		TerminalsA m_terminalsA{};

		bool m_started{ false };
	};
}
#endif // EXAMPLE1_FSM_H
