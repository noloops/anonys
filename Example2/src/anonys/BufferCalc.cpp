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
#include "fsm/Elevator.h"
#include "fsm/TrafficLight.h"
#include "fsm/Washer.h"
#include "AnonysManualConfig.h"

namespace anonys
{
    BufferCalc calcBuffer() {
        BufferCalc result{true};

        {
            uint16_t maxBufferSize{0};
            calcMaxBuffer(fsm::Elevator::Idle, maxBufferSize);
            calcMaxBuffer(fsm::Elevator::FullSpeed, maxBufferSize);
            calcMaxBuffer(fsm::Elevator::Decelerating, maxBufferSize);
            calcMaxBuffer(fsm::Elevator::GoingDown, maxBufferSize);
            calcMaxBuffer(fsm::Elevator::Stopped, maxBufferSize);
            result.sizeElevator = maxBufferSize;
            if (maxBufferSize > BufferSize::Elevator) {
                result.ok = false;
            }
        }

        {
            uint16_t maxBufferSize{0};
            calcMaxBuffer(fsm::TrafficLight::Off, maxBufferSize);
            calcMaxBuffer(fsm::TrafficLight::Green, maxBufferSize);
            calcMaxBuffer(fsm::TrafficLight::Yellow, maxBufferSize);
            calcMaxBuffer(fsm::TrafficLight::Red, maxBufferSize);
            calcMaxBuffer(fsm::TrafficLight::Flashing, maxBufferSize);
            result.sizeTrafficLight = maxBufferSize;
            if (maxBufferSize > BufferSize::TrafficLight) {
                result.ok = false;
            }
        }

        {
            uint16_t maxBufferSize{0};
            calcMaxBuffer(fsm::Washer::Idle, maxBufferSize);
            calcMaxBuffer(fsm::Washer::Filling, maxBufferSize);
            calcMaxBuffer(fsm::Washer::Agitating, maxBufferSize);
            calcMaxBuffer(fsm::Washer::Soaking, maxBufferSize);
            calcMaxBuffer(fsm::Washer::Draining, maxBufferSize);
            calcMaxBuffer(fsm::Washer::Done, maxBufferSize);
            calcMaxBuffer(fsm::Washer::Error, maxBufferSize);
            calcMaxBuffer(fsm::Washer::Halted, maxBufferSize);
            result.sizeWasher = maxBufferSize;
            if (maxBufferSize > BufferSize::Washer) {
                result.ok = false;
            }
        }

        return result;
    }
}
