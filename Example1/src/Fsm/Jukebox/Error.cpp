#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::Jukebox;
	using RecoveryTimeout = anonys::Timeout1;

	struct Me {
		anonys::Timer timer;
		terminals::Std& std;
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterError);
		me.timer.start<RecoveryTimeout>(10000);
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitError);
	}

	anonys::State* handle(Me& me, events::Reset& event) {
		me.std.log.write(terminals::Message::ResetInError);
		return &Fsm::Idle;
	}

	anonys::State* handle(Me& me, RecoveryTimeout& event) {
		me.std.log.write(terminals::Message::RecoveryTimeoutInError);
		return &Fsm::Idle;
	}
}

// Generated code, do not edit:
namespace anonys_0_8 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Reset>().id:
			return handle(me, *static_cast<events::Reset*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout1>().id:
			return handle(me, *static_cast<TimeoutA*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd } };
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
