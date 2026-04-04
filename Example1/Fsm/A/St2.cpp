#include "anonys/fsm/A.h"
#include "Terminals/Terminals.h"
#include "Events/Events.h"

namespace {
	using Fsm = anonys::fsm::A;
	using TimeoutA = anonys::Timeout1;
	using TimeoutB = anonys::Timeout2;
	using TimeoutC = anonys::Timeout3;

	struct Me {
		anonys::Timer timer;
		terminals::Std& std;
		terminals::T2 t2{};
	};

	void enter(Me& me) {
		me.std.log.write("Enter St2");
		me.timer.start<TimeoutA>(150);
		me.timer.start<TimeoutC>(500);
	}

	void exit(Me& me) {
		me.std.log.write("Exit St2");
	}

	anonys::State* handle(Me& me, events::Event2& event) {
		me.std.log.write("Handle Event2 in St2");
		return &Fsm::St2;
	}

	anonys::State* handle(Me& me, events::Event7& event) {
		me.std.log.write("Handle Event7 in St2");
		return &Fsm::St1;
	}

	anonys::State* handle(Me& me, events::Event8& event) {
		me.std.log.write("Handle Event8 in St2");
		return &Fsm::St1a;
	}

	anonys::State* handle(Me& me, TimeoutA& event) {
		me.std.log.write("Handle TimeoutA in St2");
		me.timer.start<TimeoutB>(50);
		me.timer.start<TimeoutA>(200);
		return nullptr;
	}

	anonys::State* handle(Me& me, TimeoutB& event) {
		me.std.log.write("Handle TimeoutB in St2");
		return nullptr;
	}

	anonys::State* handle(Me& me, TimeoutC& event) {
		me.std.log.write("Handle TimeoutC in St2");
		return &Fsm::St1a;
	}
}

// Generated code, do not edit:
namespace anonys_0_3 {
	anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
		Me& me{ *static_cast<Me*>(pMembers) };
		switch (event.eventId.id) {
		case anonys::getEventId<events::Event2>().id:
			return handle(me, *static_cast<events::Event2*>(event.pData));
		case anonys::getEventId<events::Event7>().id:
			return handle(me, *static_cast<events::Event7*>(event.pData));
		case anonys::getEventId<events::Event8>().id:
			return handle(me, *static_cast<events::Event8*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout1>().id:
			return handle(me, *static_cast<anonys::Timeout1*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout2>().id:
			return handle(me, *static_cast<anonys::Timeout2*>(event.pData));
		case anonys::getTimeoutEventId<anonys::Timeout3>().id:
			return handle(me, *static_cast<anonys::Timeout3*>(event.pData));
		default:
			return &anonys::DummyStates::Unhandled;
		}
	}

	uint16_t getMembersSize() {
		return anonys::getAlignedSize<Me>();
	}

	void liveCycle(bool create, void* pTerminals, void* pMembers) {
		auto& terminals{ *static_cast<anonys_0::Terminals*>(pTerminals) };
		if (create) {
			Me& me{ *::new (pMembers) Me{ *terminals.pTimer, *terminals.pStd } };
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
}
