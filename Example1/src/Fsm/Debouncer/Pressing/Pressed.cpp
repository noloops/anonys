// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/Debouncer.h"
#include "Terminals/EventSender.h"

namespace {
    using Fsm = anonys::fsm::Debouncer;

    struct Me {
        terminals::EventSender& eventSender;
    };

    void enter(Me& me) {
        me.eventSender.sendPressed();
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_1_3 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        return &anonys::DummyStates::Unhandled;
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pEventSender } };
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
