#include "Demo.h"
#include "Expected.h"
#include "Setup.h"
#include "Executor.h"
#include "Events/Events.h"
#include <iostream>
#include <string>

namespace env {
	void Demo::printHelp() {
		std::cout << "Commands:" << std::endl;
		std::cout << "  on        send PowerOn" << std::endl;
		std::cout << "  off       send PowerOff" << std::endl;
		std::cout << "  coin      send InsertCoin" << std::endl;
		std::cout << "  play      send Play" << std::endl;
		std::cout << "  pause     send Pause" << std::endl;
		std::cout << "  skip      send Skip" << std::endl;
		std::cout << "  eject     send Eject" << std::endl;
		std::cout << "  diag      send Diagnostic" << std::endl;
		std::cout << "  mal       send Malfunction" << std::endl;
		std::cout << "  reset     send Reset" << std::endl;
		std::cout << "  auto      send AutoPause" << std::endl;
		std::cout << "  conf N    send ConfigureAutoPause(N)" << std::endl;
		std::cout << "  e         send next queued event" << std::endl;
		std::cout << "  t         send next timeout" << std::endl;
		std::cout << "  ?         print this help" << std::endl;
		std::cout << "  q         quit" << std::endl;
	}

	void Demo::run() {
		Expected::enable(false);
		Setup setup;
		Executor executor{setup.fsm, setup.eventSender, setup.timerService};

		constexpr auto F = anonys::FsmId::Jukebox;

		setup.fsm.start();
        std::cout  << std::endl << "RUNNING DEMO" << std::endl;
		printHelp();

		std::string line;
		while (std::cout << "> " && std::getline(std::cin, line)) {
			if (line == "q") {
				break;
			}
			else if (line == "?") {
				printHelp();
			}
			else if (line == "on") {
				executor.send<events::PowerOn>(F, events::PowerOn{});
			}
			else if (line == "off") {
				executor.send<events::PowerOff>(F, events::PowerOff{});
			}
			else if (line == "coin") {
				executor.send<events::InsertCoin>(F, events::InsertCoin{});
			}
			else if (line == "play") {
				executor.send<events::Play>(F, events::Play{});
			}
			else if (line == "pause") {
				executor.send<events::Pause>(F, events::Pause{});
			}
			else if (line == "skip") {
				executor.send<events::Skip>(F, events::Skip{});
			}
			else if (line == "eject") {
				executor.send<events::Eject>(F, events::Eject{});
			}
			else if (line == "diag") {
				executor.send<events::Diagnostic>(F, events::Diagnostic{});
			}
			else if (line == "mal") {
				executor.send<events::Malfunction>(F, events::Malfunction{});
			}
			else if (line == "reset") {
				executor.send<events::Reset>(F, events::Reset{});
			}
			else if (line == "auto") {
				executor.send<events::AutoPause>(F, events::AutoPause{});
			}
			else if (line.rfind("conf ", 0) == 0) {
				int32_t n{std::stoi(line.substr(5))};
				executor.send<events::ConfigureAutoPause>(F, events::ConfigureAutoPause{n});
			}
			else if (line == "e") {
				executor.sendNextEvent();
			}
			else if (line == "t") {
				executor.sendNextTimeout();
			}
		}
	}
}
