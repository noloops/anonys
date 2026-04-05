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
		TestLog log{"A:"};
		terminals::Std stdTerminal{eventSender, log};
		TestTimerService timerService;
		TestTracingService tracingService;
		anonys::FsmPool fsm;

		Setup() {
			fsm.initializeA(timerService, stdTerminal);
			fsm.setTracingService(anonys::FsmId::A, &tracingService);
		}
	};
}
