#include "anonys/fsm/A.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::A;
	using UserTimeout = anonys::Timeout1;

	struct Me {
		anonys::Timer timer;
		terminals::Std& std;
		terminals::T1 t1{};
	};

	void enter(Me& me) {
		me.std.log.write(terminals::Message::EnterSt1);
	}

	void exit(Me& me) {
		me.std.log.write(terminals::Message::ExitSt1);
	}

	anonys::State* handle(Me& me, events::Event1& event) {
		me.std.log.write(terminals::Message::Event1InSt1);
		return &Fsm::St1a;
	}

	anonys::State* handle(Me& me, events::Event4& event) {
		me.std.log.write(terminals::Message::Event4InSt1);
		return &Fsm::St2;
	}

	anonys::State* handle(Me& me, events::Event5& event) {
		me.std.log.write(terminals::Message::Event5InSt1);
		me.timer.start<UserTimeout>(500);
		return nullptr;
	}

	anonys::State* handle(Me& me, UserTimeout& event) {
		me.std.log.write(terminals::Message::UserTimeoutInSt1);
		return &Fsm::St1;
	}
}

// Generated code, do not edit:
namespace anonys_0_1 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Event1>().id:
			return handle(me, *static_cast<events::Event1*>(event.pData));
		case anonys::getEventId<events::Event4>().id:
			return handle(me, *static_cast<events::Event4*>(event.pData));
		case anonys::getEventId<events::Event5>().id:
			return handle(me, *static_cast<events::Event5*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout1>().id:
			return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd } };
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

	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}
}
