// Generated file, do not edit!
#ifndef EXAMPLE2_ANONYS_EVENTID_H
#define EXAMPLE2_ANONYS_EVENTID_H

#include "anonys/Types.h"

struct Start;
namespace signals {
    struct Stop;
}
namespace signals::alert {
    struct Emergency;
}
namespace ctrl {
    class Proceed;
}
namespace ctrl::cmd {
    struct Reset;
}
namespace io {
    struct SensorTriggered;
}
namespace io::data {
    struct Tick;
}

namespace anonys
{
    class Timeout1 {};
    class Timeout2 {};
    class Timeout3 {};
    class Timeout4 {};

    template <typename T> constexpr EventId getEventId() = delete;
    template<> constexpr EventId getEventId<Start>() { return 0; }
    template<> constexpr EventId getEventId<signals::Stop>() { return 1; }
    template<> constexpr EventId getEventId<signals::alert::Emergency>() { return 2; }
    template<> constexpr EventId getEventId<ctrl::Proceed>() { return 3; }
    template<> constexpr EventId getEventId<ctrl::cmd::Reset>() { return 4; }
    template<> constexpr EventId getEventId<io::SensorTriggered>() { return 5; }
    template<> constexpr EventId getEventId<io::data::Tick>() { return 6; }

    template <typename T> constexpr EventId getTimeoutEventId() = delete;
    template<> constexpr EventId getTimeoutEventId<Timeout1>() { return 60001; }
    template<> constexpr EventId getTimeoutEventId<Timeout2>() { return 60002; }
    template<> constexpr EventId getTimeoutEventId<Timeout3>() { return 60003; }
    template<> constexpr EventId getTimeoutEventId<Timeout4>() { return 60004; }
    static_assert(getTimeoutEventId<Timeout1>().id == MinTimoutEventId.id);
}

#endif // EXAMPLE2_ANONYS_EVENTID_H
