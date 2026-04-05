#include "Tester.h"
#include "Expected.h"
#include "Setup.h"
#include "Executor.h"
#include "Events/Events.h"
#include <iostream>

namespace env {
	bool Tester::failed() {
		std::cout << "TEST FAILED" << std::endl;
		return false;
	}

	bool Tester::success() {
		std::cout << "TEST PASSED" << std::endl;
		return true;
	}

	bool Tester::test1() {
		std::cout << "=== test1 ===" << std::endl;

		Expected::enable(true);

		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		// Record expected entries for fsm.start() -> enters St1
		Expected::tracingTraceEnterState(anonys::FsmId::A, 1);
		Expected::logWrite(terminals::Message::EnterSt1);

		setup.fsm.start();

		if (!Expected::isEmpty()) {
			return failed();
		}

		// Send Event1 -> transitions St1 -> St1a
		Expected::logWrite(terminals::Message::Event1InSt1);
		Expected::tracingTraceHandledEvent(anonys::FsmId::A, 1, anonys::EventId{1});
		Expected::tracingTraceEnterState(anonys::FsmId::A, 2);
		Expected::logWrite(terminals::Message::EnterSt1a);

		executor.send<events::Event1>(anonys::FsmId::A, events::Event1{});

		if (!Expected::isEmpty()) {
			return failed();
		}

		// Drain any follow-up events/timeouts
		while (executor.sendNext()) {
			if (!Expected::isEmpty()) {
				return failed();
			}
		}

		if (!Expected::isEmpty()) {
			return failed();
		}

		if (executor.hasWarnings()) {
			return failed();
		}

		return success();
	}
}
