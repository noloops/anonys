#include "env/Tester.h"
#include "env/Demo.h"

int main()
{
	bool ok = env::Tester::runAllTests();
	if (ok) {
		env::Demo::run();
	}
	return ok ? 0 : 1;
}
