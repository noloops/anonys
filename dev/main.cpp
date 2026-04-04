#include <iostream>
#include <type_traits>
#include "anonys/FsmPool.h"
#include "Terminals/Terminals.h"

namespace {
	class DummyTimerService : public anonys::TimerService {
	public:
		void startTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) final {
		}
		void stopTimers(anonys::FsmId fsmId, int16_t depth) final {
		}
	};

	class DummyTracingService : public anonys::TracingService {
	public:
		void traceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) final {
		}
		void traceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) final {
		}
		void traceEnterState(anonys::FsmId fsmId, uint16_t stateId) final {
		}
		void traceExitState(anonys::FsmId fsmId, uint16_t stateId) final {
		}
	};
}

int main()
{
	static terminals::EventSender eventSender{};
	static terminals::Log log{"A:"};
	static terminals::Std stdTerminal{ eventSender, log };
	static DummyTimerService timerService{};
	static DummyTracingService tracingService{};

	static anonys::FsmPool fsm{};
	fsm.initializeA(timerService, stdTerminal);
	fsm.setTracingService(anonys::FsmId::A, &tracingService);
	fsm.start();

    std::cout << "Hello World!\n";
}
