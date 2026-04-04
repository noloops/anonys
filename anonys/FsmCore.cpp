#include "FsmCore.h"
#include "Utils.h"

namespace {
	class TimeoutDummy {};
}

namespace anonys
{
	void FsmCore::initialize(FsmId fsmId, void* pTerminals, uint8_t* pAlignedBuffer, size_t bufferSize, TimerService* pTimerService)
	{
		ANONYS_ASSERT(m_pTerminals == nullptr);
		ANONYS_ASSERT(pTerminals != nullptr);
		ANONYS_ASSERT(pAlignedBuffer != nullptr);
		ANONYS_ASSERT(bufferSize > 0);

		m_fsmId = fsmId;
		m_pTerminals = pTerminals;
		m_pMembersBegin = pAlignedBuffer;
		m_pMembersEnd = pAlignedBuffer + bufferSize;
		m_pMembersNext = pAlignedBuffer;
		m_pTimerService = pTimerService;
	}

	void FsmCore::handleEvent(Event& event)
	{
		ANONYS_ASSERT(m_pTerminals != nullptr);
		for (int16_t i = m_depth; i >= 0; --i) {
			StateDef const* const pState{ m_stack[i].pState };
			if (pState->pHandleEvent != nullptr) {
				m_curDepth = i;
				StateDef const* const pNewState{ pState->pHandleEvent(m_stack[i].pMembers, event) };
				m_curDepth = -1;
				if (pNewState == &DummyStates::Unhandled) {
					continue;
				}
				else if (pNewState != nullptr) {
					executeTransition(pNewState);
				}
				return;
			}
		}
	}

	void FsmCore::handleTimeoutEvent(int16_t depth, EventId eventId) {
		if ((depth >= 0) && (depth <= m_depth)) {
			StateDef const* const pState{ m_stack[depth].pState };
			if (pState->pHandleEvent != nullptr) {
				TimeoutDummy timeoutDummy{};
				Event event{ eventId, &timeoutDummy };
				m_curDepth = depth;
				StateDef const* const pNewState{ pState->pHandleEvent(m_stack[depth].pMembers, event) };
				m_curDepth = -1;
				if ((pNewState != nullptr) && (pNewState != &DummyStates::Unhandled)) {
					executeTransition(pNewState);
				}
			}
		}
	}

	void FsmCore::executeTransition(const StateDef* pState)
	{
		ANONYS_ASSERT(m_pTerminals != nullptr);
		ANONYS_ASSERT((m_depth >= -1) && (m_depth < MaxNestedStates));
		ANONYS_ASSERT((pState == nullptr) || (pState->fsmId == m_fsmId));
		if (pState == nullptr) {
			popAll();
		}
		else if ((m_depth >= 0) && (pState->stateId == m_stack[m_depth].pState->stateId)) {
			pop();
			push(pState);
		}
		else {
			StateDef const* const pShared{ findSharedSuperState(pState) };
			if (pShared != nullptr) {
				popToState(*pShared);
				if (pShared->stateId != pState->stateId) {
					pushToState(pState);
				}
			}
			else {
				popAll();
				pushToState(pState);
			}
		}
	}

	const StateDef* FsmCore::findSharedSuperState(const StateDef* pState)
	{
		if ((pState == nullptr) || (m_depth < 0)) {
			return nullptr;
		}
		for (int16_t i{ m_depth }; i >= 0; --i) {
			uint16_t const stateId{ m_stack[i].pState->stateId };
			const StateDef* pNext{ pState->pSuperState };
			while (pNext != nullptr) {
				if (stateId == pNext->stateId) {
					return pNext;
				}
				pNext = pNext->pSuperState;
			}
		}
		return nullptr;
	}
	void FsmCore::popAll()
	{
		while (m_depth >= 0) {
			pop();
		}
	}

	void FsmCore::popToState(const StateDef& state)
	{
		uint16_t const stateId{ state.stateId };
		while (m_depth >= 0) {
			if (m_stack[m_depth].pState->stateId == stateId) {
				return;
			}
			pop();
		}
		ANONYS_ASSERT(false);
	}

	void FsmCore::pushToState(const StateDef* pState)
	{
		uint16_t const innerStateId{ (m_depth < 0) ? 0U : m_stack[m_depth].pState->stateId};

		const StateDef* states[MaxNestedStates]{};
		int32_t count{ 0 };
		while ((pState != nullptr) && ((m_depth < 0) || (pState->stateId != innerStateId))) {
			ANONYS_ASSERT(count < MaxNestedStates);
			states[count++] = pState;
			pState = pState->pSuperState;
		}	
		for (int32_t i{ --count }; i >= 0; --i) {
			push(states[i]);
		}
	}

	void FsmCore::push(const StateDef* pState)
	{
		ANONYS_ASSERT(pState != nullptr);
		ANONYS_ASSERT(m_depth >= -1);
		ANONYS_ASSERT(m_depth < MaxNestedStates);
		ANONYS_ASSERT(pState->pLiveCycle != nullptr);
		uint8_t* const pMembersNext{ m_pMembersNext + pState->pGetMembersSize() };
		ANONYS_ASSERT(pMembersNext <= m_pMembersEnd);
		El& el{ m_stack[++m_depth] };
		el.pState = pState;
		el.pMembers = m_pMembersNext;
		m_pMembersNext = pMembersNext;
		m_curDepth = m_depth;
		el.pState->pLiveCycle(true, m_pTerminals, el.pMembers);
		m_curDepth = -1;
	}

	void FsmCore::pop()
	{
		ANONYS_ASSERT(m_depth >= 0);
		El& el{ m_stack[m_depth] };
		m_curDepth = m_depth;
		el.pState->pLiveCycle(false, m_pTerminals, el.pMembers);
		m_curDepth = -1;
		ANONYS_ASSERT(el.pMembers >= m_pMembersBegin);
		ANONYS_ASSERT(el.pMembers < m_pMembersEnd);
		m_pMembersNext = el.pMembers;
		el = { };
		--m_depth;
	}
}
