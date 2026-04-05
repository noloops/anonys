#pragma once

#include <cstdint>

namespace terminals {
	enum class Message : int32_t {
		EnterSt1 = 0,
		ExitSt1,
		Event1InSt1,
		Event4InSt1,
		Event5InSt1,
		UserTimeoutInSt1,
		EnterSt2,
		ExitSt2,
		Event2InSt2,
		Event7InSt2,
		Event8InSt2,
		TimeoutAInSt2,
		TimeoutBInSt2,
		TimeoutCInSt2,
		EnterSt1a,
		ExitSt1a,
		Event0InSt1a,
		Event3InSt1a,
		Event5InSt1a,
		UserTimeoutInSt1a,
		SystemTimeoutInSt1a,
	};

	class LogService {
	public:
		virtual ~LogService() = default;

		virtual void write(Message message) = 0;
		virtual void write(Message message, int32_t value) = 0;

		static const char* resolve(Message message);
	};
}