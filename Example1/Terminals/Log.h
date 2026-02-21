#pragma once

namespace terminals {
	class Log {
	public:
		Log(const char* pHeader) : m_pHeader{ pHeader } {}

		void write(const char* message);

	private:
		const char* m_pHeader;
	};
}