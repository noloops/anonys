#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::Jukebox;

	struct Me {
		terminals::Std& std;
		terminals::Counter counter{};
		terminals::Mixer mixer{};
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterPlaying);
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitPlaying);
	}

	anonys::State* handle(Me& me, events::Eject& event) {
		me.std.log.write(terminals::Message::EjectInPlaying);
		return &Fsm::Idle;
	}

	anonys::State* handle(Me& me, events::PowerOff& event) {
		me.std.log.write(terminals::Message::PowerOffInPlaying);
		return &Fsm::Off;
	}

	anonys::State* handle(Me& me, events::Malfunction& event) {
		me.std.log.write(terminals::Message::MalfunctionInPlaying);
		return &Fsm::Error;
	}

	anonys::State* handle(Me& me, events::AutoPause& event) {
		me.std.log.write(terminals::Message::AutoPauseInPlaying);
		return &Fsm::AutoPause;
	}
}

// Generated code, do not edit:
namespace anonys_0_3 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Eject>().id:
			return handle(me, *static_cast<events::Eject*>(event.pData));
		case anonys::getEventId<events::PowerOff>().id:
			return handle(me, *static_cast<events::PowerOff*>(event.pData));
		case anonys::getEventId<events::Malfunction>().id:
			return handle(me, *static_cast<events::Malfunction*>(event.pData));
		case anonys::getEventId<events::AutoPause>().id:
			return handle(me, *static_cast<events::AutoPause*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pStd } };
			terminals.pCounter = &me.counter;
			terminals.pMixer = &me.mixer;
			enter(me);
		}
		else {
			Me& me{ *static_cast<Me*>(pMembers) };
			exit(me);
			me.~Me();
			terminals.pCounter = nullptr;
			terminals.pMixer = nullptr;
		}
	}

	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}
}
