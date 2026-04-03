#include "Fsm/A.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = fsm::A;

	struct Me {
		terminals::Std& std;
		terminals::T1& t1;
		terminals::T2 t2{};
		terminals::Timer timer{ std.timerMngr };
	};

	void enter(Me& me) {
		me.std.log.write("Enter St1a");
	}

	void exit(Me& me) {
		me.std.log.write("Exit St1a");
	}

	anonys::State* handle(Me& me, events::Event0& event) {
		me.std.log.write("Handle Event0 in St1a");
		return &Fsm::St2;
	}

	anonys::State* handle(Me& me, events::Event3& event) {
		me.std.log.write("Handle Event3 in St1a");
		return &Fsm::St1a;
	}

	anonys::State* handle(Me& me, events::Event5& event) {
		me.std.log.write("Handle Event5 in St1a");
		return nullptr;
	}
}

// Generated code - do not edit

namespace anonys_1_2 {
	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pStd, *terminals.pT1 } };
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
		case anonys::getEventId<events::Event0>():
			return handle(me, *static_cast<events::Event0*>(event.pData));
		case anonys::getEventId<events::Event3>():
			return handle(me, *static_cast<events::Event3*>(event.pData));
		case anonys::getEventId<events::Event5>():
			return handle(me, *static_cast<events::Event5*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}
}
