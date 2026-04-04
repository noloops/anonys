// Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_EVENTID_H
#define EXAMPLE1_ANONYS_EVENTID_H

#include "anonys/Types.h"

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
	class Timeout1 {};
	class Timeout2 {};
	class Timeout3 {};

	template <typename T> constexpr EventId getEventId() = delete;
	template <>	constexpr EventId getEventId<events::Event0>() { return 0; }
	template <>	constexpr EventId getEventId<events::Event1>() { return 1; }
	template <>	constexpr EventId getEventId<events::Event2>() { return 2; }
	template <>	constexpr EventId getEventId<events::Event3>() { return 3; }
	template <>	constexpr EventId getEventId<events::Event4>() { return 4; }
	template <>	constexpr EventId getEventId<events::Event5>() { return 5; }
	template <>	constexpr EventId getEventId<events::Event6>() { return 6; }
	template <>	constexpr EventId getEventId<events::Event7>() { return 7; }
	template <>	constexpr EventId getEventId<events::Event8>() { return 8; }

	template <typename T> constexpr EventId getTimeoutEventId() = delete;
	template <>	constexpr EventId getTimeoutEventId<Timeout1>() { return 60001; }
	template <>	constexpr EventId getTimeoutEventId<Timeout2>() { return 60002; }
	template <>	constexpr EventId getTimeoutEventId<Timeout3>() { return 60003; }
	static_assert(getTimeoutEventId<Timeout1>().id == MinTimoutEventId.id);
}

#endif // EXAMPLE1_ANONYS_EVENTID_H
