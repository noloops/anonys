// Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_EVENTID_H
#define EXAMPLE1_ANONYS_EVENTID_H

#include "anonys/Types.h"

// TODO add special timeout event id, e.g. 0xFFFF, and make sure it is handled correctly in FsmCore.cpp

namespace events {
	struct Event0;
	struct Event1;
	struct Event2;
	struct Event3;
	struct Event4;
	struct Event5;
	struct Event6;
	struct Event7;
	struct Event8;
}

namespace anonys
{
	template <>	constexpr EventId getEventId<events::Event0>() { return 0; }
	template <>	constexpr EventId getEventId<events::Event1>() { return 1; }
	template <>	constexpr EventId getEventId<events::Event2>() { return 2; }
	template <>	constexpr EventId getEventId<events::Event3>() { return 3; }
	template <>	constexpr EventId getEventId<events::Event4>() { return 4; }
	template <>	constexpr EventId getEventId<events::Event5>() { return 5; }
	template <>	constexpr EventId getEventId<events::Event6>() { return 6; }
	template <>	constexpr EventId getEventId<events::Event7>() { return 7; }
	template <>	constexpr EventId getEventId<events::Event8>() { return 8; }
}

#endif // EXAMPLE1_ANONYS_EVENTID_H
