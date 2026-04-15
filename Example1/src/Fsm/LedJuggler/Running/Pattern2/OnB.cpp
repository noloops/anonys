// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/LedJuggler.h"
#include "Terminals/Led.h"
#include "Events/Events.h"

namespace {
    using Fsm = anonys::fsm::LedJuggler;
    using TimeoutA = anonys::Timeout1;

    struct Me {
        anonys::Timer timer;
        terminals::Led& led;
    };

    void enter(Me& me) {
        me.led.setLed(true);
        me.timer.start<TimeoutA>(1000);
    }

    void exit(Me&) {}

    anonys::State* handle(Me&, const events::Click&) {
        return &Fsm::BlinkB;
    }

    anonys::State* handle(Me&, const TimeoutA&) {
        return &Fsm::OffB;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_8 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::Click>().id:
            return handle(me, *static_cast<events::Click*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pLed } };
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
