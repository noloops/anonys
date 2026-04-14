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
    struct Click;
}

namespace anonys
{
    class Timeout1 {};

    template <typename T> constexpr EventId getEventId() = delete;
    template<> constexpr EventId getEventId<events::PowerOn>() { return 0; }
    template<> constexpr EventId getEventId<events::PowerOff>() { return 1; }
    template<> constexpr EventId getEventId<events::InsertCoin>() { return 2; }
    template<> constexpr EventId getEventId<events::Play>() { return 3; }
    template<> constexpr EventId getEventId<events::Pause>() { return 4; }
    template<> constexpr EventId getEventId<events::Skip>() { return 5; }
    template<> constexpr EventId getEventId<events::Eject>() { return 6; }
    template<> constexpr EventId getEventId<events::Diagnostic>() { return 7; }
    template<> constexpr EventId getEventId<events::Malfunction>() { return 8; }
    template<> constexpr EventId getEventId<events::Reset>() { return 9; }
    template<> constexpr EventId getEventId<events::AutoPause>() { return 10; }
    template<> constexpr EventId getEventId<events::ConfigureAutoPause>() { return 11; }
    template<> constexpr EventId getEventId<events::Click>() { return 12; }

    template <typename T> constexpr EventId getTimeoutEventId() = delete;
    template<> constexpr EventId getTimeoutEventId<Timeout1>() { return 60001; }
    static_assert(getTimeoutEventId<Timeout1>().id == MinTimoutEventId.id);
}

#endif // EXAMPLE1_ANONYS_EVENTID_H
