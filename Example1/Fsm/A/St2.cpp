#include "Fsm/A.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = fsm::A;

	struct Me {
		terminals::Std& std;
		terminals::T2 t2{};
		terminals::Timer timer1{ std.timerMngr };
		terminals::Timer timer2{ std.timerMngr };
	};

	void enter(Me& me) {
		me.std.log.write("Enter St2");
	}

	void exit(Me& me) {
		me.std.log.write("Exit St2");
	}

	anonys::State* handle(Me& me, events::Event2& event) {
		me.std.log.write("Handle Event0 in St1a");
		return &Fsm::St2;
	}

	anonys::State* handle(Me& me, events::Event7& event) {
		me.std.log.write("Handle Event3 in St1a");
		return &Fsm::St1a;
	}

	anonys::State* handle(Me& me, events::Event8& event) {
		me.std.log.write("Handle Event5 in St1a");
		return nullptr;
	}
}

// Generated code - do not edit

namespace anonys_1_3 {
	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pStd } };
			terminals.pT2 = &me.t2;
			enter(me);
		}
		else {
			Me& me{ *static_cast<Me*>(pMembers) };
			exit(me);
			me.~Me();
			terminals.pT2 = nullptr;
		}
	}

	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId) {
		case anonys::getEventId<events::Event2>():
			return handle(me, *static_cast<events::Event2*>(event.pData));
		case anonys::getEventId<events::Event7>():
			return handle(me, *static_cast<events::Event7*>(event.pData));
		case anonys::getEventId<events::Event8>():
			return handle(me, *static_cast<events::Event8*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

}
