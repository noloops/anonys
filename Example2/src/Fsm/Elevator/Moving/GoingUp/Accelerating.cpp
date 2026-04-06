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

	struct Me {
		dev::SpeedRegulator speedRegulator{};
	};

	void enter(Me& me) {
	}

	void exit(Me& me) {
	}

	anonys::State* handle(Me& me, ctrl::Proceed& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_0_4 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<ctrl::Proceed>().id:
            return handle(me, *static_cast<ctrl::Proceed*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{} };
            terminals.pSpeedRegulator = &me.speedRegulator;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pSpeedRegulator = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
