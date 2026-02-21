#ifndef STATES_STATES_H
#define STATES_STATES_H

#include "StateHandlers.h"

namespace States {
	struct A {
		static constexpr anonys::StateDef St1 = { 1, 1, nullptr, anonys_1_1::getSize, anonys_1_1::liveCycle, anonys_1_1::handleEvent };
	};
}

#endif // STATES_STATES_H
