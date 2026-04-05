#pragma once

#include <cstdint>
#include "anonys/Types.h"
#include "anonys/EventId.h"

namespace terminals {
	class EventSenderService {
	public:
		virtual ~EventSenderService() = default;

		template <typename T>
		void send(anonys::FsmId fsmId, const T& event) {
			constexpr anonys::EventId eventId{ anonys::getEventId<T>() };
			doSend(fsmId, eventId, &event, sizeof(T));
		}

	protected:
		virtual void doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) = 0;
	};
}
