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
        term::litho::Scanner& scanner;
        term::litho::MaskStage& maskStage;
        term::litho::LaserSource& laserSource;
        term::litho::FocusUnit focusUnit{};
        term::litho::ReticleHandler reticleHandler{};
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::litho::ExposureDone& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::sys::EmergencyStop& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_32 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::litho::ExposureDone>().id:
            return handle(me, *static_cast<evt::litho::ExposureDone*>(event.pData));
        case anonys::getEventId<evt::sys::EmergencyStop>().id:
            return handle(me, *static_cast<evt::sys::EmergencyStop*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pScanner, *terminals.pMaskStage, *terminals.pLaserSource } };
            terminals.pFocusUnit = &me.focusUnit;
            terminals.pReticleHandler = &me.reticleHandler;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pFocusUnit = nullptr;
            terminals.pReticleHandler = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
