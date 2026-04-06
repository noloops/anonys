#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::Jukebox;
	using TrackEndTimeout = anonys::Timeout1;

	struct Me {
		anonys::Timer timer;
		terminals::Std& std;
		terminals::Counter& counter;
		terminals::Mixer& mixer;
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterNormal, me.counter.increment());
		me.mixer.setVolume(80);
		me.timer.start<TrackEndTimeout>(3000);
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitNormal);
	}

	anonys::State* handle(Me& me, events::Pause& event) {
		me.std.log.write(terminals::Message::PauseInNormal);
		return &Fsm::Paused;
	}

	anonys::State* handle(Me& me, events::Skip& event) {
		me.std.log.write(terminals::Message::SkipInNormal);
		return &Fsm::Normal;
	}

	anonys::State* handle(Me& me, TrackEndTimeout& event) {
		me.std.log.write(terminals::Message::TrackEndInNormal);
		return &Fsm::Idle;
	}
}

// Generated code, do not edit:
namespace anonys_0_4 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Pause>().id:
			return handle(me, *static_cast<events::Pause*>(event.pData));
		case anonys::getEventId<events::Skip>().id:
			return handle(me, *static_cast<events::Skip*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout1>().id:
			return handle(me, *static_cast<TrackEndTimeout*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd, *terminals.pCounter, *terminals.pMixer } };
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
