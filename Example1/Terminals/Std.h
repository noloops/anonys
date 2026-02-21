#pragma once

#include "Log.h"
#include "Timers.h"
#include "EventSender.h"

namespace terminals {
	struct Std {
		EventSender& sender;
		TimerMngr& timerMngr;
		Log& log;
	};
}
