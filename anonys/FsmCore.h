#ifndef ANONYS_FSMBASE_H
#define ANONYS_FSMBASE_H

#include "Types.h"
#include "AnonysManualConfig.h"
#include "anonys/GeneratedConfig.h"
#include "anonys/FsmId.h"
#include "anonys/Timer.h"

namespace anonys
{
	class FsmCore : private TimerCore {
	public:
		void initialize(FsmId fsmId, void* pTerminals, uint8_t* pAlignedBuffer, size_t bufferSize, TimerService* pTimerService = nullptr);

		void handleEvent(Event& event);

		void handleTimeoutEvent(int16_t depth, EventId eventId);

		void executeTransition(const StateDef* pState);

		inline TimerCore& getTimerCore() { return *this; }

		inline int16_t getDepth() const { return m_depth; }

		// TODO Decide if 0 should be made invalid state id.
		inline uint16_t getCurrentStateId() const { return (m_depth >= 0) ? m_stack[m_depth].pState->stateId : 0; }

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

		void* m_pTerminals{nullptr};

		El m_stack[MaxNestedStates]{ };
		int16_t m_depth{ -1 };

		uint8_t* m_pMembersBegin{ nullptr };
		uint8_t* m_pMembersEnd{ nullptr };
		uint8_t* m_pMembersNext{ nullptr };
	};
}

#endif // ANONYS_FSMBASE_H
