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

	// Test case: Start -> St1 -> St1a -> St1 -> St2 (with timeouts) -> St1
	bool Tester::test1() {
		std::cout << "=== test1 ===" << std::endl;

		Expected::enable(true);

		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		// --- Phase 1: Start -> enters St1 ---

		Expected::tracingTraceEnterState(anonys::FsmId::A, 1);
		Expected::logWrite(terminals::Message::EnterSt1);

		setup.fsm.start();

		if (!Expected::check()) { return failed(); }

		// --- Phase 2: Event1 in St1 -> St1a (push child onto St1) ---
		// St1 handles Event1: log, trace, then push St1a
		// St1a::enter logs + starts Timeout2(1000ms)

		Expected::logWrite(terminals::Message::Event1InSt1);
		Expected::tracingTraceHandledEvent(anonys::FsmId::A, 1, anonys::EventId{1});
		Expected::tracingTraceEnterState(anonys::FsmId::A, 2);
		Expected::logWrite(terminals::Message::EnterSt1a);
		Expected::timerStartTimer(anonys::FsmId::A, 1, anonys::EventId{60002}, 1000);

		executor.send<events::Event1>(anonys::FsmId::A, events::Event1{});

		if (!Expected::check()) { return failed(); }

		// No events were generated internally
		if (executor.sendNextEvent()) { return failed(); }

		// --- Phase 3: Event0 in St1a -> St1 (pop St1a+St1, re-enter St1) ---
		// St1a handles Event0: log, trace
		// Transition: pop St1a (exit+stopTimers), pop St1 (exit), push St1 (enter)

		Expected::logWrite(terminals::Message::Event0InSt1a);
		Expected::tracingTraceHandledEvent(anonys::FsmId::A, 2, anonys::EventId{0});
		Expected::tracingTraceExitState(anonys::FsmId::A, 2);
		Expected::logWrite(terminals::Message::ExitSt1a);
		Expected::timerStopTimers(anonys::FsmId::A, 1);
		Expected::tracingTraceExitState(anonys::FsmId::A, 1);
		Expected::logWrite(terminals::Message::ExitSt1);
		Expected::tracingTraceEnterState(anonys::FsmId::A, 1);
		Expected::logWrite(terminals::Message::EnterSt1);

		executor.send<events::Event0>(anonys::FsmId::A, events::Event0{});

		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// --- Phase 4: Event4 in St1 -> St2 (cross-tree transition) ---
		// St1 handles Event4: log, trace
		// Transition: pop St1 (exit), push St2 (enter + start Timeout1(150) + Timeout3(500))

		Expected::logWrite(terminals::Message::Event4InSt1);
		Expected::tracingTraceHandledEvent(anonys::FsmId::A, 1, anonys::EventId{4});
		Expected::tracingTraceExitState(anonys::FsmId::A, 1);
		Expected::logWrite(terminals::Message::ExitSt1);
		Expected::tracingTraceEnterState(anonys::FsmId::A, 3);
		Expected::logWrite(terminals::Message::EnterSt2);
		Expected::timerStartTimer(anonys::FsmId::A, 0, anonys::EventId{60001}, 150);
		Expected::timerStartTimer(anonys::FsmId::A, 0, anonys::EventId{60003}, 500);

		executor.send<events::Event4>(anonys::FsmId::A, events::Event4{});

		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// --- Phase 5: Timeout1 fires in St2 @150ms (no transition) ---
		// St2 handles Timeout1: log, start TimeoutB(50), start TimeoutA(200), trace
		// Timer queue after: Timeout2@200, Timeout1@350, Timeout3@500

		Expected::logWrite(terminals::Message::TimeoutAInSt2);
		Expected::timerStartTimer(anonys::FsmId::A, 0, anonys::EventId{60002}, 50);
		Expected::timerStartTimer(anonys::FsmId::A, 0, anonys::EventId{60001}, 200);
		Expected::tracingTraceHandledEvent(anonys::FsmId::A, 3, anonys::EventId{60001});

		if (!executor.sendNextTimeout()) { return failed(); }

		if (!Expected::check()) { return failed(); }

		// --- Phase 6: Timeout2 fires in St2 @200ms (no transition) ---
		// St2 handles Timeout2: log, trace

		Expected::logWrite(terminals::Message::TimeoutBInSt2);
		Expected::tracingTraceHandledEvent(anonys::FsmId::A, 3, anonys::EventId{60002});

		if (!executor.sendNextTimeout()) { return failed(); }

		if (!Expected::check()) { return failed(); }

		// --- Phase 7: Event7 in St2 -> St1 (exit St2 with timer cleanup) ---
		// St2 handles Event7: log, trace
		// Transition: pop St2 (exit+stopTimers), push St1 (enter)
		// stopTimers clears remaining Timeout1@350 and Timeout3@500

		Expected::logWrite(terminals::Message::Event7InSt2);
		Expected::tracingTraceHandledEvent(anonys::FsmId::A, 3, anonys::EventId{7});
		Expected::tracingTraceExitState(anonys::FsmId::A, 3);
		Expected::logWrite(terminals::Message::ExitSt2);
		Expected::timerStopTimers(anonys::FsmId::A, 0);
		Expected::tracingTraceEnterState(anonys::FsmId::A, 1);
		Expected::logWrite(terminals::Message::EnterSt1);

		executor.send<events::Event7>(anonys::FsmId::A, events::Event7{});

		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }

		return success();
	}
}
