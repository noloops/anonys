#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::Jukebox;

	struct Me {
		terminals::Std& std;
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterOn);
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitOn);
	}

	anonys::State* handle(Me& me, events::PowerOff& event) {
		me.std.log.write(terminals::Message::PowerOffInOn);
		return &Fsm::Off;
	}

	anonys::State* handle(Me& me, events::Malfunction& event) {
		me.std.log.write(terminals::Message::MalfunctionInOn);
		return &Fsm::Error;
	}
}

// Generated code, do not edit:
namespace anonys_0_2 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        Me& me{ *static_cast<Me*>(pMembers) };
        switch (event.eventId.id) {
        case anonys::getEventId<events::PowerOff>().id:
            return handle(me, *static_cast<events::PowerOff*>(event.pData));
        case anonys::getEventId<events::Malfunction>().id:
            return handle(me, *static_cast<events::Malfunction*>(event.pData));
        default:
            return &anonys::DummyStates::Unhandled;
        }
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
        if (create) {
            Me& me{ *::new (pMembers) Me{ *terminals.pStd } };
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
