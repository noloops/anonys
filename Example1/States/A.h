#ifndef STATES_A_H
#define STATES_A_H

#include "_impl/A.h"

namespace States {
	struct A {
		static constexpr anonys::StateDef St1 = { 1, 1, nullptr, anonys_1_1::getSize, anonys_1_1::liveCycle, anonys_1_1::handleEvent };
	};
}

#endif // STATES_A_H
