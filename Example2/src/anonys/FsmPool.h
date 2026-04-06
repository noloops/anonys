// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE2_FSM_H
#define EXAMPLE2_FSM_H

#include <type_traits>

#include "anonys/FsmCore.h"

#include "impl/terminalsElevator.h"
#include "impl/terminalsTrafficLight.h"
#include "impl/terminalsWasher.h"

namespace anonys
{
    class FsmPool {
    public:
        static constexpr uint16_t Count{ static_cast<uint16_t>(FsmId::Count_)};
        using TerminalsElevator = anonys_0::Terminals;
        using TerminalsTrafficLight = anonys_1::Terminals;
        using TerminalsWasher = anonys_2::Terminals;

        void handleEvent(FsmId fsmId, Event& event);

        void handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId);

        void setTracingService(TracingService* pTracingService = nullptr);

        void setTracingService(FsmId fsmId, TracingService* pTracingService = nullptr);

        void initializeElevator(TimerService& timerService);

        void initializeTrafficLight(TimerService& timerService, Display& display);

        void initializeWasher(TimerService& timerService, hw::Motor& motor, hw::io::Valve& valve);

        void start();

    private:
        FsmCore m_fsm[Count]{};

        std::aligned_storage_t<BufferSize::Elevator, anonys::StdAlign> m_bufferElevator{};
        std::aligned_storage_t<BufferSize::TrafficLight, anonys::StdAlign> m_bufferTrafficLight{};
        std::aligned_storage_t<BufferSize::Washer, anonys::StdAlign> m_bufferWasher{};

        TerminalsElevator m_terminalsElevator{};
        TerminalsTrafficLight m_terminalsTrafficLight{};
        TerminalsWasher m_terminalsWasher{};

        bool m_started{ false };
    };
}
#endif // EXAMPLE2_FSM_H
