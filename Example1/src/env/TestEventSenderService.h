// ANONYS
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

#include <cstdint>
#include <cstring>
#include <list>
#include <type_traits>
#include "anonys/Utils.h"
#include "Terminals/EventSenderService.h"

namespace env {
	class TestEventSenderService : public terminals::EventSenderService {
	public:
		using Buffer = std::aligned_storage_t<64, anonys::StdAlign>;

		struct Result {
			bool valid;
			anonys::FsmId fsmId;
			anonys::Event event;
		};

		Result getEvent(Buffer& buffer);
		bool isEmpty() const { return m_events.empty(); }
		void clear() { m_events.clear(); }

	protected:
		void doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) override;

	private:
		struct Entry {
			anonys::FsmId fsmId;
			anonys::Event event;
			Buffer buffer;
		};

		std::list<Entry> m_events;
	};
}
