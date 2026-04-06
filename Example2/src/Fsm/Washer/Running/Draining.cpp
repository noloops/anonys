#include "anonys/fsm/Washer.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::Washer;
	using TimeoutA = anonys::Timeout1;

	struct Me {
		anonys::Timer timer;
		hw::Motor& motor;
		hw::io::Valve& valve;
	};

	void enter(Me& me) {
		me.timer.start<TimeoutA>(30000);
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
namespace anonys_2_7 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<io::SensorTriggered>().id:
			return handle(me, *static_cast<io::SensorTriggered*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout1>().id:
			return handle(me, *static_cast<TimeoutA*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_2::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pMotor, *terminals.pValve } };
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
