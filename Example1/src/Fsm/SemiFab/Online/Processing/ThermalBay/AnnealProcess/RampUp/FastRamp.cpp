// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/SemiFab.h"

namespace {
    using Fsm = anonys::fsm::SemiFab;
    using TimeoutA = anonys::Timeout1;

    struct Me {
        anonys::Timer timer;
        term::io::Std& std;
        term::thermal::Furnace& furnace;
        term::thermal::TempCtrl& tempCtrl;
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::thermal::SoakReached& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, evt::thermal::RampRate& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const TimeoutA& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_130 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::thermal::SoakReached>().id:
            return handle(me, *static_cast<evt::thermal::SoakReached*>(event.pData));
        case anonys::getEventId<evt::thermal::RampRate>().id:
            return handle(me, *static_cast<evt::thermal::RampRate*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd, *terminals.pFurnace, *terminals.pTempCtrl } };
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
