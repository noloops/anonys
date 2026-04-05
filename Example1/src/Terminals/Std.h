#pragma once

#include "LogService.h"
#include "EventSenderService.h"

namespace terminals {
	struct Std {
		EventSenderService& sender;
		LogService& log;
	};
}
