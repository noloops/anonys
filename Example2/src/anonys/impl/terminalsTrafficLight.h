// Generated file, do not edit!
#ifndef EXAMPLE2_ANONYS_TERMINALS_TRAFFICLIGHT_H
#define EXAMPLE2_ANONYS_TERMINALS_TRAFFICLIGHT_H

#include "anonys/Timer.h"

struct Display;
namespace ctrl {
    class Panel;
}

namespace anonys_1 {
    struct Terminals {
        anonys::TimerCore* pTimer;
        Display* pDisplay;
        ctrl::Panel* pPanel;
    };
}

#endif // EXAMPLE2_ANONYS_TERMINALS_TRAFFICLIGHT_H
