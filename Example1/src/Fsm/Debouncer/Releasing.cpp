// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/Debouncer.h"
#include "Events/Events.h"
#include "Terminals/EventSender.h"

namespace {
    using Fsm = anonys::fsm::Debouncer;
    using TimeoutConfirmed = anonys::Timeout1;

    struct Me {
        anonys::Timer timer;
    };

    void enter(Me& me) {
        me.timer.start<TimeoutConfirmed>(20);
    }

    anonys::State* handle(Me&, const events::ButtonEvent& event) {
        return event.pressed ? &Fsm::Pressing : nullptr;
    }

    anonys::State* handle(Me&, const TimeoutConfirmed&) {
        return &Fsm::Released;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_1_4 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::ButtonEvent>().id:
            return handle(me, *static_cast<events::ButtonEvent*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer } };
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            me.~Me();
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
