#include "anonys/fsm/Jukebox.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::Jukebox;

	struct Me {
		anonys::Timer timer;
		terminals::Std& std;
		terminals::Counter& counter;
		terminals::Mixer& mixer;
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterPaused, me.mixer.adjust(-80));
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitPaused);
	}

	anonys::State* handle(Me& me, events::Play& event) {
		me.std.log.write(terminals::Message::PlayInPaused);
		return &Fsm::Normal;
	}
}

// Generated code, do not edit:
namespace anonys_0_5 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Play>().id:
			return handle(me, *static_cast<events::Play*>(event.pData));
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
