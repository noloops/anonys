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
