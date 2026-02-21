#ifndef ANONYS_TYPES_H
#define ANONYS_TYPES_H

#include <cstdint>
namespace anonys
{
	struct Event {
		uint16_t eventId;
		void* pData;
	};

	struct StateDef {
		uint16_t stateId;
		uint16_t stateMachineId;
		const StateDef* pSuperState;
		uint16_t(*pGetSize)();
		void (*pLiveCycle)(bool create, void* pTerminals, void* pMembers);
		void (*pHandleEvent)(void* pMembers, Event& event);
	};
}

#endif // ANONYS_TYPES_H

