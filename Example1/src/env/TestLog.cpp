#include "TestLog.h"
#include <iostream>

namespace env {
	void TestLog::write(terminals::Message message) {
		std::cout << m_pHeader << " " << terminals::LogService::resolve(message) << std::endl;
	}

	void TestLog::write(terminals::Message message, int32_t value) {
		std::cout << m_pHeader << " " << terminals::LogService::resolve(message) << " " << value << std::endl;
	}
}
