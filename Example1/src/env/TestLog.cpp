#include "TestLog.h"
#include "Expected.h"
#include "Helper.h"
#include <iostream>

namespace env {
	void TestLog::write(terminals::Message message) {
		Expected::checkLogWrite(message);
		std::cout << m_pHeader << " " << Helper::getLogMessage(message) << std::endl;
	}

	void TestLog::write(terminals::Message message, int32_t value) {
		Expected::checkLogWrite(message, value);
		std::cout << m_pHeader << " " << Helper::getLogMessage(message) << " (" << value << ")" << std::endl;
	}
}
