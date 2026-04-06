#include "anonys/fsm/Washer.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	using Fsm = anonys::fsm::Washer;

	struct Me {
		hw::Motor& motor;
	};

	void enter(Me& me) {
	}

	void exit(Me& me) {
	}

	anonys::State* handle(Me& me, ctrl::cmd::Reset& event) {
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_2_8 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<ctrl::cmd::Reset>().id:
            return handle(me, *static_cast<ctrl::cmd::Reset*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_2::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pMotor } };
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
