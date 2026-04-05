#include "env/Tester.h"

int main()
{
	bool ok{true};
	if (!env::Tester::testStartAndPowerCycle()) ok = false;
	if (!env::Tester::testSelfTransitions()) ok = false;
	if (!env::Tester::testPlayPauseCycle()) ok = false;
	if (!env::Tester::testEventBubbling()) ok = false;
	if (!env::Tester::testTrackEndTimeout()) ok = false;
	if (!env::Tester::testSleepTimeout()) ok = false;
	if (!env::Tester::testErrorAndRecovery()) ok = false;
	if (!env::Tester::testUnhandledEvent()) ok = false;
	return ok ? 0 : 1;
}
