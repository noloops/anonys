// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#include "FsmPool.h"
#include "anonys/Utils.h"

#include "fsm/Jukebox.h"
#include "fsm/LedJuggler.h"

namespace anonys
{
    static_assert(BufferSize::Jukebox % anonys::StdAlign == 0, "Buffer size must be a multiple of alignment");
    static_assert(BufferSize::LedJuggler % anonys::StdAlign == 0, "Buffer size must be a multiple of alignment");

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

    void FsmPool::initializeLedJuggler(TimerService& timerService, terminals::Led& led) {
        ANONYS_ASSERT(m_terminalsLedJuggler.pTimer == nullptr);
        FsmCore& fsm{ m_fsm[static_cast<uint16_t>(FsmId::LedJuggler)] };
        m_terminalsLedJuggler.pTimer = &(fsm.getTimerCore());
        m_terminalsLedJuggler.pLed = &led;

        uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferLedJuggler)) };
        fsm.initialize(FsmId::LedJuggler, &m_terminalsLedJuggler, pBuffer, sizeof(m_bufferLedJuggler), &timerService);
    }

    void FsmPool::start() {
        ANONYS_ASSERT(!m_started);
        m_started = true;
        m_fsm[static_cast<uint16_t>(FsmId::Jukebox)].executeTransition(&fsm::Jukebox::Off);
        m_fsm[static_cast<uint16_t>(FsmId::LedJuggler)].executeTransition(&fsm::LedJuggler::BlinkA);
    }
}
