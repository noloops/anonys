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
        term::etch::PlasmaGen& plasmaGen;
        term::etch::GasCtrl& gasCtrl;
        term::etch::PressureCtrl& pressureCtrl;
        term::etch::Endpoint endpoint{};
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::etch::EtchDone& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::etch::PlasmaIgnited& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::etch::PlasmaOff& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::etch::EndpointDetected& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_54 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::etch::EtchDone>().id:
            return handle(me, *static_cast<evt::etch::EtchDone*>(event.pData));
        case anonys::getEventId<evt::etch::PlasmaIgnited>().id:
            return handle(me, *static_cast<evt::etch::PlasmaIgnited*>(event.pData));
        case anonys::getEventId<evt::etch::PlasmaOff>().id:
            return handle(me, *static_cast<evt::etch::PlasmaOff*>(event.pData));
        case anonys::getEventId<evt::etch::EndpointDetected>().id:
            return handle(me, *static_cast<evt::etch::EndpointDetected*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pPlasmaGen, *terminals.pGasCtrl, *terminals.pPressureCtrl } };
            terminals.pEndpoint = &me.endpoint;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pEndpoint = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
