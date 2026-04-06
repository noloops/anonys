// ANONYS
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "anonys/FsmPool.h"
#include "Terminals.h"

namespace {
	class DummyTimerService : public anonys::TimerService {
	public:
		void startTimer(anonys::FsmId, int16_t, anonys::EventId, uint32_t) override {}
		void stopTimers(anonys::FsmId, int16_t) override {}
	};
}

int main()
{
	DummyTimerService timerService;
	Display display;
	hw::Motor motor;
	hw::io::Valve valve;

	anonys::FsmPool fsm;
	fsm.initializeElevator(timerService);
	fsm.initializeTrafficLight(timerService, display);
	fsm.initializeWasher(timerService, motor, valve);
	fsm.start();

	return 0;
}
