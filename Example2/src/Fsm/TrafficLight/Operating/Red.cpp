// ANONYS
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/fsm/TrafficLight.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::TrafficLight;
	using TimeoutA = anonys::Timeout1;
	using TimeoutB = anonys::Timeout2;

	struct Me {
		anonys::Timer timer;
		Display& display;
	};

	void enter(Me& me) {
		me.timer.start<TimeoutA>(30000);
		me.timer.start<TimeoutB>(45000);
	}

	void exit(Me& me) {
	}

	anonys::State* handle(Me& me, ctrl::Proceed& event) {
		return nullptr;
	}

	anonys::State* handle(Me& me, TimeoutA& event) {
		return nullptr;
	}

	anonys::State* handle(Me& me, TimeoutB& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_1_5 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<ctrl::Proceed>().id:
            return handle(me, *static_cast<ctrl::Proceed*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout2>().id:
            return handle(me, *static_cast<anonys::Timeout2*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pDisplay } };
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
