// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#ifndef EXAMPLE1_TERMINALS_EVENTSENDER_H
#define EXAMPLE1_TERMINALS_EVENTSENDER_H

#include <cstdint>

namespace terminals {

	class EventSender {
	public:
		void sendPressed() { m_queued = 1; }
		void sendReleased() { m_queued = -1; }

		int32_t consume() {
			int32_t const val{ m_queued };
			m_queued = 0;
			return val;
		}

	private:
		int32_t m_queued{ 0 };
	};

}

#endif // EXAMPLE1_TERMINALS_EVENTSENDER_H
