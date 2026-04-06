#include "anonys/fsm/Elevator.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::Elevator;

	struct Me {
		ctrl::reg::FloorTracker& floorTracker;
	};

	anonys::State* handle(Me& me, io::SensorTriggered& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_0_6 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<io::SensorTriggered>().id:
			return handle(me, *static_cast<io::SensorTriggered*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			::new (pMembers) Me{ *terminals.pFloorTracker };
		}
		else {
			Me& me{ *static_cast<Me*>(pMembers) };
			me.~Me();
		}
	}

	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}
}
