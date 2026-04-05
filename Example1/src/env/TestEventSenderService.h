#pragma once

#include <cstdint>
#include <cstring>
#include <type_traits>
#include "anonys/Utils.h"
#include "Terminals/EventSenderService.h"

namespace env {
	class TestEventSenderService : public terminals::EventSenderService {
	public:
		using Buffer = std::aligned_storage_t<64, anonys::StdAlign>;

		struct Result {
			bool valid;
			anonys::Event event;
		};

		Result getEvent(Buffer& buffer);

	protected:
		void doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) override;

	private:
		static constexpr int MaxQueued = 32;

		struct Entry {
			bool active;
			anonys::FsmId fsmId;
			uint16_t eventIdValue;
			uint16_t size;
			uint8_t data[64];
		};

		Entry m_queue[MaxQueued]{};
		int m_head{ 0 };
		int m_count{ 0 };
	};
}
