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
        term::thermal::Furnace& furnace;
        term::thermal::CoolingSys& coolingSys;
        term::thermal::TempCtrl tempCtrl{};
        term::thermal::GasSupply gasSupply{};
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::thermal::DiffusionStart& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::thermal::DiffusionDone& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_146 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::thermal::DiffusionStart>().id:
            return handle(me, *static_cast<evt::thermal::DiffusionStart*>(event.pData));
        case anonys::getEventId<evt::thermal::DiffusionDone>().id:
            return handle(me, *static_cast<evt::thermal::DiffusionDone*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pFurnace, *terminals.pCoolingSys } };
            terminals.pTempCtrl = &me.tempCtrl;
            terminals.pGasSupply = &me.gasSupply;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pTempCtrl = nullptr;
            terminals.pGasSupply = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
