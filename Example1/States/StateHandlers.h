#ifndef STATES_STATEHANDLERS_H
#define STATES_STATEHANDLERS_H

#include "anonys/Types.h"

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
	uint16_t getSize();
	void liveCycle(bool create, void* pTerminals, void* pMembers);
	void handleEvent(void* pMembers, anonys::Event& event);
}

#endif // STATES_STATEHANDLERS_H
