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
    using SleepTimeout = anonys::Timeout1;

    struct Me {
        anonys::Timer timer;
        terminals::Std& std;
    };

    void enter(Me& me) {
        me.std.log.write(terminals::Message::EnterIdle);
        me.timer.start<SleepTimeout>(5000);
    }

    void exit(Me& me) {
        me.std.log.write(terminals::Message::ExitIdle);
    }

    anonys::State* handle(Me& me, const events::InsertCoin& event) {
        me.std.log.write(terminals::Message::InsertCoinInIdle);
        return &Fsm::Normal;
    }

    anonys::State* handle(Me& me, const events::Malfunction& event) {
        me.std.log.write(terminals::Message::MalfunctionStoppedInIdle);
        return nullptr;
    }

    anonys::State* handle(Me& me, const events::Diagnostic& event) {
        me.std.log.write(terminals::Message::DiagnosticInIdle);
        return &Fsm::Idle;
    }

    anonys::State* handle(Me& me, const SleepTimeout& event) {
        me.std.log.write(terminals::Message::SleepTimeoutInIdle);
        return &Fsm::Off;
    }
}

// Generated code, do not edit:
namespace anonys_0_3 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::InsertCoin>().id:
            return handle(me, *static_cast<events::InsertCoin*>(event.pData));
        case anonys::getEventId<events::Malfunction>().id:
            return handle(me, *static_cast<events::Malfunction*>(event.pData));
        case anonys::getEventId<events::Diagnostic>().id:
            return handle(me, *static_cast<events::Diagnostic*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd } };
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
