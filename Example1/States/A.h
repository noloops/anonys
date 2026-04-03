#ifndef EXAMPLE1_STATES_A_H
#define EXAMPLE1_STATES_A_H

#include "_impl/A.h"
#include "anonys/Types.h"
#include "StateMachines/StateMachineId.h"

#ifdef ANONYS_STATE_MACHINE_HEADER_GUARD
#error Only one state machine header can be included in a translation unit
#endif

namespace States {
	struct A {
		static constexpr anonys::StateDef St1 = { 1, 1, nullptr, anonys_1_1::getMembersSize, anonys_1_1::liveCycle, anonys_1_1::handleEvent };
	};
}

#endif // EXAMPLE1_STATES_A_H
