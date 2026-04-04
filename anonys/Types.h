#ifndef ANONYS_TYPES_H
#define ANONYS_TYPES_H

#include <cstdint>
#include "anonys/FsmId.h"

namespace anonys
{
	// TODO make EventId a tag class.
	using EventId = uint16_t;

	static constexpr EventId MinTimoutEventId{ 60'001 };

	template <typename T> constexpr EventId getEventId() = delete;
	template <typename T> constexpr EventId getTimeoutEventId() = delete;

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

