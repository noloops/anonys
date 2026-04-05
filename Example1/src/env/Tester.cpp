#include "Tester.h"
#include "Expected.h"
#include "Setup.h"
#include "Executor.h"
#include "Events/Events.h"
#include <iostream>

namespace env {
	using M = terminals::Message;
	constexpr auto F = anonys::FsmId::Jukebox;

	bool Tester::failed() {
		std::cout << "TEST FAILED" << std::endl;
		return false;
	}

	bool Tester::success() {
		std::cout << "TEST PASSED" << std::endl;
		return true;
	}

	// --- Helpers for common setup sequences ---

	static bool startJukebox(Setup& setup) {
		Expected::tracingTraceEnterState(F, 1);
		Expected::logWrite(M::EnterOff);
		setup.fsm.start();
		return Expected::check();
	}

	static bool powerOn(Executor& exec) {
		Expected::logWrite(M::PowerOnInOff);
		Expected::tracingTraceHandledEvent(F, 1, anonys::EventId{0});
		Expected::tracingTraceExitState(F, 1);
		Expected::logWrite(M::ExitOff);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 0, anonys::EventId{60002}, 5000);
		exec.send<events::PowerOn>(F, events::PowerOn{});
		if (!Expected::check()) return false;
		if (exec.sendNextEvent()) return false;
		return true;
	}

	static bool insertCoin(Executor& exec, int32_t count) {
		Expected::logWrite(M::InsertCoinInIdle);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{2});
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 3);
		Expected::logWrite(M::EnterPlaying);
		Expected::tracingTraceEnterState(F, 4);
		Expected::logWrite(M::EnterNormal, count);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 3000);
		exec.send<events::InsertCoin>(F, events::InsertCoin{});
		if (!Expected::check()) return false;
		if (exec.sendNextEvent()) return false;
		return true;
	}

	// --- Test cases ---

	bool Tester::testStartAndPowerCycle() {
		std::cout << "=== testStartAndPowerCycle ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();
		if (!powerOn(executor)) return failed();

		// PowerOff in Idle -> Off
		Expected::logWrite(M::PowerOffInIdle);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{1});
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 1);
		Expected::logWrite(M::EnterOff);
		executor.send<events::PowerOff>(F, events::PowerOff{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		// PowerOn again -> Idle (verify re-entry works)
		if (!powerOn(executor)) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}

	bool Tester::testSelfTransitions() {
		std::cout << "=== testSelfTransitions ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();
		if (!powerOn(executor)) return failed();

		// Diagnostic in Idle -> Idle (root self-transition: pop + push)
		Expected::logWrite(M::DiagnosticInIdle);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{7});
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 0, anonys::EventId{60002}, 5000);
		executor.send<events::Diagnostic>(F, events::Diagnostic{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		if (!insertCoin(executor, 1)) return failed();

		// Skip in Normal -> Normal (child self-transition: pop + push, parent survives)
		Expected::logWrite(M::SkipInNormal);
		Expected::tracingTraceHandledEvent(F, 4, anonys::EventId{5});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceEnterState(F, 4);
		Expected::logWrite(M::EnterNormal, 2);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 3000);
		executor.send<events::Skip>(F, events::Skip{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}

	bool Tester::testPlayPauseCycle() {
		std::cout << "=== testPlayPauseCycle ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();
		if (!powerOn(executor)) return failed();
		if (!insertCoin(executor, 1)) return failed();

		// Pause in Normal -> Paused (sibling: shared parent Playing stays)
		Expected::logWrite(M::PauseInNormal);
		Expected::tracingTraceHandledEvent(F, 4, anonys::EventId{4});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceEnterState(F, 5);
		Expected::logWrite(M::EnterPaused, 0);
		executor.send<events::Pause>(F, events::Pause{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		// Play in Paused -> Normal (sibling back, counter persists: 1 -> 2)
		Expected::logWrite(M::PlayInPaused);
		Expected::tracingTraceHandledEvent(F, 5, anonys::EventId{3});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitPaused);
		Expected::tracingTraceEnterState(F, 4);
		Expected::logWrite(M::EnterNormal, 2);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 3000);
		executor.send<events::Play>(F, events::Play{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		// Skip -> Normal (self, counter continues: 3)
		Expected::logWrite(M::SkipInNormal);
		Expected::tracingTraceHandledEvent(F, 4, anonys::EventId{5});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceEnterState(F, 4);
		Expected::logWrite(M::EnterNormal, 3);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 3000);
		executor.send<events::Skip>(F, events::Skip{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}

	bool Tester::testEventBubbling() {
		std::cout << "=== testEventBubbling ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();
		if (!powerOn(executor)) return failed();
		if (!insertCoin(executor, 1)) return failed();

		// Eject in Normal -> bubbles to Playing -> Idle
		Expected::logWrite(M::EjectInPlaying);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{6});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 0, anonys::EventId{60002}, 5000);
		executor.send<events::Eject>(F, events::Eject{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		// InsertCoin -> Normal again (fresh Playing, counter resets to 1)
		if (!insertCoin(executor, 1)) return failed();

		// PowerOff in Normal -> bubbles to Playing -> Off
		Expected::logWrite(M::PowerOffInPlaying);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{1});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceEnterState(F, 1);
		Expected::logWrite(M::EnterOff);
		executor.send<events::PowerOff>(F, events::PowerOff{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}

	bool Tester::testTrackEndTimeout() {
		std::cout << "=== testTrackEndTimeout ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();
		if (!powerOn(executor)) return failed();
		if (!insertCoin(executor, 1)) return failed();

		// TrackTimer fires at depth 1 -> Normal handles -> Idle
		Expected::logWrite(M::TrackEndInNormal);
		Expected::tracingTraceHandledEvent(F, 4, anonys::EventId{60001});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 0, anonys::EventId{60002}, 5000);
		if (!executor.sendNextTimeout()) return failed();
		if (!Expected::check()) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}

	bool Tester::testSleepTimeout() {
		std::cout << "=== testSleepTimeout ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();
		if (!powerOn(executor)) return failed();

		// SleepTimer fires at depth 0 -> Idle handles -> Off
		Expected::logWrite(M::SleepTimeoutInIdle);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{60002});
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 1);
		Expected::logWrite(M::EnterOff);
		if (!executor.sendNextTimeout()) return failed();
		if (!Expected::check()) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}

	bool Tester::testErrorAndRecovery() {
		std::cout << "=== testErrorAndRecovery ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();
		if (!powerOn(executor)) return failed();
		if (!insertCoin(executor, 1)) return failed();

		// Malfunction in Normal -> bubbles to Playing -> Error
		Expected::logWrite(M::MalfunctionInPlaying);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{8});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceEnterState(F, 6);
		Expected::logWrite(M::EnterError);
		Expected::timerStartTimer(F, 0, anonys::EventId{60003}, 10000);
		executor.send<events::Malfunction>(F, events::Malfunction{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		// Reset in Error -> Idle
		Expected::logWrite(M::ResetInError);
		Expected::tracingTraceHandledEvent(F, 6, anonys::EventId{9});
		Expected::tracingTraceExitState(F, 6);
		Expected::logWrite(M::ExitError);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 0, anonys::EventId{60002}, 5000);
		executor.send<events::Reset>(F, events::Reset{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		// Now test auto-recovery path: go to Normal -> Error again
		if (!insertCoin(executor, 1)) return failed();

		Expected::logWrite(M::MalfunctionInPlaying);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{8});
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceEnterState(F, 6);
		Expected::logWrite(M::EnterError);
		Expected::timerStartTimer(F, 0, anonys::EventId{60003}, 10000);
		executor.send<events::Malfunction>(F, events::Malfunction{});
		if (!Expected::check()) return failed();
		if (executor.sendNextEvent()) return failed();

		// RecoveryTimer fires -> Idle
		Expected::logWrite(M::RecoveryTimeoutInError);
		Expected::tracingTraceHandledEvent(F, 6, anonys::EventId{60003});
		Expected::tracingTraceExitState(F, 6);
		Expected::logWrite(M::ExitError);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 0, anonys::EventId{60002}, 5000);
		if (!executor.sendNextTimeout()) return failed();
		if (!Expected::check()) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}

	bool Tester::testUnhandledEvent() {
		std::cout << "=== testUnhandledEvent ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) return failed();

		// Send Play to Off -> nobody handles it
		Expected::tracingTraceUnhandledEvent(F, 0, anonys::EventId{3});
		executor.send<events::Play>(F, events::Play{});
		if (!Expected::check()) return failed();

		// Go to Normal to test deep unhandled event
		if (!powerOn(executor)) return failed();
		if (!insertCoin(executor, 1)) return failed();

		// Send Reset in Normal -> Normal doesn't handle, Playing doesn't handle
		Expected::tracingTraceUnhandledEvent(F, 0, anonys::EventId{9});
		executor.send<events::Reset>(F, events::Reset{});
		if (!Expected::check()) return failed();

		if (executor.hasWarnings()) return failed();
		return success();
	}
}
