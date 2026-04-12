// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

#include <cstdint>
#include "anonys/Types.h"
#include "anonys/EventId.h"

namespace terminals {
    class EventSenderService {
    public:
        virtual ~EventSenderService() = default;

        template <typename T>
        void send(anonys::FsmId fsmId, const T& event) {
            constexpr anonys::EventId eventId{ anonys::getEventId<T>() };
            doSend(fsmId, eventId, &event, sizeof(T));
        }

    protected:
        virtual void doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) = 0;
    };
}
