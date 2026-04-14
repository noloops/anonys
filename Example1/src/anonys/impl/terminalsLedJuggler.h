// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_TERMINALS_LEDJUGGLER_H
#define EXAMPLE1_ANONYS_TERMINALS_LEDJUGGLER_H

#include "anonys/Timer.h"

namespace terminals {
    class Led;
    class PatternTracker;
}

namespace anonys_0 {
    struct Terminals {
        anonys::TimerCore* pTimer;
        terminals::Led* pLed;
        terminals::PatternTracker* pPatternTracker;
    };
}

#endif // EXAMPLE1_ANONYS_TERMINALS_LEDJUGGLER_H
