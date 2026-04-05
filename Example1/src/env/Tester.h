#pragma once

namespace env {
	class Tester {
	public:
		static bool testStartAndPowerCycle();
		static bool testSelfTransitions();
		static bool testPlayPauseCycle();
		static bool testEventBubbling();
		static bool testTrackEndTimeout();
		static bool testSleepTimeout();
		static bool testErrorAndRecovery();
		static bool testUnhandledEvent();

	private:
		static bool failed();
		static bool success();
	};
}
