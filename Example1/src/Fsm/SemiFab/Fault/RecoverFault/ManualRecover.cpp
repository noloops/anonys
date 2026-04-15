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
        term::ctrl::Panel& panel;
        term::hw::VacuumGauge& vacuumGauge;
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::sys::Reset& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const TimeoutA& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_291 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::sys::Reset>().id:
            return handle(me, *static_cast<evt::sys::Reset*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd, *terminals.pPanel, *terminals.pVacuumGauge } };
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
