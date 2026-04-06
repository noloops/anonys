// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

#include "anonys/TracingService.h"

namespace env {
	class TestTracingService : public anonys::TracingService {
	public:
		void traceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) final;
		void traceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) final;
		void traceEnterState(anonys::FsmId fsmId, uint16_t stateId) final;
		void traceExitState(anonys::FsmId fsmId, uint16_t stateId) final;
	};
}
