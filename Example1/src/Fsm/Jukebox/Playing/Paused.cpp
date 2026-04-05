#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::Jukebox;

	struct Me {
		terminals::Std& std;
		terminals::Mixer& mixer;
		terminals::Countdown countdown{std.log};
	};

	void enter(Me& me) {
		me.countdown.set(3);
		me.std.log.write(terminals::Message::EnterPaused, me.mixer.adjust(-80));
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitPaused);
	}

	anonys::State* handle(Me& me, events::Play& event) {
		me.std.log.write(terminals::Message::PlayInPaused);
		return &Fsm::Normal;
	}

	anonys::State* handle(Me& me, events::Pause& event) {
		me.std.log.write(terminals::Message::PauseInPaused);
		return &Fsm::Paused;
	}

	anonys::State* handle(Me& me, events::ConfigureAutoPause& event) {
		me.countdown.set(event.getCountdown());
		me.std.log.write(terminals::Message::ConfigureAutoPauseInPaused, event.getCountdown());
		return &Fsm::AutoPause;
	}
}

// Generated code, do not edit:
namespace anonys_0_5 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Play>().id:
			return handle(me, *static_cast<events::Play*>(event.pData));
		case anonys::getEventId<events::Pause>().id:
			return handle(me, *static_cast<events::Pause*>(event.pData));
		case anonys::getEventId<events::ConfigureAutoPause>().id:
			return handle(me, *static_cast<events::ConfigureAutoPause*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pMixer } };
			terminals.pCountdown = &me.countdown;
			enter(me);
		}
		else {
			Me& me{ *static_cast<Me*>(pMembers) };
			exit(me);
			me.~Me();
			terminals.pCountdown = nullptr;
		}
	}

	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}
}
