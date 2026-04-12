// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE2_ANONYS_TERMINALS_ELEVATOR_H
#define EXAMPLE2_ANONYS_TERMINALS_ELEVATOR_H

#include "anonys/Timer.h"

namespace ctrl::reg {
    class FloorTracker;
}
namespace dev {
    class SpeedRegulator;
}

namespace anonys_0 {
    struct Terminals {
        anonys::TimerCore* pTimer;
        ctrl::reg::FloorTracker* pFloorTracker;
        dev::SpeedRegulator* pSpeedRegulator;
    };
}

#endif // EXAMPLE2_ANONYS_TERMINALS_ELEVATOR_H
