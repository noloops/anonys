#ifndef EXAMPLE1_STATES_A_H
#define EXAMPLE1_STATES_A_H

#include "_impl/A_impl.h"
#include "AnonysFsmId.h"

namespace States {
	struct A {
		static constexpr anonys::FsmId Id{ anonys::FsmId::A };
		static constexpr anonys::StateDef St1 = { 1, anonys::FsmId::A, nullptr, anonys_1_1::getMembersSize, anonys_1_1::liveCycle, anonys_1_1::handleEvent };
	};
}

#endif // EXAMPLE1_STATES_A_H
