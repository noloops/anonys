#include "anonys/FsmPool.h"
#include "anonys/BufferCalc.h"
#include "Terminals.h"
#include <iostream>

namespace {
    class DummyTimerService : public anonys::TimerService {
    public:
        void startTimer(anonys::FsmId, int16_t, anonys::EventId, uint32_t) override {}
        void stopTimers(anonys::FsmId, int16_t) override {}
    };
}

int main()
{
    auto const bufferCalcResult{anonys::calcBuffer()};
    std::cout << "BufferCalc: ok=" << bufferCalcResult.ok
              << " sizeSemiFab=" << bufferCalcResult.sizeSemiFab << std::endl;
    if (!bufferCalcResult.ok) {
        return 2;
    }
    DummyTimerService timerService;
    term::io::Std std;
    anonys::FsmPool fsm;
    fsm.initializeSemiFab(timerService, std);
    fsm.start();
    return 0;
}
