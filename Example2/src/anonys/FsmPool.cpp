// ANONYS - Generated file, do not edit!
#include "FsmPool.h"
#include "anonys/Utils.h"

#include "fsm/Elevator.h"
#include "fsm/TrafficLight.h"
#include "fsm/Washer.h"

namespace anonys
{
    static_assert(BufferSize::Elevator % anonys::StdAlign == 0, "Buffer size must be a multiple of alignment");
    static_assert(BufferSize::TrafficLight % anonys::StdAlign == 0, "Buffer size must be a multiple of alignment");
    static_assert(BufferSize::Washer % anonys::StdAlign == 0, "Buffer size must be a multiple of alignment");

    void FsmPool::handleEvent(FsmId fsmId, Event& event) {
        if (static_cast<uint16_t>(fsmId) < FsmCount) {
            m_fsm[static_cast<uint16_t>(fsmId)].handleEvent(event);
        }
    }

    void FsmPool::handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId) {
        if (static_cast<uint16_t>(fsmId) < FsmCount) {
            m_fsm[static_cast<uint16_t>(fsmId)].handleTimeoutEvent(depth, eventId);
        }
    }

    void FsmPool::setTracingService(TracingService* pTracingService) {
        for (uint16_t fsmId{0}; fsmId < FsmCount; ++fsmId) {
            m_fsm[fsmId].setTracingService(pTracingService);
        }
    }

    void FsmPool::setTracingService(FsmId fsmId, TracingService* pTracingService) {
        if (static_cast<uint16_t>(fsmId) < FsmCount) {
            m_fsm[static_cast<uint16_t>(fsmId)].setTracingService(pTracingService);
        }
    }

    void FsmPool::initializeElevator(TimerService& timerService) {
        ANONYS_ASSERT(m_terminalsElevator.pTimer == nullptr);
        FsmCore& fsm{ m_fsm[static_cast<uint16_t>(FsmId::Elevator)] };
        m_terminalsElevator.pTimer = &(fsm.getTimerCore());

        uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferElevator)) };
        fsm.initialize(FsmId::Elevator, &m_terminalsElevator, pBuffer, sizeof(m_bufferElevator), &timerService);
    }

    void FsmPool::initializeTrafficLight(TimerService& timerService, Display& display) {
        ANONYS_ASSERT(m_terminalsTrafficLight.pTimer == nullptr);
        FsmCore& fsm{ m_fsm[static_cast<uint16_t>(FsmId::TrafficLight)] };
        m_terminalsTrafficLight.pTimer = &(fsm.getTimerCore());
        m_terminalsTrafficLight.pDisplay = &display;

        uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferTrafficLight)) };
        fsm.initialize(FsmId::TrafficLight, &m_terminalsTrafficLight, pBuffer, sizeof(m_bufferTrafficLight), &timerService);
    }

    void FsmPool::initializeWasher(TimerService& timerService, hw::Motor& motor, hw::io::Valve& valve) {
        ANONYS_ASSERT(m_terminalsWasher.pTimer == nullptr);
        FsmCore& fsm{ m_fsm[static_cast<uint16_t>(FsmId::Washer)] };
        m_terminalsWasher.pTimer = &(fsm.getTimerCore());
        m_terminalsWasher.pMotor = &motor;
        m_terminalsWasher.pValve = &valve;

        uint8_t* const pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&m_bufferWasher)) };
        fsm.initialize(FsmId::Washer, &m_terminalsWasher, pBuffer, sizeof(m_bufferWasher), &timerService);
    }

    void FsmPool::start() {
        ANONYS_ASSERT(!m_started);
        m_started = true;
        m_fsm[static_cast<uint16_t>(FsmId::Elevator)].executeTransition(&fsm::Elevator::Idle);
        m_fsm[static_cast<uint16_t>(FsmId::TrafficLight)].executeTransition(&fsm::TrafficLight::Off);
        m_fsm[static_cast<uint16_t>(FsmId::Washer)].executeTransition(&fsm::Washer::Idle);
    }
}
