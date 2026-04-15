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

#include "fsm/SemiFab.h"

namespace anonys
{
    static_assert(BufferSize::SemiFab % anonys::StdAlign == 0, "Buffer size must be a multiple of alignment");

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

    void FsmPool::initializeSemiFab(TimerService& timerService, term::io::Std& std) {
        ANONYS_ASSERT(m_terminalsSemiFab.pTimer == nullptr);
        FsmCore& fsm{ m_fsm[static_cast<uint16_t>(FsmId::SemiFab)] };
        m_terminalsSemiFab.pTimer = &(fsm.getTimerCore());
        m_terminalsSemiFab.pStd = &std;

        uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferSemiFab)) };
        fsm.initialize(FsmId::SemiFab, &m_terminalsSemiFab, pBuffer, sizeof(m_bufferSemiFab), &timerService);
    }

    void FsmPool::start() {
        ANONYS_ASSERT(!m_started);
        m_started = true;
        m_fsm[static_cast<uint16_t>(FsmId::SemiFab)].executeTransition(&fsm::SemiFab::Offline);
    }
}
