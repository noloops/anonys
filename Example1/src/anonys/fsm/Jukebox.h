// Generated file, do not edit!
#ifndef EXAMPLE1_FSM_JUKEBOX_H
#define EXAMPLE1_FSM_JUKEBOX_H

#include "anonys/impl/handlersJukebox.h"
#include "anonys/EventId.h"
#include "anonys/FsmId.h"

namespace anonys::fsm {
	struct Jukebox {
		static constexpr anonys::FsmId Id{ anonys::FsmId::Jukebox };
		static constexpr anonys::StateDef Off = { 1, anonys::FsmId::Jukebox, nullptr, anonys_0_1::getMembersSize, anonys_0_1::liveCycle, anonys_0_1::handleEvent };
		static constexpr anonys::StateDef Idle = { 2, anonys::FsmId::Jukebox, nullptr, anonys_0_2::getMembersSize, anonys_0_2::liveCycle, anonys_0_2::handleEvent };
		static constexpr anonys::StateDef Playing = { 3, anonys::FsmId::Jukebox, nullptr, anonys_0_3::getMembersSize, anonys_0_3::liveCycle, anonys_0_3::handleEvent };
		static constexpr anonys::StateDef Normal = { 4, anonys::FsmId::Jukebox, &Playing, anonys_0_4::getMembersSize, anonys_0_4::liveCycle, anonys_0_4::handleEvent };
		static constexpr anonys::StateDef Paused = { 5, anonys::FsmId::Jukebox, &Playing, anonys_0_5::getMembersSize, anonys_0_5::liveCycle, anonys_0_5::handleEvent };
		static constexpr anonys::StateDef Error = { 6, anonys::FsmId::Jukebox, nullptr, anonys_0_6::getMembersSize, anonys_0_6::liveCycle, anonys_0_6::handleEvent };
	};
}

#endif // EXAMPLE1_FSM_JUKEBOX_H
