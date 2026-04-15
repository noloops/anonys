// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_FSM_DEBOUNCER_H
#define EXAMPLE1_FSM_DEBOUNCER_H

#include "anonys/impl/handlersDebouncer.h"
#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys::fsm {
    struct Debouncer {
        static constexpr anonys::FsmId Id{ anonys::FsmId::Debouncer };
        static constexpr anonys::StateDef Initial = { 1, anonys::FsmId::Debouncer, nullptr, anonys_1_1::getMembersSize, anonys_1_1::liveCycle, anonys_1_1::handleEvent };
        static constexpr anonys::StateDef Pressing = { 2, anonys::FsmId::Debouncer, nullptr, anonys_1_2::getMembersSize, anonys_1_2::liveCycle, anonys_1_2::handleEvent };
        static constexpr anonys::StateDef Pressed = { 3, anonys::FsmId::Debouncer, &Pressing, anonys_1_3::getMembersSize, anonys_1_3::liveCycle, anonys_1_3::handleEvent };
        static constexpr anonys::StateDef Releasing = { 4, anonys::FsmId::Debouncer, nullptr, anonys_1_4::getMembersSize, anonys_1_4::liveCycle, anonys_1_4::handleEvent };
        static constexpr anonys::StateDef Released = { 5, anonys::FsmId::Debouncer, &Releasing, anonys_1_5::getMembersSize, anonys_1_5::liveCycle, anonys_1_5::handleEvent };
    };
}

#endif // EXAMPLE1_FSM_DEBOUNCER_H
