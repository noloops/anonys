// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/LedJuggler.h"
#include "Terminals/PatternTracker.h"

namespace {
    using Fsm = anonys::fsm::LedJuggler;

    struct Me {
        terminals::PatternTracker& patternTracker;
    };

    void enter(Me& me) {
        me.patternTracker.setPattern2();
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_6 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        return &anonys::DummyStates::Unhandled;
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pPatternTracker } };
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
