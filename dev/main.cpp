#include <iostream>
#include <type_traits>
#include "env/DummyTimerService.h"
#include "env/DummyTracingService.h"
#include "env/Log.h"
#include "Terminals/Terminals.h"
#include "anonys/FsmPool.h"

int main()
{
	static terminals::EventSender eventSender{};
	static env::Log log{"A:"};
	static terminals::Std stdTerminal{ eventSender, log };
	static env::DummyTimerService timerService{};
	static env::DummyTracingService tracingService{};

	static anonys::FsmPool fsm{};
	fsm.initializeA(timerService, stdTerminal);
	fsm.setTracingService(anonys::FsmId::A, &tracingService);
	fsm.start();

    std::cout << "Hello World!\n";
}
