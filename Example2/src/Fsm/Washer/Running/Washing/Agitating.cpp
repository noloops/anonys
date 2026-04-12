// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/Washer.h"
#include "Events.h"
#include "Terminals.h"

namespace {
    using Fsm = anonys::fsm::Washer;
    using TimeoutA = anonys::Timeout1;
    using TimeoutB = anonys::Timeout2;
    using TimeoutC = anonys::Timeout3;

    struct Me {
        anonys::Timer timer;
        dev::sensor::WaterLevel& waterLevel;
        hw::Motor& motor;
    };

    void enter(Me& me) {
        me.timer.start<TimeoutA>(5000);
        me.timer.start<TimeoutB>(15000);
        me.timer.start<TimeoutC>(30000);
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const io::data::Tick& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const TimeoutA& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const TimeoutB& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const TimeoutC& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_2_5 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<io::data::Tick>().id:
            return handle(me, *static_cast<io::data::Tick*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout2>().id:
            return handle(me, *static_cast<anonys::Timeout2*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout3>().id:
            return handle(me, *static_cast<anonys::Timeout3*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_2::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pWaterLevel, *terminals.pMotor } };
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
