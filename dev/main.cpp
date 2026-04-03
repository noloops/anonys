#include <iostream>
#include <type_traits>
#include "anonys/Fsm.h"
#include "Terminals/Terminals.h"

int main()
{
	static terminals::EventSender eventSender{};
	static terminals::TimerMngr timerMngr{};
	static terminals::Log log{"A:"};
	static terminals::Std stdTerminal{ eventSender, timerMngr, log };

	static anonys::Fsm fsm{};
	fsm.initializeA(stdTerminal);
	fsm.start();

    std::cout << "Hello World!\n";
}
