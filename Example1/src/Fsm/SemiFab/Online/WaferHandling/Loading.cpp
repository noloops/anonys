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
        term::hw::LoadLock& loadLock;
        term::sensor::WaferSensor& waferSensor;
    };

    void enter(Me& me) {
    }

    void exit(Me& me) {
    }

    anonys::State* handle(Me& me, const evt::wafer::CassetteInserted& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::wafer::WaferArrived& event) {
        return nullptr;
    }

    anonys::State* handle(Me& me, const evt::xfer::RobotReady& event) {
        return nullptr;
    }
}

// ANONYS - Generated code – do not edit the rest of this file!
namespace anonys_0_9 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<evt::wafer::CassetteInserted>().id:
            return handle(me, *static_cast<evt::wafer::CassetteInserted*>(event.pData));
        case anonys::getEventId<evt::wafer::WaferArrived>().id:
            return handle(me, *static_cast<evt::wafer::WaferArrived*>(event.pData));
        case anonys::getEventId<evt::xfer::RobotReady>().id:
            return handle(me, *static_cast<evt::xfer::RobotReady*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pPanel, *terminals.pRobot, *terminals.pLoadLock, *terminals.pWaferSensor } };
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
