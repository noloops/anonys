#include "TestTracingService.h"
#include "Expected.h"
#include "Helper.h"
#include <iostream>

namespace env {
	void TestTracingService::traceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		Expected::checkTracingTraceHandledEvent(fsmId, stateId, eventId);
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " " << Helper::getStateName(fsmId, stateId)
			<< " handled event " << Helper::getEventName(eventId) << std::endl;
	}

	void TestTracingService::traceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		Expected::checkTracingTraceUnhandledEvent(fsmId, stateId, eventId);
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " " << Helper::getStateName(fsmId, stateId)
			<< " unhandled event " << Helper::getEventName(eventId) << std::endl;
	}

	void TestTracingService::traceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		Expected::checkTracingTraceEnterState(fsmId, stateId);
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " enter " << Helper::getStateName(fsmId, stateId) << std::endl;
	}

	void TestTracingService::traceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		Expected::checkTracingTraceExitState(fsmId, stateId);
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " exit " << Helper::getStateName(fsmId, stateId) << std::endl;
	}
}
