#include <iostream>
#include <type_traits>
#include "env/TestTimerService.h"
#include "env/TestTracingService.h"
#include "env/TestEventSenderService.h"
#include "env/TestLog.h"
#include "Terminals/Terminals.h"
#include "anonys/FsmPool.h"

int main()
{
	static env::TestEventSenderService eventSender{};
	static env::TestLog log{"A:"};
	static terminals::Std stdTerminal{ eventSender, log };
	static env::TestTimerService timerService{};
	static env::TestTracingService tracingService{};

	static anonys::FsmPool fsm{};
	fsm.initializeA(timerService, stdTerminal);
	fsm.setTracingService(anonys::FsmId::A, &tracingService);
	fsm.start();

    std::cout << "Hello World!\n";
}
