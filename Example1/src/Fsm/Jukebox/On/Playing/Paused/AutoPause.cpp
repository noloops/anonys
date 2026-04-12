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
    using PauseCountdownTimeout = anonys::Timeout1;

    struct Me {
        anonys::Timer timer;
        terminals::Std& std;
        terminals::Countdown& countdown;
    };

    void enter(Me& me) {
        me.std.log.write(terminals::Message::EnterAutoPause);
        me.timer.start<PauseCountdownTimeout>(1000);
    }

    void exit(Me& me) {
        me.std.log.write(terminals::Message::ExitAutoPause);
    }

    anonys::State* handle(Me& me, const PauseCountdownTimeout& event) {
        me.std.log.write(terminals::Message::CountdownTimerInAutoPause);
        if (me.countdown.decrement()) {
            me.std.sender.send<events::Play>(Fsm::Id, events::Play{});
        }
        return &Fsm::AutoPause;
    }

    anonys::State* handle(Me& me, const events::Pause& event) {
        me.std.log.write(terminals::Message::PauseInAutoPause);
        return &Fsm::Paused;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_7 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::Pause>().id:
            return handle(me, *static_cast<events::Pause*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd, *terminals.pCountdown } };
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
