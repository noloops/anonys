// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_TERMINALS_JUKEBOX_H
#define EXAMPLE1_ANONYS_TERMINALS_JUKEBOX_H

#include "anonys/Timer.h"

namespace terminals {
    struct Std;
    class Counter;
    class Mixer;
    class Countdown;
}

namespace anonys_0 {
    struct Terminals {
        anonys::TimerCore* pTimer;
        terminals::Std* pStd;
        terminals::Counter* pCounter;
        terminals::Mixer* pMixer;
        terminals::Countdown* pCountdown;
    };
}

#endif // EXAMPLE1_ANONYS_TERMINALS_JUKEBOX_H
