#pragma once

namespace terminals {
	class LogService {
	public:
		virtual~ LogService() = default;

		virtual void write(const char* message) = 0;
	};
}