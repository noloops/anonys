#ifndef ANONYS_STATEMACHINEBASE_H
#define ANONYS_STATEMACHINEBASE_H

#include "Types.h"
#include "AnonysConfig.h"

namespace anonys
{
	class StateMachineBase {
	public:
		StateMachineBase(uint16_t stateMachineId, void* pTerminals, uint8_t* pAlignedBuffer, size_t bufferSize);

		~StateMachineBase();

		void handleEvent(Event& event);

		void executeTransition(const StateDef* pState);

		const StateDef* findSharedSuperState(const StateDef* pState);

		void popAll();

		void popToState(const StateDef& state);

		void pushToState(const StateDef* pState);

	private:
		struct El {
			StateDef const* pState{nullptr};
			uint8_t* pMembers{nullptr};
		};

		void push(const StateDef* pState);

		void pop();

		uint16_t const m_stateMachineId;

		void* const m_pTerminals;

		El m_stack[MaxNestedStates]{ };
		int16_t m_inner{ -1 };

		uint8_t* const m_pMembersBegin;
		uint8_t* const m_pMembersEnd;
		uint8_t* m_pMembersNext;
	};
}

#endif // ANONYS_STATEMACHINEBASE_H
