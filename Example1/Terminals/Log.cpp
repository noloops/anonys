#include "Log.h"
#include <iostream>

namespace terminals {
	void Log::write(const char* pMessage) {
		std::cout << m_pHeader << " " << pMessage << std::endl;
	}
}