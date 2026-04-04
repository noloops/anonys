// Generated file, do not edit!
#include "FsmPool.h"
#include "anonys/Utils.h"

#include "Fsm/A.h"

namespace anonys
{
	void FsmPool::handleEvent(FsmId fsmId, Event& event) {
		if (fsmId < FsmId::Count_) {
			m_fsm[static_cast<uint16_t>(fsmId)].handleEvent(event);
		}
	}

	void FsmPool::start() {
		ANONYS_ASSERT(!m_started);
		m_started = true;
		m_fsm[static_cast<uint16_t>(FsmId::A)].executeTransition(&fsm::A::St1);
	}
	void FsmPool::initializeA(TimerService& timerService, terminals::Std& std) {
		ANONYS_ASSERT(m_terminalsA.pTimer == nullptr);
		FsmCore& fsm{ m_fsm[static_cast<uint16_t>(FsmId::A)] };
		m_terminalsA.pTimer = &(fsm.getTimerCore());
		m_terminalsA.pStd = &std;

		uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferA)) };
		fsm.initialize(FsmId::A, &m_terminalsA, pBuffer, sizeof(m_bufferA), &timerService);
	}
}
