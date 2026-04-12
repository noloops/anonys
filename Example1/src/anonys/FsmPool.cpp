// ANONYS - Generated file, do not edit!
#include "FsmPool.h"
#include "anonys/Utils.h"

#include "fsm/Jukebox.h"

namespace anonys
{
    static_assert(BufferSize::Jukebox % anonys::StdAlign == 0, "Buffer size must be a multiple of alignment");

    void FsmPool::handleEvent(FsmId fsmId, Event& event) {
        if (static_cast<uint16_t>(fsmId) < FsmCount) {
            m_fsm[static_cast<uint16_t>(fsmId)].handleEvent(event);
        }
    }

    void FsmPool::handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId) {
        if (static_cast<uint16_t>(fsmId) < FsmCount) {
            m_fsm[static_cast<uint16_t>(fsmId)].handleTimeoutEvent(depth, eventId);
        }
    }

    void FsmPool::setTracingService(TracingService* pTracingService) {
        for (uint16_t fsmId{0}; fsmId < FsmCount; ++fsmId) {
            m_fsm[fsmId].setTracingService(pTracingService);
        }
    }

    void FsmPool::setTracingService(FsmId fsmId, TracingService* pTracingService) {
        if (static_cast<uint16_t>(fsmId) < FsmCount) {
            m_fsm[static_cast<uint16_t>(fsmId)].setTracingService(pTracingService);
        }
    }

    void FsmPool::initializeJukebox(TimerService& timerService, terminals::Std& std) {
        ANONYS_ASSERT(m_terminalsJukebox.pTimer == nullptr);
        FsmCore& fsm{ m_fsm[static_cast<uint16_t>(FsmId::Jukebox)] };
        m_terminalsJukebox.pTimer = &(fsm.getTimerCore());
        m_terminalsJukebox.pStd = &std;

        uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferJukebox)) };
        fsm.initialize(FsmId::Jukebox, &m_terminalsJukebox, pBuffer, sizeof(m_bufferJukebox), &timerService);
    }

    void FsmPool::start() {
        ANONYS_ASSERT(!m_started);
        m_started = true;
        m_fsm[static_cast<uint16_t>(FsmId::Jukebox)].executeTransition(&fsm::Jukebox::Off);
    }
}
