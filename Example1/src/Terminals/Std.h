#pragma once

#include "LogService.h"
#include "EventSender.h"

namespace terminals {
	struct Std {
		EventSender& sender;
		LogService& log;
	};
}
