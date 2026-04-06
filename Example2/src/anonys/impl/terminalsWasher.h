// Generated file, do not edit!
#ifndef EXAMPLE2_ANONYS_TERMINALS_WASHER_H
#define EXAMPLE2_ANONYS_TERMINALS_WASHER_H

#include "anonys/Timer.h"

namespace hw {
    struct Motor;
}
namespace hw::io {
    struct Valve;
}
namespace dev::sensor {
    struct WaterLevel;
}

namespace anonys_2 {
    struct Terminals {
        anonys::TimerCore* pTimer;
        hw::Motor* pMotor;
        hw::io::Valve* pValve;
        dev::sensor::WaterLevel* pWaterLevel;
    };
}

#endif // EXAMPLE2_ANONYS_TERMINALS_WASHER_H
