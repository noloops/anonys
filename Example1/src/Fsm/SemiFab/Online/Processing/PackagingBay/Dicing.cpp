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

    struct Me {
        term::io::Std& std;
        term::ctrl::Panel& panel;
        term::hw::Robot& robot;
        term::pkg::Dicer& dicer;
        term::pkg::Marker marker{};
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::pkg::DiceStart& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::pkg::DiceDone& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_195 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::pkg::DiceStart>().id:
            return handle(me, *static_cast<evt::pkg::DiceStart*>(event.pData));
        case anonys::getEventId<evt::pkg::DiceDone>().id:
            return handle(me, *static_cast<evt::pkg::DiceDone*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pPanel, *terminals.pRobot, *terminals.pDicer } };
            terminals.pMarker = &me.marker;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pMarker = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
