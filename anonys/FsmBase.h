#ifndef ANONYS_FSMBASE_H
#define ANONYS_FSMBASE_H

#include "Types.h"
#include "AnonysConfig.h"
#include "AnonysFsmId.h"

namespace anonys
{
	class FsmBase {
	public:
		FsmBase(FsmId fsmId, void* pTerminals, uint8_t* pAlignedBuffer, size_t bufferSize);

		~FsmBase();

		void handleEvent(Event& event);

		void executeTransition(const StateDef* pState);

		int16_t getDepth() const { return m_inner; }

		uint16_t getCurrentStateId() const { return (m_inner >= 0) ? m_stack[m_inner].pState->stateId : 0; }

	private:
		struct El {
			StateDef const* pState{nullptr};
			uint8_t* pMembers{nullptr};
		};

		const StateDef* findSharedSuperState(const StateDef* pState);

		void popAll();

		void popToState(const StateDef& state);

		void pushToState(const StateDef* pState);

		void push(const StateDef* pState);

		void pop();

		FsmId const m_fsmId;

		void* const m_pTerminals;

		El m_stack[MaxNestedStates]{ };
		int16_t m_inner{ -1 };

		uint8_t* const m_pMembersBegin;
		uint8_t* const m_pMembersEnd;
		uint8_t* m_pMembersNext;
	};
}

#endif // ANONYS_FSMBASE_H
