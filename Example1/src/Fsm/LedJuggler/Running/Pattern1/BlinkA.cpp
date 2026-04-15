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
#include <array>

namespace {
    using Fsm = anonys::fsm::LedJuggler;
    using TimeoutCompleted = anonys::Timeout1;  // phase ends → OnA
    using TimeoutStep = anonys::Timeout2;  // blink step

    // on(300) off(150) on(100) off(450) — distinctive slow double-pulse
    static constexpr std::array<uint16_t, 4> Durations{ 300, 150, 100, 450 };

    struct Me {
        anonys::Timer timer;
        terminals::Led& led;
        uint16_t step{ 0 };
    };

    void enter(Me& me) {
        me.led.setLed(true);  // step 0 = even = on
        me.timer.start<TimeoutCompleted>(1300);
        me.timer.start<TimeoutStep>(Durations[0]);
    }

    void exit(Me&) {}

    anonys::State* handle(Me&, const events::Click&) {
        return &Fsm::Paused;
    }

    anonys::State* handle(Me&, const TimeoutCompleted&) {
        return &Fsm::OnA;
    }

    anonys::State* handle(Me& me, const TimeoutStep&) {
        me.step = (me.step + 1u) % static_cast<uint16_t>(Durations.size());
        me.led.setLed(me.step % 2 == 0);
        me.timer.start<TimeoutStep>(Durations[me.step]);
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_3 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::Click>().id:
            return handle(me, *static_cast<events::Click*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout2>().id:
            return handle(me, *static_cast<anonys::Timeout2*>(event.pData));
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
