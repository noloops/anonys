#ifndef EXAMPLE1_ANONYSEVENTID_H
#define EXAMPLE1_ANONYSEVENTID_H

#include <cstdint>

namespace anonys
{
	enum class EventId : uint16_t {
		Test1 = 0,
		Test2 = 1
	};
}

#endif // EXAMPLE1_ANONYSEVENTID_H
