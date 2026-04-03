#include "States/A.h"
#include "Terminals/Terminals.h"

namespace {
	using Fsm = States::A;

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
}

// Generated code - do not edit

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

	const anonys::StateDef* handleEvent(void* pMembers, anonys::Event& event) {
		return nullptr;
	}
}
