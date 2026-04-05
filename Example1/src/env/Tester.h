#pragma once

namespace env {
	class Tester {
	public:
		static bool test1();

	private:
		static bool failed();
		static bool success();
	};
}
