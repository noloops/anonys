#pragma once

namespace terminals {

	class TimerMngr {
	private:
		int m_dummies[7]{};
	};

	class Timer {
	public:
		Timer(TimerMngr& mngr) : m_mngr{ mngr } {}
		~Timer() {}

	private:
		TimerMngr& m_mngr;
		int m_dummies[3]{};
	};
}
