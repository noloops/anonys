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
#include "fsm/Jukebox.h"
#include "AnonysManualConfig.h"

namespace anonys
{
    BufferCalc calcBuffer() {
        BufferCalc result{true};
        {
            uint16_t maxBufferSize{0};
            calcMaxBuffer(fsm::Jukebox::Off, maxBufferSize);
            calcMaxBuffer(fsm::Jukebox::Idle, maxBufferSize);
            calcMaxBuffer(fsm::Jukebox::Normal, maxBufferSize);
            calcMaxBuffer(fsm::Jukebox::AutoPause, maxBufferSize);
            calcMaxBuffer(fsm::Jukebox::Error, maxBufferSize);
            result.sizeJukebox = maxBufferSize;
            if (maxBufferSize > BufferSize::Jukebox) {
                result.ok = false;
            }
        }
        return result;
    }
}
