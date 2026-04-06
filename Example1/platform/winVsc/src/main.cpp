#include "env/Tester.h"
#include "env/Demo.h"

int main()
{
	if (!env::Tester::runAllTests()) {
		return 1;
	}
	env::Demo::run();
	return 0;
}
