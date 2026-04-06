// ANONYS
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

namespace env {
	class Tester {
	public:
		static bool runAllTests();

		static bool testStartAndPowerCycle();
		static bool testSelfTransitions();
		static bool testPlayPauseCycle();
		static bool testEventBubbling();
		static bool testTrackEndTimeout();
		static bool testSleepTimeout();
		static bool testErrorAndRecovery();
		static bool testUnhandledEvent();
		static bool testAutoPauseCountdown();
		static bool testConfigureAndCancelAutoPause();
		static bool testMalfunctionStoppedInIdle();
		static bool testPauseUnhandledInPaused();

	private:
		static bool failed();
		static bool success();
	};
}
