#include "Helper.h"

namespace env {
	const char* Helper::getFsmName(anonys::FsmId fsmId) {
		switch (fsmId) {
		case anonys::FsmId::A: return "A";
		default: return "?";
		}
	}

	const char* Helper::getStateName(anonys::FsmId fsmId, uint16_t stateId) {
		switch (fsmId) {
		case anonys::FsmId::A:
			switch (stateId) {
			case 1: return "St1";
			case 2: return "St1a";
			case 3: return "St2";
			default: return "?";
			}
		default: return "?";
		}
	}
}
