// Generated file, do not edit!
#ifndef EXAMPLE2_ANONYS_TERMINALS_ELEVATOR_H
#define EXAMPLE2_ANONYS_TERMINALS_ELEVATOR_H

#include "anonys/Timer.h"

namespace ctrl::reg { class FloorTracker; }
namespace dev { class SpeedRegulator; }

namespace anonys_0 {
	struct Terminals {
		anonys::TimerCore* pTimer;
		ctrl::reg::FloorTracker* pFloorTracker;
		dev::SpeedRegulator* pSpeedRegulator;
	};
}

#endif // EXAMPLE2_ANONYS_TERMINALS_ELEVATOR_H
