// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_TERMINALS_JUKEBOX_H
#define EXAMPLE1_ANONYS_TERMINALS_JUKEBOX_H

#include "anonys/Timer.h"

namespace terminals {
    struct Std;
    class Counter;
    class Mixer;
    class Countdown;
}

namespace anonys_0 {
    struct Terminals {
        anonys::TimerCore* pTimer;
        terminals::Std* pStd;
        terminals::Counter* pCounter;
        terminals::Mixer* pMixer;
        terminals::Countdown* pCountdown;
    };
}

#endif // EXAMPLE1_ANONYS_TERMINALS_JUKEBOX_H
