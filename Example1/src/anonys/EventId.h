// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_EVENTID_H
#define EXAMPLE1_ANONYS_EVENTID_H

#include "anonys/Types.h"

namespace events {
    struct Click;
    struct ButtonEvent;
}

namespace anonys
{
    class Timeout1 {};
    class Timeout2 {};

    template <typename T> constexpr EventId getEventId() = delete;
    template<> constexpr EventId getEventId<events::Click>() { return 0; }
    template<> constexpr EventId getEventId<events::ButtonEvent>() { return 1; }

    template <typename T> constexpr EventId getTimeoutEventId() = delete;
    template<> constexpr EventId getTimeoutEventId<Timeout1>() { return 60001; }
    template<> constexpr EventId getTimeoutEventId<Timeout2>() { return 60002; }
    static_assert(getTimeoutEventId<Timeout1>().id == MinTimoutEventId.id);
}

#endif // EXAMPLE1_ANONYS_EVENTID_H
