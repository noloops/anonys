#include "Log.h"
#include <iostream>

namespace env {
	void Log::write(const char* pMessage) {
		std::cout << m_pHeader << " " << pMessage << std::endl;
	}
}