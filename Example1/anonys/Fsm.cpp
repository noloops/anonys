// Generated file, do not edit!
#include "Fsm.h"
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
	void FsmPool::initializeA(terminals::Std& std) {
		ANONYS_ASSERT(m_terminalsA.pStd == nullptr);
		m_terminalsA.pStd = &std;

		uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferA)) };
		m_fsm[static_cast<uint16_t>(FsmId::A)].initialize(FsmId::A, &m_terminalsA, pBuffer, sizeof(m_bufferA));
	}
}
