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

#include "impl/terminalsJukebox.h"
#include "impl/terminalsLedJuggler.h"

namespace anonys
{
    class FsmPool {
    public:
        static constexpr uint16_t Count{ FsmCount };
        using TerminalsJukebox = anonys_0::Terminals;
        using TerminalsLedJuggler = anonys_1::Terminals;

        void handleEvent(FsmId fsmId, Event& event);

        void handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId);

        void setTracingService(TracingService* pTracingService = nullptr);

        void setTracingService(FsmId fsmId, TracingService* pTracingService = nullptr);

        void initializeJukebox(TimerService& timerService, terminals::Std& std);

        void initializeLedJuggler(TimerService& timerService, terminals::Led& led);

        void start();

    private:
        FsmCore m_fsm[Count]{};

        std::aligned_storage_t<BufferSize::Jukebox, anonys::StdAlign> m_bufferJukebox{};
        std::aligned_storage_t<BufferSize::LedJuggler, anonys::StdAlign> m_bufferLedJuggler{};

        TerminalsJukebox m_terminalsJukebox{};
        TerminalsLedJuggler m_terminalsLedJuggler{};

        bool m_started{ false };
    };
}
#endif // EXAMPLE1_FSM_H
