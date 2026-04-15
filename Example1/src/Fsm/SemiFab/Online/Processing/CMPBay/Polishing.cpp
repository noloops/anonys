// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/SemiFab.h"
#include "Events.h"
#include "Terminals.h"

namespace {
    using Fsm = anonys::fsm::SemiFab;

    struct Me {
        term::io::Std& std;
        term::cmp::PolishHead& polishHead;
        term::cmp::SlurryPump& slurryPump;
        term::cmp::CmpEndpoint cmpEndpoint{};
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::cmp::PolishDone& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::cmp::EndpointHit& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::cmp::RinseComplete& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_94 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::cmp::PolishDone>().id:
            return handle(me, *static_cast<evt::cmp::PolishDone*>(event.pData));
        case anonys::getEventId<evt::cmp::EndpointHit>().id:
            return handle(me, *static_cast<evt::cmp::EndpointHit*>(event.pData));
        case anonys::getEventId<evt::cmp::RinseComplete>().id:
            return handle(me, *static_cast<evt::cmp::RinseComplete*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pPolishHead, *terminals.pSlurryPump } };
            terminals.pCmpEndpoint = &me.cmpEndpoint;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pCmpEndpoint = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
