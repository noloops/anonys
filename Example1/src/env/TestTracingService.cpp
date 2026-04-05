#include "TestTracingService.h"
#include <iostream>

namespace env {
	static const char* fsmIdName(anonys::FsmId fsmId) {
		switch (fsmId) {
		case anonys::FsmId::A: return "A";
		default: return "?";
		}
	}

	void TestTracingService::traceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		std::cout << "[Trace] FSM " << fsmIdName(fsmId)
			<< " State " << stateId
			<< " handled event " << eventId.id << std::endl;
	}

	void TestTracingService::traceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		std::cout << "[Trace] FSM " << fsmIdName(fsmId)
			<< " State " << stateId
			<< " unhandled event " << eventId.id << std::endl;
	}

	void TestTracingService::traceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		std::cout << "[Trace] FSM " << fsmIdName(fsmId)
			<< " enter State " << stateId << std::endl;
	}

	void TestTracingService::traceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		std::cout << "[Trace] FSM " << fsmIdName(fsmId)
			<< " exit State " << stateId << std::endl;
	}
}
