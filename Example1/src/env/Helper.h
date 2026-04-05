#pragma once

#include <cstdint>
#include "anonys/FsmId.h"

namespace env {
	class Helper {
	public:
		static const char* getFsmName(anonys::FsmId fsmId);
		static const char* getStateName(anonys::FsmId fsmId, uint16_t stateId);
	};
}
