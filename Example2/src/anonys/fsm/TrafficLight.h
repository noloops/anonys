// Generated file, do not edit!
#ifndef EXAMPLE2_FSM_TRAFFICLIGHT_H
#define EXAMPLE2_FSM_TRAFFICLIGHT_H

#include "anonys/impl/handlersTrafficLight.h"
#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys::fsm {
    struct TrafficLight {
        static constexpr anonys::FsmId Id{ anonys::FsmId::TrafficLight };
        static constexpr anonys::StateDef Off = { 1, anonys::FsmId::TrafficLight, nullptr, anonys_1_1::getMembersSize, anonys_1_1::liveCycle, anonys_1_1::handleEvent };
        static constexpr anonys::StateDef Operating = { 2, anonys::FsmId::TrafficLight, nullptr, anonys_1_2::getMembersSize, anonys_1_2::liveCycle, anonys_1_2::handleEvent };
        static constexpr anonys::StateDef Green = { 3, anonys::FsmId::TrafficLight, &Operating, anonys_1_3::getMembersSize, anonys_1_3::liveCycle, anonys_1_3::handleEvent };
        static constexpr anonys::StateDef Yellow = { 4, anonys::FsmId::TrafficLight, &Operating, anonys_1_4::getMembersSize, anonys_1_4::liveCycle, anonys_1_4::handleEvent };
        static constexpr anonys::StateDef Red = { 5, anonys::FsmId::TrafficLight, &Operating, anonys_1_5::getMembersSize, anonys_1_5::liveCycle, anonys_1_5::handleEvent };
        static constexpr anonys::StateDef Flashing = { 6, anonys::FsmId::TrafficLight, nullptr, anonys_1_6::getMembersSize, anonys_1_6::liveCycle, anonys_1_6::handleEvent };
    };
}

#endif // EXAMPLE2_FSM_TRAFFICLIGHT_H
