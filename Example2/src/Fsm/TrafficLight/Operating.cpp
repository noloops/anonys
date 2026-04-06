#include "anonys/fsm/TrafficLight.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::TrafficLight;

	struct Me {
		Display& display;
		ctrl::Panel panel{};
	};

	void enter(Me& me) {
	}

	void exit(Me& me) {
	}

	anonys::State* handle(Me& me, signals::Stop& event) {
		return nullptr;
	}

	anonys::State* handle(Me& me, signals::alert::Emergency& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_1_2 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<signals::Stop>().id:
            return handle(me, *static_cast<signals::Stop*>(event.pData));
        case anonys::getEventId<signals::alert::Emergency>().id:
            return handle(me, *static_cast<signals::alert::Emergency*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pDisplay } };
            terminals.pPanel = &me.panel;
            enter(me);
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            exit(me);
            me.~Me();
            terminals.pPanel = nullptr;
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
