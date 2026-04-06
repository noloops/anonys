// Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_EVENTID_H
#define EXAMPLE1_ANONYS_EVENTID_H

#include "anonys/Types.h"

namespace events {
    struct PowerOn;
    struct PowerOff;
    struct InsertCoin;
    struct Play;
    struct Pause;
    struct Skip;
    struct Eject;
    struct Diagnostic;
    struct Malfunction;
    struct Reset;
    struct AutoPause;
    class ConfigureAutoPause;
}

namespace anonys
{
    class Timeout1 {};
    class Timeout2 {};
    class Timeout3 {};
    class Timeout4 {};

    template <typename T> constexpr EventId getEventId() = delete;
    template <>    constexpr EventId getEventId<events::PowerOn>() { return 0; }
    template <>    constexpr EventId getEventId<events::PowerOff>() { return 1; }
    template <>    constexpr EventId getEventId<events::InsertCoin>() { return 2; }
    template <>    constexpr EventId getEventId<events::Play>() { return 3; }
    template <>    constexpr EventId getEventId<events::Pause>() { return 4; }
    template <>    constexpr EventId getEventId<events::Skip>() { return 5; }
    template <>    constexpr EventId getEventId<events::Eject>() { return 6; }
    template <>    constexpr EventId getEventId<events::Diagnostic>() { return 7; }
    template <>    constexpr EventId getEventId<events::Malfunction>() { return 8; }
    template <>    constexpr EventId getEventId<events::Reset>() { return 9; }
    template <>    constexpr EventId getEventId<events::AutoPause>() { return 10; }
    template <>    constexpr EventId getEventId<events::ConfigureAutoPause>() { return 11; }

    template <typename T> constexpr EventId getTimeoutEventId() = delete;
    template <>    constexpr EventId getTimeoutEventId<Timeout1>() { return 60001; }
    template <>    constexpr EventId getTimeoutEventId<Timeout2>() { return 60002; }
    template <>    constexpr EventId getTimeoutEventId<Timeout3>() { return 60003; }
    template <>    constexpr EventId getTimeoutEventId<Timeout4>() { return 60004; }
    static_assert(getTimeoutEventId<Timeout1>().id == MinTimoutEventId.id);
}

#endif // EXAMPLE1_ANONYS_EVENTID_H
