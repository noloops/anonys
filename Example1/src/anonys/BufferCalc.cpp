// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#include "BufferCalc.h"
#include "anonys/calcMaxBuffer.h"
#include "fsm/LedJuggler.h"
#include "fsm/Debouncer.h"
#include "AnonysManualConfig.h"

namespace anonys
{
    BufferCalc calcBuffer() {
        BufferCalc result{true};
        {
            uint16_t maxBufferSize{0};
            calcMaxBuffer(fsm::LedJuggler::BlinkA, maxBufferSize);
            calcMaxBuffer(fsm::LedJuggler::OnA, maxBufferSize);
            calcMaxBuffer(fsm::LedJuggler::OffA, maxBufferSize);
            calcMaxBuffer(fsm::LedJuggler::BlinkB, maxBufferSize);
            calcMaxBuffer(fsm::LedJuggler::OnB, maxBufferSize);
            calcMaxBuffer(fsm::LedJuggler::OffB, maxBufferSize);
            calcMaxBuffer(fsm::LedJuggler::Paused, maxBufferSize);
            result.sizeLedJuggler = maxBufferSize;
            if (maxBufferSize > BufferSize::LedJuggler) {
                result.ok = false;
            }
        }
        {
            uint16_t maxBufferSize{0};
            calcMaxBuffer(fsm::Debouncer::Initial, maxBufferSize);
            calcMaxBuffer(fsm::Debouncer::Pressed, maxBufferSize);
            calcMaxBuffer(fsm::Debouncer::Released, maxBufferSize);
            result.sizeDebouncer = maxBufferSize;
            if (maxBufferSize > BufferSize::Debouncer) {
                result.ok = false;
            }
        }
        return result;
    }
}
