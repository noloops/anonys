#ifndef ANONYS_TYPES_H
#define ANONYS_TYPES_H

#include <cstdint>
#include "anonys/FsmId.h"
#include "anonys/EventId.h"

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

	struct DummyStates {
		static constexpr anonys::StateDef Unhandled = { 0, anonys::FsmId::Count_, nullptr, nullptr, nullptr, nullptr };
	};

	using State = const StateDef;
}

#endif // ANONYS_TYPES_H

