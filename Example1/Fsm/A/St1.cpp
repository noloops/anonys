#include "anonys/fsm/A.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::A;

	struct Me {
		terminals::Std& std;
		terminals::T1 t1{};
		terminals::Timer timer{ std.timerMngr };
	};

	void enter(Me& me) {
		me.std.log.write("Enter St1");
	}

	void exit(Me& me) {
		me.std.log.write("Exit St1");
	}

	anonys::State* handle(Me& me, events::Event1& event) {
		me.std.log.write("Handle Event1 in St1");
		return &Fsm::St1a;
	}

	anonys::State* handle(Me& me, events::Event4& event) {
		me.std.log.write("Handle Event4 in St1");
		return &Fsm::St2;
	}

	anonys::State* handle(Me& me, events::Event5& event) {
		me.std.log.write("Handle Event5 in St1");
		return nullptr;
	}
}

// Generated code, do not edit:
namespace anonys_1_1 {
	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_1::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pStd } };
			terminals.pT1 = &me.t1;
			enter(me);
		}
		else {
			Me& me{ *static_cast<Me*>(pMembers) };
			exit(me);
			me.~Me();
			terminals.pT1 = nullptr;
		}
	}

	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId) {
		case anonys::getEventId<events::Event1>():
			return handle(me, *static_cast<events::Event1*>(event.pData));
		case anonys::getEventId<events::Event4>():
			return handle(me, *static_cast<events::Event4*>(event.pData));
		case anonys::getEventId<events::Event5>():
			return handle(me, *static_cast<events::Event5*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}
}
