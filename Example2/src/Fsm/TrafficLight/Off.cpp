#include "anonys/fsm/TrafficLight.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::TrafficLight;

	struct Me {
		Display& display;
	};

	void exit(Me& me) {
	}

	anonys::State* handle(Me& me, Start& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_1_1 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<Start>().id:
            return handle(me, *static_cast<Start*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
        if (create) {
            ::new (pMembers) Me{ *terminals.pDisplay };
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
