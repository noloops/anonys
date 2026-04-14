// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_FSM_LEDJUGGLER_H
#define EXAMPLE1_FSM_LEDJUGGLER_H

#include "anonys/impl/handlersLedJuggler.h"
#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys::fsm {
    struct LedJuggler {
        static constexpr anonys::FsmId Id{ anonys::FsmId::LedJuggler };
        static constexpr anonys::StateDef Running = { 1, anonys::FsmId::LedJuggler, nullptr, anonys_0_1::getMembersSize, anonys_0_1::liveCycle, anonys_0_1::handleEvent };
        static constexpr anonys::StateDef Pattern1 = { 2, anonys::FsmId::LedJuggler, &Running, anonys_0_2::getMembersSize, anonys_0_2::liveCycle, anonys_0_2::handleEvent };
        static constexpr anonys::StateDef BlinkA = { 3, anonys::FsmId::LedJuggler, &Pattern1, anonys_0_3::getMembersSize, anonys_0_3::liveCycle, anonys_0_3::handleEvent };
        static constexpr anonys::StateDef OnA = { 4, anonys::FsmId::LedJuggler, &Pattern1, anonys_0_4::getMembersSize, anonys_0_4::liveCycle, anonys_0_4::handleEvent };
        static constexpr anonys::StateDef OffA = { 5, anonys::FsmId::LedJuggler, &Pattern1, anonys_0_5::getMembersSize, anonys_0_5::liveCycle, anonys_0_5::handleEvent };
        static constexpr anonys::StateDef Pattern2 = { 6, anonys::FsmId::LedJuggler, &Running, anonys_0_6::getMembersSize, anonys_0_6::liveCycle, anonys_0_6::handleEvent };
        static constexpr anonys::StateDef BlinkB = { 7, anonys::FsmId::LedJuggler, &Pattern2, anonys_0_7::getMembersSize, anonys_0_7::liveCycle, anonys_0_7::handleEvent };
        static constexpr anonys::StateDef OnB = { 8, anonys::FsmId::LedJuggler, &Pattern2, anonys_0_8::getMembersSize, anonys_0_8::liveCycle, anonys_0_8::handleEvent };
        static constexpr anonys::StateDef OffB = { 9, anonys::FsmId::LedJuggler, &Pattern2, anonys_0_9::getMembersSize, anonys_0_9::liveCycle, anonys_0_9::handleEvent };
        static constexpr anonys::StateDef Paused = { 10, anonys::FsmId::LedJuggler, &Running, anonys_0_10::getMembersSize, anonys_0_10::liveCycle, anonys_0_10::handleEvent };
    };
}

#endif // EXAMPLE1_FSM_LEDJUGGLER_H
