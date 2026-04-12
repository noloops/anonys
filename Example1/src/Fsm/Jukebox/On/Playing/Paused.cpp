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
        terminals::Mixer& mixer;
        terminals::Countdown countdown{std.log};
    };

    void enter(Me& me) {
        me.countdown.set(3);
        me.std.log.write(terminals::Message::EnterPaused, me.mixer.adjust(-80));
    }

    void exit(Me& me) {
        me.std.log.write(terminals::Message::ExitPaused);
    }

    anonys::State* handle(Me& me, const events::Play& event) {
        me.std.log.write(terminals::Message::PlayInPaused);
        return &Fsm::Normal;
    }

    anonys::State* handle(Me& me, events::ConfigureAutoPause& event) {
        me.countdown.set(event.getCountdown());
        me.std.log.write(terminals::Message::ConfigureAutoPauseInPaused, event.getCountdown());
        return &Fsm::AutoPause;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_6 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::Play>().id:
            return handle(me, *static_cast<events::Play*>(event.pData));
        case anonys::getEventId<events::ConfigureAutoPause>().id:
            return handle(me, *static_cast<events::ConfigureAutoPause*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pMixer } };
            terminals.pCountdown = &me.countdown;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pCountdown = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
