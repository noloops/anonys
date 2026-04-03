#ifndef ANONYS_TYPES_H
#define ANONYS_TYPES_H

#include <cstdint>
#include "AnonysFsmId.h"
#include "AnonysEventId.h"

namespace anonys
{
	struct Event {
		EventId eventId;
		void* pData;
	};

	struct StateDef {
		uint16_t stateId;
		FsmId fsmId;
		const StateDef* pSuperState;
		uint16_t(*pGetMembersSize)();
		void (*pLiveCycle)(bool create, void* pTerminals, void* pMembers);
		const StateDef* (*pHandleEvent)(void* pMembers, Event& event);
	};

	struct Internal {
		static constexpr anonys::StateDef DummyStateUnhandled = { 0, anonys::FsmId::Count_, nullptr, nullptr, nullptr, nullptr };
	};
}

#endif // ANONYS_TYPES_H

