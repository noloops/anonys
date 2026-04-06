// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/Elevator.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::Elevator;
	using TimeoutA = anonys::Timeout1;

	struct Me {
		anonys::Timer timer;
		ctrl::reg::FloorTracker floorTracker{};
	};

	void enter(Me& me) {
		me.timer.start<TimeoutA>(15000);
	}

	void exit(Me& me) {
	}

	anonys::State* handle(Me& me, io::SensorTriggered& event) {
		return nullptr;
	}

	anonys::State* handle(Me& me, TimeoutA& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_0_3 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<io::SensorTriggered>().id:
            return handle(me, *static_cast<io::SensorTriggered*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer } };
            terminals.pFloorTracker = &me.floorTracker;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pFloorTracker = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
