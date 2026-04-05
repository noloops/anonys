#include "TestEventSenderService.h"
#include <cstring>

namespace env {
	void TestEventSenderService::doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		if (m_count >= MaxQueued) {
			return;
		}
		int tail = (m_head + m_count) % MaxQueued;
		Entry& entry = m_queue[tail];
		entry.active = true;
		entry.fsmId = fsmId;
		entry.eventIdValue = eventId.id;
		entry.size = size;
		if (size > 0 && pData != nullptr) {
			std::memcpy(entry.data, pData, size);
		}
		++m_count;
	}

	TestEventSenderService::Result TestEventSenderService::getEvent(Buffer& buffer) {
		if (m_count == 0) {
			return { false, { anonys::EventId{0}, nullptr } };
		}
		Entry& entry = m_queue[m_head];
		void* pBuffer = &buffer;
		if (entry.size > 0) {
			std::memcpy(pBuffer, entry.data, entry.size);
		}
		anonys::Event event{ anonys::EventId{entry.eventIdValue}, pBuffer };
		m_head = (m_head + 1) % MaxQueued;
		--m_count;
		return { true, event };
	}
}
