#include "TestTracingService.h"
#include "Helper.h"
#include <iostream>

namespace env {
	void TestTracingService::traceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " " << Helper::getStateName(fsmId, stateId)
			<< " handled event " << eventId.id << std::endl;
	}

	void TestTracingService::traceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " " << Helper::getStateName(fsmId, stateId)
			<< " unhandled event " << eventId.id << std::endl;
	}

	void TestTracingService::traceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " enter " << Helper::getStateName(fsmId, stateId) << std::endl;
	}

	void TestTracingService::traceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		std::cout << "[Trace] FSM " << Helper::getFsmName(fsmId)
			<< " exit " << Helper::getStateName(fsmId, stateId) << std::endl;
	}
}
