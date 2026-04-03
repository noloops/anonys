// Generated file, do not edit!
#ifndef EXAMPLE1_FSM_A_H
#define EXAMPLE1_FSM_A_H

#include "anonys/impl/handlersA.h"
#include "anonys/FsmId.h"

namespace anonys::fsm {
	struct A {
		static constexpr anonys::FsmId Id{ anonys::FsmId::A };
		static constexpr anonys::StateDef St1 = { 1, anonys::FsmId::A, nullptr, anonys_1_1::getMembersSize, anonys_1_1::liveCycle, anonys_1_1::handleEvent };
		static constexpr anonys::StateDef St1a = { 2, anonys::FsmId::A, &St1, anonys_1_2::getMembersSize, anonys_1_2::liveCycle, anonys_1_2::handleEvent };
		static constexpr anonys::StateDef St2 = { 3, anonys::FsmId::A, nullptr, anonys_1_3::getMembersSize, anonys_1_3::liveCycle, anonys_1_3::handleEvent };
	};
}

#endif // EXAMPLE1_FSM_A_H
