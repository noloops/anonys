#include "FsmBase.h"
#include "Utils.h"

namespace anonys
{
	FsmBase::FsmBase(FsmId fsmId, void* pTerminals, uint8_t* pAlignedBuffer, size_t bufferSize) :
		m_fsmId{ fsmId },
		m_pTerminals{ pTerminals },
		m_pMembersBegin{ pAlignedBuffer },
		m_pMembersEnd{ pAlignedBuffer + bufferSize },
		m_pMembersNext{ pAlignedBuffer }
	{
		ANONYS_ASSERT(m_pTerminals != nullptr);
		ANONYS_ASSERT(m_pMembersBegin != nullptr);
		ANONYS_ASSERT(bufferSize > 0);
	}

	FsmBase::~FsmBase()
	{
	}

	void FsmBase::handleEvent(Event& event)
	{
		for (int16_t i = m_inner; i >= 0; --i) {
			StateDef const* const pState{ m_stack[i].pState };
			if (pState->pHandleEvent != nullptr) {
				StateDef const* const pNewState{ pState->pHandleEvent(m_stack[i].pMembers, event) };
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

	void FsmBase::executeTransition(const StateDef* pState)
	{
		ANONYS_ASSERT((m_inner >= -1) && (m_inner < MaxNestedStates));
		ANONYS_ASSERT((pState == nullptr) || (pState->fsmId == m_fsmId));
		if (pState == nullptr) {
			popAll();
		}
		else if ((m_inner >= 0) && (pState->stateId == m_stack[m_inner].pState->stateId)) {
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

	const StateDef* FsmBase::findSharedSuperState(const StateDef* pState)
	{
		if ((pState == nullptr) || (m_inner < 0)) {
			return nullptr;
		}
		for (int16_t i{ m_inner }; i >= 0; --i) {
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
	void FsmBase::popAll()
	{
		while (m_inner >= 0) {
			pop();
		}
	}

	void FsmBase::popToState(const StateDef& state)
	{
		uint16_t const stateId{ state.stateId };
		while (m_inner >= 0) {
			if (m_stack[m_inner].pState->stateId == stateId) {
				return;
			}
			pop();
		}
		ANONYS_ASSERT(false);
	}

	void FsmBase::pushToState(const StateDef* pState)
	{
		uint16_t const innerStateId{ (m_inner < 0) ? 0U : m_stack[m_inner].pState->stateId};

		const StateDef* states[MaxNestedStates]{};
		int32_t count{ 0 };
		while ((pState != nullptr) && ((m_inner < 0) || (pState->stateId != innerStateId))) {
			ANONYS_ASSERT(count < MaxNestedStates);
			states[count++] = pState;
			pState = pState->pSuperState;
		}	
		for (int32_t i{ --count }; i >= 0; --i) {
			push(states[i]);
		}
	}

	void FsmBase::push(const StateDef* pState)
	{
		ANONYS_ASSERT(pState != nullptr);
		ANONYS_ASSERT(m_inner >= -1);
		ANONYS_ASSERT(m_inner < MaxNestedStates);
		ANONYS_ASSERT(pState->pLiveCycle != nullptr);
		uint8_t* const pMembersNext{ m_pMembersNext + pState->pGetMembersSize() };
		ANONYS_ASSERT(pMembersNext <= m_pMembersEnd);
		El& el{ m_stack[++m_inner] };
		el.pState = pState;
		el.pMembers = m_pMembersNext;
		m_pMembersNext = pMembersNext;
		el.pState->pLiveCycle(true, m_pTerminals, el.pMembers);
	}

	void FsmBase::pop()
	{
		ANONYS_ASSERT(m_inner >= 0);
		El& el{ m_stack[m_inner] };
		el.pState->pLiveCycle(false, m_pTerminals, el.pMembers);
		ANONYS_ASSERT(el.pMembers >= m_pMembersBegin);
		ANONYS_ASSERT(el.pMembers < m_pMembersEnd);
		m_pMembersNext = el.pMembers;
		el = { };
		--m_inner;
	}
}
