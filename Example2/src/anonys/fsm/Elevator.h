// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE2_FSM_ELEVATOR_H
#define EXAMPLE2_FSM_ELEVATOR_H

#include "anonys/impl/handlersElevator.h"
#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys::fsm {
    struct Elevator {
        static constexpr anonys::FsmId Id{ anonys::FsmId::Elevator };
        static constexpr anonys::StateDef Idle = { 1, anonys::FsmId::Elevator, nullptr, anonys_0_1::getMembersSize, anonys_0_1::liveCycle, anonys_0_1::handleEvent };
        static constexpr anonys::StateDef Moving = { 2, anonys::FsmId::Elevator, nullptr, anonys_0_2::getMembersSize, anonys_0_2::liveCycle, anonys_0_2::handleEvent };
        static constexpr anonys::StateDef GoingUp = { 3, anonys::FsmId::Elevator, &Moving, anonys_0_3::getMembersSize, anonys_0_3::liveCycle, anonys_0_3::handleEvent };
        static constexpr anonys::StateDef Accelerating = { 4, anonys::FsmId::Elevator, &GoingUp, anonys_0_4::getMembersSize, anonys_0_4::liveCycle, anonys_0_4::handleEvent };
        static constexpr anonys::StateDef FullSpeed = { 5, anonys::FsmId::Elevator, &Accelerating, anonys_0_5::getMembersSize, anonys_0_5::liveCycle, anonys_0_5::handleEvent };
        static constexpr anonys::StateDef Decelerating = { 6, anonys::FsmId::Elevator, &GoingUp, anonys_0_6::getMembersSize, anonys_0_6::liveCycle, anonys_0_6::handleEvent };
        static constexpr anonys::StateDef GoingDown = { 7, anonys::FsmId::Elevator, &Moving, anonys_0_7::getMembersSize, anonys_0_7::liveCycle, anonys_0_7::handleEvent };
        static constexpr anonys::StateDef Stopped = { 8, anonys::FsmId::Elevator, nullptr, anonys_0_8::getMembersSize, anonys_0_8::liveCycle, anonys_0_8::handleEvent };
    };
}

#endif // EXAMPLE2_FSM_ELEVATOR_H
