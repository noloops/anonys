#ifndef EXAMPLE1_ANONYSEVENTID_H
#define EXAMPLE1_ANONYSEVENTID_H

// Generated file, do not edit!

#include <cstdint>

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
	using EventId = uint16_t;

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
}

#endif // EXAMPLE1_ANONYSEVENTID_H
