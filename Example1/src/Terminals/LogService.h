// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

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