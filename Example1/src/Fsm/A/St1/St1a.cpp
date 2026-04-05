#include "anonys/fsm/A.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::A;
	using UserTimeout = anonys::Timeout1;
	using SystemTimeout = anonys::Timeout2;

	struct Me {
		anonys::Timer timer;
		terminals::Std& std;
		terminals::T1& t1;
		terminals::T2 t2{};
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterSt1a);
		me.timer.start<SystemTimeout>(1000);
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitSt1a);
	}

	anonys::State* handle(Me& me, events::Event0& event) {
		me.std.log.write(terminals::Message::Event0InSt1a);
		return &Fsm::St1;
	}

	anonys::State* handle(Me& me, events::Event3& event) {
		me.std.log.write(terminals::Message::Event3InSt1a);
		return &Fsm::St1a;
	}

	anonys::State* handle(Me& me, events::Event5& event) {
		me.std.log.write(terminals::Message::Event5InSt1a);
		me.timer.start<UserTimeout>(100);
		return nullptr;
	}

	anonys::State* handle(Me& me, UserTimeout& event) {
		me.std.log.write(terminals::Message::UserTimeoutInSt1a);
		return &Fsm::St2;
	}

	anonys::State* handle(Me& me, SystemTimeout& event) {
		me.std.log.write(terminals::Message::SystemTimeoutInSt1a);
		return &Fsm::St1a;
	}
}

// Generated code, do not edit:
namespace anonys_0_2 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Event0>().id:
			return handle(me, *static_cast<events::Event0*>(event.pData));
		case anonys::getEventId<events::Event3>().id:
			return handle(me, *static_cast<events::Event3*>(event.pData));
		case anonys::getEventId<events::Event5>().id:
			return handle(me, *static_cast<events::Event5*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout1>().id:
			return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout2>().id:
			return handle(me, *static_cast<anonys::Timeout2*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd, *terminals.pT1 } };
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

	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}
}
