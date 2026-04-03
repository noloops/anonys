#ifndef EXAMPLE1_FSM_A_IMPL_H
#define EXAMPLE1_FSM_A_IMPL_H

#include "anonys/Types.h"
#include "anonys/Utils.h"

#ifdef ANONYS_STATE_MACHINE_HEADER_GUARD
#error Only one state machine header can be included in a translation unit
#endif

namespace terminals {
	struct Std;
	class T1;
	class T2;
}

namespace anonys_1 {
	struct Terminals {
		terminals::Std* pStd;
		terminals::T1* pT1;
		terminals::T2* pT2;
	};
}

namespace anonys_1_1 {
	uint16_t getMembersSize();
	void liveCycle(bool create, void* pTerminals, void* pMembers);
	const anonys::StateDef* handleEvent(void* pMembers, anonys::Event& event);
}

#endif // EXAMPLE1_FSM_A_IMPL_H
