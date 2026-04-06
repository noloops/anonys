#include "env/Tester.h"
#include "env/Demo.h"

int main()
{
	if (env::Tester::runAllTests()) {
		env::Demo::run();
	}
	return 0;
}
