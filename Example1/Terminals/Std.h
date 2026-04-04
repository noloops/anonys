#pragma once

#include "Log.h"
#include "EventSender.h"

namespace terminals {
	struct Std {
		EventSender& sender;
		Log& log;
	};
}
