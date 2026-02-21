#ifndef STATES_A_ST1_H
#define STATES_A_ST1_H
#else
#error no multiple inclusion allowed!
#endif

#include <new>
#include "anonys/Utils.h"

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

	void handleEvent(void* pMembers, anonys::Event& event) {

	}
}
