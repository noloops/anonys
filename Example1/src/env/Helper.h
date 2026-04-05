#pragma once

#include <cstdint>
#include "anonys/FsmId.h"
#include "anonys/Types.h"
#include "Terminals/LogService.h"

namespace env {
	class Helper {
	public:
		static const char* getFsmName(anonys::FsmId fsmId);
		static const char* getStateName(anonys::FsmId fsmId, uint16_t stateId);
		static const char* getEventName(anonys::EventId eventId);
		static const char* getLogMessage(terminals::Message message);
	};
}
