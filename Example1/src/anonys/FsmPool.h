// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_FSM_H
#define EXAMPLE1_FSM_H

#include <type_traits>

#include "anonys/FsmCore.h"

#include "impl/terminalsLedJuggler.h"
#include "impl/terminalsDebouncer.h"

namespace anonys
{
    class FsmPool {
    public:
        static constexpr uint16_t Count{ FsmCount };
        using TerminalsLedJuggler = anonys_0::Terminals;
        using TerminalsDebouncer = anonys_1::Terminals;

        void handleEvent(FsmId fsmId, Event& event);

        void handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId);

        void setTracingService(TracingService* pTracingService = nullptr);

        void setTracingService(FsmId fsmId, TracingService* pTracingService = nullptr);

        void initializeLedJuggler(TimerService& timerService, terminals::Led& led);

        void initializeDebouncer(TimerService& timerService, terminals::EventSender& eventSender);

        void start();

    private:
        FsmCore m_fsm[Count]{};

        std::aligned_storage_t<BufferSize::LedJuggler, anonys::StdAlign> m_bufferLedJuggler{};
        std::aligned_storage_t<BufferSize::Debouncer, anonys::StdAlign> m_bufferDebouncer{};

        TerminalsLedJuggler m_terminalsLedJuggler{};
        TerminalsDebouncer m_terminalsDebouncer{};

        bool m_started{ false };
    };
}
#endif // EXAMPLE1_FSM_H
