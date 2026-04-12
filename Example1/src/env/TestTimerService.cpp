// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "TestTimerService.h"
#include "Expected.h"

namespace env {
    void TestTimerService::startTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) {
        Expected::checkTimerStartTimer(fsmId, depth, eventId, timeoutMs);
        uint32_t const triggerTime{m_systemTimeMs + timeoutMs};
        Result const entry{triggerTime, true, {fsmId, depth, eventId, timeoutMs}};

        auto it{m_timeouts.end()};
        while (it != m_timeouts.begin()) {
            auto const prev{std::prev(it)};
            if (prev->systemTimeMs <= triggerTime) {
                break;
            }
            it = prev;
        }
        m_timeouts.insert(it, entry);
    }

    void TestTimerService::stopTimers(anonys::FsmId fsmId, int16_t depth) {
        Expected::checkTimerStopTimers(fsmId, depth);
        for (auto it{m_timeouts.begin()}; it != m_timeouts.end(); ) {
            if (it->timeout.fsmId == fsmId && it->timeout.depth == depth) {
                it = m_timeouts.erase(it);
            } else {
                ++it;
            }
        }
    }

    TestTimerService::Result TestTimerService::getNextTimeout() {
        if (m_timeouts.empty()) {
            return {m_systemTimeMs, false, {anonys::FsmId::Jukebox, 0, anonys::EventId{0}, 0}};
        }

        Result const result{m_timeouts.front()};
        m_timeouts.pop_front();
        if (result.systemTimeMs > m_systemTimeMs) {
            m_systemTimeMs = result.systemTimeMs;
        }
        return result;
    }
}
