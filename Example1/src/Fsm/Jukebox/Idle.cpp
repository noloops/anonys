#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::Jukebox;
	using SleepTimer = anonys::Timeout2;

	struct Me {
		anonys::Timer timer;
		terminals::Std& std;
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterIdle);
		me.timer.start<SleepTimer>(5000);
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitIdle);
	}

	anonys::State* handle(Me& me, events::InsertCoin& event) {
		me.std.log.write(terminals::Message::InsertCoinInIdle);
		return &Fsm::Normal;
	}

	anonys::State* handle(Me& me, events::PowerOff& event) {
		me.std.log.write(terminals::Message::PowerOffInIdle);
		return &Fsm::Off;
	}

	anonys::State* handle(Me& me, events::Diagnostic& event) {
		me.std.log.write(terminals::Message::DiagnosticInIdle);
		return &Fsm::Idle;
	}

	anonys::State* handle(Me& me, SleepTimer& event) {
		me.std.log.write(terminals::Message::SleepTimeoutInIdle);
		return &Fsm::Off;
	}
}

// Generated code, do not edit:
namespace anonys_0_2 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::InsertCoin>().id:
			return handle(me, *static_cast<events::InsertCoin*>(event.pData));
		case anonys::getEventId<events::PowerOff>().id:
			return handle(me, *static_cast<events::PowerOff*>(event.pData));
		case anonys::getEventId<events::Diagnostic>().id:
			return handle(me, *static_cast<events::Diagnostic*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout2>().id:
			return handle(me, *static_cast<SleepTimer*>(event.pData));
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
