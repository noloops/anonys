#pragma once

#include <cstdint>

namespace terminals {
	enum class Message : int32_t {
		EnterOff = 0,
		ExitOff,
		PowerOnInOff,
		EnterOn,
		ExitOn,
		PowerOffInOn,
		MalfunctionInOn,
		EnterIdle,
		ExitIdle,
		InsertCoinInIdle,
		DiagnosticInIdle,
		SleepTimeoutInIdle,
		MalfunctionStoppedInIdle,
		EnterPlaying,
		ExitPlaying,
		EjectInPlaying,
		AutoPauseInPlaying,
		EnterNormal,
		ExitNormal,
		PauseInNormal,
		SkipInNormal,
		TrackEndInNormal,
		EnterPaused,
		ExitPaused,
		PlayInPaused,
		ConfigureAutoPauseInPaused,
		EnterAutoPause,
		ExitAutoPause,
		PauseInAutoPause,
		CountdownTimerInAutoPause,
		CountdownReachedZero,
		EnterError,
		ExitError,
		ResetInError,
		RecoveryTimeoutInError,
	};

	class LogService {
	public:
		virtual ~LogService() = default;

		virtual void write(Message message) = 0;
		virtual void write(Message message, int32_t value) = 0;
	};
}