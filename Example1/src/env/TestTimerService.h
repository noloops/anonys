// ANONYS
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

#include <list>
#include "anonys/Timer.h"

namespace env {
	class TestTimerService : public anonys::TimerService {
	public:
		struct TimeoutDef {
			anonys::FsmId fsmId;
			int16_t depth;
			anonys::EventId eventId;
			uint32_t timeoutMs;
		};

		struct Result {
			uint32_t systemTimeMs;
			bool valid;
			TimeoutDef timeout;
		};

		Result getNextTimeout();
		bool isEmpty() const { return m_timeouts.empty(); }
		void clear() { m_timeouts.clear(); }

		void startTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) final;
		void stopTimers(anonys::FsmId fsmId, int16_t depth) final;

	private:
		std::list<Result> m_timeouts;
		uint32_t m_systemTimeMs{ 0 };
	};
}
