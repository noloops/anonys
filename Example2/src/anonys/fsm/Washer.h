// Generated file, do not edit!
#ifndef EXAMPLE2_FSM_WASHER_H
#define EXAMPLE2_FSM_WASHER_H

#include "anonys/impl/handlersWasher.h"
#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys::fsm {
	struct Washer {
		static constexpr anonys::FsmId Id{ anonys::FsmId::Washer };
		static constexpr anonys::StateDef Idle = { 1, anonys::FsmId::Washer, nullptr, anonys_2_1::getMembersSize, anonys_2_1::liveCycle, anonys_2_1::handleEvent };
		static constexpr anonys::StateDef Running = { 2, anonys::FsmId::Washer, nullptr, anonys_2_2::getMembersSize, anonys_2_2::liveCycle, anonys_2_2::handleEvent };
		static constexpr anonys::StateDef Filling = { 3, anonys::FsmId::Washer, &Running, anonys_2_3::getMembersSize, anonys_2_3::liveCycle, anonys_2_3::handleEvent };
		static constexpr anonys::StateDef Washing = { 4, anonys::FsmId::Washer, &Running, anonys_2_4::getMembersSize, anonys_2_4::liveCycle, anonys_2_4::handleEvent };
		static constexpr anonys::StateDef Agitating = { 5, anonys::FsmId::Washer, &Washing, anonys_2_5::getMembersSize, anonys_2_5::liveCycle, anonys_2_5::handleEvent };
		static constexpr anonys::StateDef Soaking = { 6, anonys::FsmId::Washer, &Washing, anonys_2_6::getMembersSize, anonys_2_6::liveCycle, anonys_2_6::handleEvent };
		static constexpr anonys::StateDef Draining = { 7, anonys::FsmId::Washer, &Running, anonys_2_7::getMembersSize, anonys_2_7::liveCycle, anonys_2_7::handleEvent };
		static constexpr anonys::StateDef Done = { 8, anonys::FsmId::Washer, nullptr, anonys_2_8::getMembersSize, anonys_2_8::liveCycle, anonys_2_8::handleEvent };
		static constexpr anonys::StateDef Error = { 9, anonys::FsmId::Washer, nullptr, anonys_2_9::getMembersSize, anonys_2_9::liveCycle, anonys_2_9::handleEvent };
	};
}

#endif // EXAMPLE2_FSM_WASHER_H
