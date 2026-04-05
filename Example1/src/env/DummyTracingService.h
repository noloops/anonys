#pragma once

#include "anonys/TracingService.h"

namespace env
{
	class DummyTracingService : public anonys::TracingService {
	public:
		void traceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) final {
		}
		void traceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) final {
		}
		void traceEnterState(anonys::FsmId fsmId, uint16_t stateId) final {
		}
		void traceExitState(anonys::FsmId fsmId, uint16_t stateId) final {
		}
	};
}