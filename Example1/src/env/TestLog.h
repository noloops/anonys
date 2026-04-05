#pragma once

#include "Terminals/LogService.h"

namespace env {
	class TestLog : public terminals::LogService {
	public:
		TestLog(const char* pHeader) : m_pHeader{ pHeader } {}

		void write(terminals::Message message) override;
		void write(terminals::Message message, int32_t value) override;

	private:
		const char* m_pHeader;
	};
}
