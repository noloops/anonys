// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "Tester.h"
#include "Expected.h"
#include "Setup.h"
#include "Executor.h"
#include "Events/Events.h"
#include <iostream>

namespace env {
	using M = terminals::Message;
	constexpr auto F = anonys::FsmId::Jukebox;

	bool Tester::runAllTests() {
		bool ok{true};
		if (!testStartAndPowerCycle()) {
			ok = false;
		}
		if (!testSelfTransitions()) {
			ok = false;
		}
		if (!testPlayPauseCycle()) {
			ok = false;
		}
		if (!testEventBubbling()) {
			ok = false;
		}
		if (!testTrackEndTimeout()) {
			ok = false;
		}
		if (!testSleepTimeout()) {
			ok = false;
		}
		if (!testErrorAndRecovery()) {
			ok = false;
		}
		if (!testUnhandledEvent()) {
			ok = false;
		}
		if (!testAutoPauseCountdown()) {
			ok = false;
		}
		if (!testConfigureAndCancelAutoPause()) {
			ok = false;
		}
		if (!testMalfunctionStoppedInIdle()) {
			ok = false;
		}
		if (!testPauseUnhandledInPaused()) {
			ok = false;
		}
		return ok;
	}

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
		Expected::logWrite(M::EnterOn);
		Expected::tracingTraceEnterState(F, 3);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 5000);
		exec.send<events::PowerOn>(F, events::PowerOn{});
		if (!Expected::check()) { return false; }
		if (exec.sendNextEvent()) { return false; }
		return true;
	}

	static bool insertCoin(Executor& exec, int32_t count) {
		Expected::logWrite(M::InsertCoinInIdle);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{2});
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceEnterState(F, 4);
		Expected::logWrite(M::EnterPlaying);
		Expected::tracingTraceEnterState(F, 5);
		Expected::logWrite(M::EnterNormal, count);
		Expected::timerStartTimer(F, 2, anonys::EventId{60001}, 3000);
		exec.send<events::InsertCoin>(F, events::InsertCoin{});
		if (!Expected::check()) { return false; }
		if (exec.sendNextEvent()) { return false; }
		return true;
	}

	static bool goToAutoPause(Executor& exec) {
		Expected::logWrite(M::AutoPauseInPlaying);
		Expected::tracingTraceHandledEvent(F, 4, anonys::EventId{10});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceEnterState(F, 6);
		Expected::logWrite(M::EnterPaused, 0);
		Expected::tracingTraceEnterState(F, 7);
		Expected::logWrite(M::EnterAutoPause);
		Expected::timerStartTimer(F, 3, anonys::EventId{60001}, 1000);
		exec.send<events::AutoPause>(F, events::AutoPause{});
		if (!Expected::check()) { return false; }
		if (exec.sendNextEvent()) { return false; }
		return true;
	}

	static bool fireCountdownTimer(Executor& exec, bool expectZero) {
		Expected::logWrite(M::CountdownTimerInAutoPause);
		if (expectZero) {
			Expected::logWrite(M::CountdownReachedZero);
			Expected::eventSenderDoSend(F, anonys::EventId{3}, nullptr, sizeof(events::Play));
		}
		Expected::tracingTraceHandledEvent(F, 7, anonys::EventId{60001});
		Expected::tracingTraceExitState(F, 7);
		Expected::logWrite(M::ExitAutoPause);
		Expected::timerStopTimers(F, 3);
		Expected::tracingTraceEnterState(F, 7);
		Expected::logWrite(M::EnterAutoPause);
		Expected::timerStartTimer(F, 3, anonys::EventId{60001}, 1000);
		if (!exec.sendNextTimeout()) { return false; }
		if (!Expected::check()) { return false; }
		return true;
	}

	static bool processAutoPlay(Executor& exec, int32_t normalCount) {
		Expected::logWrite(M::PlayInPaused);
		Expected::tracingTraceHandledEvent(F, 6, anonys::EventId{3});
		Expected::tracingTraceExitState(F, 7);
		Expected::logWrite(M::ExitAutoPause);
		Expected::timerStopTimers(F, 3);
		Expected::tracingTraceExitState(F, 6);
		Expected::logWrite(M::ExitPaused);
		Expected::tracingTraceEnterState(F, 5);
		Expected::logWrite(M::EnterNormal, normalCount);
		Expected::timerStartTimer(F, 2, anonys::EventId{60001}, 3000);
		if (!exec.sendNextEvent()) { return false; }
		if (!Expected::check()) { return false; }
		return true;
	}

	// --- Test cases ---

	bool Tester::testStartAndPowerCycle() {
		std::cout << "=== testStartAndPowerCycle ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }

		// PowerOff in Idle -> bubbles to On -> Off
		Expected::logWrite(M::PowerOffInOn);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{1});
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitOn);
		Expected::tracingTraceEnterState(F, 1);
		Expected::logWrite(M::EnterOff);
		executor.send<events::PowerOff>(F, events::PowerOff{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// PowerOn again -> Idle (verify re-entry works)
		if (!powerOn(executor)) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testSelfTransitions() {
		std::cout << "=== testSelfTransitions ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }

		// Diagnostic in Idle -> Idle (root self-transition: pop + push)
		Expected::logWrite(M::DiagnosticInIdle);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{7});
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceEnterState(F, 3);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 5000);
		executor.send<events::Diagnostic>(F, events::Diagnostic{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		if (!insertCoin(executor, 1)) { return failed(); }

		// Skip in Normal -> Normal (child self-transition: pop + push, parent survives)
		Expected::logWrite(M::SkipInNormal);
		Expected::tracingTraceHandledEvent(F, 5, anonys::EventId{5});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceEnterState(F, 5);
		Expected::logWrite(M::EnterNormal, 2);
		Expected::timerStartTimer(F, 2, anonys::EventId{60001}, 3000);
		executor.send<events::Skip>(F, events::Skip{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testPlayPauseCycle() {
		std::cout << "=== testPlayPauseCycle ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// Pause in Normal -> Paused (sibling: shared parent Playing stays)
		Expected::logWrite(M::PauseInNormal);
		Expected::tracingTraceHandledEvent(F, 5, anonys::EventId{4});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceEnterState(F, 6);
		Expected::logWrite(M::EnterPaused, 0);
		executor.send<events::Pause>(F, events::Pause{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// Play in Paused -> Normal (sibling back, counter persists: 1 -> 2)
		Expected::logWrite(M::PlayInPaused);
		Expected::tracingTraceHandledEvent(F, 6, anonys::EventId{3});
		Expected::tracingTraceExitState(F, 6);
		Expected::logWrite(M::ExitPaused);
		Expected::tracingTraceEnterState(F, 5);
		Expected::logWrite(M::EnterNormal, 2);
		Expected::timerStartTimer(F, 2, anonys::EventId{60001}, 3000);
		executor.send<events::Play>(F, events::Play{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// Skip -> Normal (self, counter continues: 3)
		Expected::logWrite(M::SkipInNormal);
		Expected::tracingTraceHandledEvent(F, 5, anonys::EventId{5});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceEnterState(F, 5);
		Expected::logWrite(M::EnterNormal, 3);
		Expected::timerStartTimer(F, 2, anonys::EventId{60001}, 3000);
		executor.send<events::Skip>(F, events::Skip{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testEventBubbling() {
		std::cout << "=== testEventBubbling ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// Eject in Normal -> bubbles to Playing -> Idle
		Expected::logWrite(M::EjectInPlaying);
		Expected::tracingTraceHandledEvent(F, 4, anonys::EventId{6});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceEnterState(F, 3);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 5000);
		executor.send<events::Eject>(F, events::Eject{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// InsertCoin -> Normal again (fresh Playing, counter resets to 1)
		if (!insertCoin(executor, 1)) { return failed(); }

		// PowerOff in Normal -> bubbles to Playing -> On -> Off
		Expected::logWrite(M::PowerOffInOn);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{1});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitOn);
		Expected::tracingTraceEnterState(F, 1);
		Expected::logWrite(M::EnterOff);
		executor.send<events::PowerOff>(F, events::PowerOff{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testTrackEndTimeout() {
		std::cout << "=== testTrackEndTimeout ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// TrackTimer fires at depth 2 -> Normal handles -> Idle
		Expected::logWrite(M::TrackEndInNormal);
		Expected::tracingTraceHandledEvent(F, 5, anonys::EventId{60001});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceEnterState(F, 3);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 5000);
		if (!executor.sendNextTimeout()) { return failed(); }
		if (!Expected::check()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testSleepTimeout() {
		std::cout << "=== testSleepTimeout ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }

		// SleepTimer fires at depth 1 -> Idle handles -> Off
		Expected::logWrite(M::SleepTimeoutInIdle);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{60001});
		Expected::tracingTraceExitState(F, 3);
		Expected::logWrite(M::ExitIdle);
		Expected::timerStopTimers(F, 1);
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitOn);
		Expected::tracingTraceEnterState(F, 1);
		Expected::logWrite(M::EnterOff);
		if (!executor.sendNextTimeout()) { return failed(); }
		if (!Expected::check()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testErrorAndRecovery() {
		std::cout << "=== testErrorAndRecovery ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// Malfunction in Normal -> bubbles to Playing -> On -> Error
		Expected::logWrite(M::MalfunctionInOn);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{8});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitOn);
		Expected::tracingTraceEnterState(F, 8);
		Expected::logWrite(M::EnterError);
		Expected::timerStartTimer(F, 0, anonys::EventId{60001}, 10000);
		executor.send<events::Malfunction>(F, events::Malfunction{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// Reset in Error -> Idle
		Expected::logWrite(M::ResetInError);
		Expected::tracingTraceHandledEvent(F, 8, anonys::EventId{9});
		Expected::tracingTraceExitState(F, 8);
		Expected::logWrite(M::ExitError);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterOn);
		Expected::tracingTraceEnterState(F, 3);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 5000);
		executor.send<events::Reset>(F, events::Reset{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// Now test auto-recovery path: go to Normal -> Error again
		if (!insertCoin(executor, 1)) { return failed(); }

		Expected::logWrite(M::MalfunctionInOn);
		Expected::tracingTraceHandledEvent(F, 2, anonys::EventId{8});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceExitState(F, 4);
		Expected::logWrite(M::ExitPlaying);
		Expected::tracingTraceExitState(F, 2);
		Expected::logWrite(M::ExitOn);
		Expected::tracingTraceEnterState(F, 8);
		Expected::logWrite(M::EnterError);
		Expected::timerStartTimer(F, 0, anonys::EventId{60001}, 10000);
		executor.send<events::Malfunction>(F, events::Malfunction{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// RecoveryTimer fires -> Idle
		Expected::logWrite(M::RecoveryTimeoutInError);
		Expected::tracingTraceHandledEvent(F, 8, anonys::EventId{60001});
		Expected::tracingTraceExitState(F, 8);
		Expected::logWrite(M::ExitError);
		Expected::timerStopTimers(F, 0);
		Expected::tracingTraceEnterState(F, 2);
		Expected::logWrite(M::EnterOn);
		Expected::tracingTraceEnterState(F, 3);
		Expected::logWrite(M::EnterIdle);
		Expected::timerStartTimer(F, 1, anonys::EventId{60001}, 5000);
		if (!executor.sendNextTimeout()) { return failed(); }
		if (!Expected::check()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testUnhandledEvent() {
		std::cout << "=== testUnhandledEvent ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }

		// Send Play to Off -> nobody handles it
		Expected::tracingTraceUnhandledEvent(F, 0, anonys::EventId{3});
		executor.send<events::Play>(F, events::Play{});
		if (!Expected::check()) { return failed(); }

		// Go to Normal to test deep unhandled event
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// Send Reset in Normal -> Normal doesn't handle, Playing doesn't handle
		Expected::tracingTraceUnhandledEvent(F, 0, anonys::EventId{9});
		executor.send<events::Reset>(F, events::Reset{});
		if (!Expected::check()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testAutoPauseCountdown() {
		std::cout << "=== testAutoPauseCountdown ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// AutoPause event in Normal -> bubbles to Playing -> exits Normal, enters Paused, enters AutoPause
		if (!goToAutoPause(executor)) { return failed(); }

		// Fire timeout 1: countdown 3->2
		if (!fireCountdownTimer(executor, false)) { return failed(); }

		// Fire timeout 2: countdown 2->1
		if (!fireCountdownTimer(executor, false)) { return failed(); }

		// Fire timeout 3: countdown 1->0, sends Play
		if (!fireCountdownTimer(executor, true)) { return failed(); }

		// Process queued Play event: exits AutoPause+Paused, enters Normal (count 2)
		if (!processAutoPlay(executor, 2)) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testConfigureAndCancelAutoPause() {
		std::cout << "=== testConfigureAndCancelAutoPause ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// AutoPause event -> Paused/AutoPause (countdown 3)
		if (!goToAutoPause(executor)) { return failed(); }

		// Fire timeout 1: countdown 3->2
		if (!fireCountdownTimer(executor, false)) { return failed(); }

		// Pause event in AutoPause -> self-transition of parent Paused
		// exits AutoPause, exits Paused, enters Paused (mixer: 0 adjusted by -80 = -80)
		Expected::logWrite(M::PauseInAutoPause);
		Expected::tracingTraceHandledEvent(F, 7, anonys::EventId{4});
		Expected::tracingTraceExitState(F, 7);
		Expected::logWrite(M::ExitAutoPause);
		Expected::timerStopTimers(F, 3);
		Expected::tracingTraceExitState(F, 6);
		Expected::logWrite(M::ExitPaused);
		Expected::tracingTraceEnterState(F, 6);
		Expected::logWrite(M::EnterPaused, -80);
		executor.send<events::Pause>(F, events::Pause{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// ConfigureAutoPause(2) in Paused -> sets countdown to 2, enters AutoPause
		Expected::logWrite(M::ConfigureAutoPauseInPaused, 2);
		Expected::tracingTraceHandledEvent(F, 6, anonys::EventId{11});
		Expected::tracingTraceEnterState(F, 7);
		Expected::logWrite(M::EnterAutoPause);
		Expected::timerStartTimer(F, 3, anonys::EventId{60001}, 1000);
		executor.send<events::ConfigureAutoPause>(F, events::ConfigureAutoPause{2});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// Fire timeout 1: countdown 2->1
		if (!fireCountdownTimer(executor, false)) { return failed(); }

		// Fire timeout 2: countdown 1->0, sends Play
		if (!fireCountdownTimer(executor, true)) { return failed(); }

		// Process queued Play: exits AutoPause+Paused, enters Normal (count 2)
		if (!processAutoPlay(executor, 2)) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testMalfunctionStoppedInIdle() {
		std::cout << "=== testMalfunctionStoppedInIdle ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }

		// Malfunction in Idle -> Idle handles, returns nullptr (no transition)
		Expected::logWrite(M::MalfunctionStoppedInIdle);
		Expected::tracingTraceHandledEvent(F, 3, anonys::EventId{8});
		executor.send<events::Malfunction>(F, events::Malfunction{});
		if (!Expected::check()) { return failed(); }

		// Verify state is still Idle by sending InsertCoin -> Normal
		if (!insertCoin(executor, 1)) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}

	bool Tester::testPauseUnhandledInPaused() {
		std::cout << "=== testPauseUnhandledInPaused ===" << std::endl;
		Expected::enable(true);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		if (!startJukebox(setup)) { return failed(); }
		if (!powerOn(executor)) { return failed(); }
		if (!insertCoin(executor, 1)) { return failed(); }

		// Pause in Normal -> Paused
		Expected::logWrite(M::PauseInNormal);
		Expected::tracingTraceHandledEvent(F, 5, anonys::EventId{4});
		Expected::tracingTraceExitState(F, 5);
		Expected::logWrite(M::ExitNormal);
		Expected::timerStopTimers(F, 2);
		Expected::tracingTraceEnterState(F, 6);
		Expected::logWrite(M::EnterPaused, 0);
		executor.send<events::Pause>(F, events::Pause{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		// Pause in Paused -> unhandled (handler moved to AutoPause)
		Expected::tracingTraceUnhandledEvent(F, 0, anonys::EventId{4});
		executor.send<events::Pause>(F, events::Pause{});
		if (!Expected::check()) { return failed(); }

		// Verify state is still Paused by sending Play -> Normal
		Expected::logWrite(M::PlayInPaused);
		Expected::tracingTraceHandledEvent(F, 6, anonys::EventId{3});
		Expected::tracingTraceExitState(F, 6);
		Expected::logWrite(M::ExitPaused);
		Expected::tracingTraceEnterState(F, 5);
		Expected::logWrite(M::EnterNormal, 2);
		Expected::timerStartTimer(F, 2, anonys::EventId{60001}, 3000);
		executor.send<events::Play>(F, events::Play{});
		if (!Expected::check()) { return failed(); }
		if (executor.sendNextEvent()) { return failed(); }

		if (executor.hasWarnings()) { return failed(); }
		return success();
	}
}
