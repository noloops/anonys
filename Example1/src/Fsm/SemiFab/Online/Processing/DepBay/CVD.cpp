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
        term::dep::Heater& heater;
        term::dep::GasMixer& gasMixer;
        term::dep::ThicknessMon thicknessMon{};
        term::dep::Showerhead showerhead{};
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::dep::DepositDone& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::dep::PurgeComplete& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_71 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::dep::DepositDone>().id:
            return handle(me, *static_cast<evt::dep::DepositDone*>(event.pData));
        case anonys::getEventId<evt::dep::PurgeComplete>().id:
            return handle(me, *static_cast<evt::dep::PurgeComplete*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pHeater, *terminals.pGasMixer } };
            terminals.pThicknessMon = &me.thicknessMon;
            terminals.pShowerhead = &me.showerhead;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pThicknessMon = nullptr;
            terminals.pShowerhead = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
