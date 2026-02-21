#include "States/AStates.h"
#include "Terminals/Terminals.h"

namespace {
	struct Me {
		terminals::Std& std;
		terminals::T1 t1{};
		terminals::Timer timer{ std.timerMngr };
	};

	void enter(Me& me) {
		me.std.log.write("Enter St1");
	}

	void exit(Me& me) {
		me.std.log.write("Exit St1");
	}
}

#include "St1.h"
