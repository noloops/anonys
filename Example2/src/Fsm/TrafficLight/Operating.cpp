// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/TrafficLight.h"
#include "Events.h"
#include "Terminals.h"

namespace {
    using Fsm = anonys::fsm::TrafficLight;

    struct Me {
        Display& display;
        ctrl::Panel panel{};
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const signals::Stop& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const signals::alert::Emergency& event) {
        return nullptr;
    }
}

// Generated code, do not edit:
namespace anonys_1_2 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<signals::Stop>().id:
            return handle(me, *static_cast<signals::Stop*>(event.pData));
        case anonys::getEventId<signals::alert::Emergency>().id:
            return handle(me, *static_cast<signals::alert::Emergency*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pDisplay } };
            terminals.pPanel = &me.panel;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pPanel = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
