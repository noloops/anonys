#pragma once

#include <cstdint>

namespace terminals {
	enum class Message : int32_t {
		EnterOff = 0,
		ExitOff,
		PowerOnInOff,
		EnterIdle,
		ExitIdle,
		InsertCoinInIdle,
		PowerOffInIdle,
		DiagnosticInIdle,
		SleepTimeoutInIdle,
		EnterPlaying,
		ExitPlaying,
		EjectInPlaying,
		PowerOffInPlaying,
		MalfunctionInPlaying,
		EnterNormal,
		ExitNormal,
		PauseInNormal,
		SkipInNormal,
		TrackEndInNormal,
		EnterPaused,
		ExitPaused,
		PlayInPaused,
		EnterError,
		ExitError,
		ResetInError,
		RecoveryTimeoutInError,
		AutoPauseInPlaying,
		ConfigureAutoPauseInPaused,
		PauseInPaused,
		EnterAutoPause,
		ExitAutoPause,
		CountdownTimerInAutoPause,
		CountdownReachedZero,
	};

	class LogService {
	public:
		virtual ~LogService() = default;

		virtual void write(Message message) = 0;
		virtual void write(Message message, int32_t value) = 0;
	};
}