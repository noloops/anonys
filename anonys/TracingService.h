#ifndef ANONYS_TRACING_H
#define ANONYS_TRACING_H

#include <cstdint>
#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys
{
	class TracingService {
	public:
		virtual ~TracingService() = default;
		virtual void traceHandledEvent(FsmId fsmId, uint16_t stateId, EventId eventId) = 0;
		virtual void traceUnhandledEvent(FsmId fsmId, uint16_t stateId, EventId eventId) = 0;
		virtual void traceEnterState(FsmId fsmId, uint16_t stateId) = 0;
		virtual void traceExitState(FsmId fsmId, uint16_t stateId) = 0;
	};
}

#endif // ANONYS_TRACING_H
