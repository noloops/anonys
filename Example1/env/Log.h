#pragma once

#include "Terminals/LogService.h"

namespace env {
	class Log : public terminals::LogService {
	public:
		Log(const char* pHeader) : m_pHeader{ pHeader } {}

		void write(const char* message);

	private:
		const char* m_pHeader;
	};
}
