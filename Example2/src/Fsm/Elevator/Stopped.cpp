#include "anonys/fsm/Elevator.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::Elevator;
	using TimeoutA = anonys::Timeout1;

	struct Me {
		anonys::Timer timer;
	};

	void enter(Me& me) {
		me.timer.start<TimeoutA>(60000);
	}

	anonys::State* handle(Me& me, Start& event) {
		return nullptr;
	}

	anonys::State* handle(Me& me, ctrl::cmd::Reset& event) {
		return nullptr;
	}

	anonys::State* handle(Me& me, TimeoutA& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_0_8 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<Start>().id:
            return handle(me, *static_cast<Start*>(event.pData));
        case anonys::getEventId<ctrl::cmd::Reset>().id:
            return handle(me, *static_cast<ctrl::cmd::Reset*>(event.pData));
        case anonys::getTimeoutEventId<anonys::Timeout1>().id:
            return handle(me, *static_cast<TimeoutA*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pTimer } };
            enter(me);
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
