// ANONYS
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

#include "TestEventSenderService.h"
#include "TestLog.h"
#include "TestTimerService.h"
#include "TestTracingService.h"
#include "Terminals/Terminals.h"
#include "anonys/FsmPool.h"

namespace env {
	struct Setup {
		TestEventSenderService eventSender;
		TestLog log{"Jukebox:"};
		terminals::Std stdTerminal{eventSender, log};
		TestTimerService timerService;
		TestTracingService tracingService;
		anonys::FsmPool fsm;

		Setup() {
			fsm.initializeJukebox(timerService, stdTerminal);
			fsm.setTracingService(anonys::FsmId::Jukebox, &tracingService);
		}
	};
}
