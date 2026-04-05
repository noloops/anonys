#include "TestEventSenderService.h"
#include <cstring>

namespace env {
	void TestEventSenderService::doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		Entry entry{{eventId, nullptr}, {}};
		if (size > 0 && pData != nullptr) {
			std::memcpy(&entry.buffer, pData, size);
		}
		entry.event.pData = &entry.buffer;
		m_events.push_back(entry);
	}

	TestEventSenderService::Result TestEventSenderService::getEvent(Buffer& buffer) {
		if (m_events.empty()) {
			return {false, {anonys::EventId{0}, nullptr}};
		}
		Entry const& entry{m_events.front()};
		std::memcpy(&buffer, &entry.buffer, sizeof(Buffer));
		anonys::Event const event{entry.event.eventId, &buffer};
		m_events.pop_front();
		return {true, event};
	}
}
