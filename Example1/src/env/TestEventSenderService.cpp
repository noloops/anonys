#include "TestEventSenderService.h"
#include "Expected.h"
#include <cstring>

namespace env {
	void TestEventSenderService::doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		Expected::checkEventSenderDoSend(fsmId, eventId, pData, size);
		Entry entry{fsmId, {eventId, nullptr}, {}};
		if (size > 0 && pData != nullptr) {
			std::memcpy(&entry.buffer, pData, size);
		}
		entry.event.pData = &entry.buffer;
		m_events.push_back(entry);
	}

	TestEventSenderService::Result TestEventSenderService::getEvent(Buffer& buffer) {
		if (m_events.empty()) {
			return {false, anonys::FsmId::Jukebox, {anonys::EventId{0}, nullptr}};
		}
		Entry const& entry{m_events.front()};
		anonys::FsmId const fsmId{entry.fsmId};
		std::memcpy(&buffer, &entry.buffer, sizeof(Buffer));
		anonys::Event const event{entry.event.eventId, &buffer};
		m_events.pop_front();
		return {true, fsmId, event};
	}
}
