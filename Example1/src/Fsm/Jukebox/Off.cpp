// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
    using Fsm = anonys::fsm::Jukebox;

    struct Me {
        terminals::Std& std;
    };

    void enter(Me& me) {
        me.std.log.write(terminals::Message::EnterOff);
    }

    void exit(Me& me) {
        me.std.log.write(terminals::Message::ExitOff);
    }

    anonys::State* handle(Me& me, events::PowerOn& event) {
        me.std.log.write(terminals::Message::PowerOnInOff);
        return &Fsm::Idle;
    }
}

// Generated code, do not edit:
namespace anonys_0_1 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::PowerOn>().id:
            return handle(me, *static_cast<events::PowerOn*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd } };
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
