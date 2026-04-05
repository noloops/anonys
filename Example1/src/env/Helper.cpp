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

	const char* Helper::getEventName(anonys::EventId eventId) {
		switch (eventId.id) {
		case 0: return "Event0";
		case 1: return "Event1";
		case 2: return "Event2";
		case 3: return "Event3";
		case 4: return "Event4";
		case 5: return "Event5";
		case 6: return "Event6";
		case 7: return "Event7";
		case 8: return "Event8";
		case 9: return "EventInt0";
		case 10: return "EventInt1";
		case 11: return "EventInt2";
		case 60001: return "Timeout1";
		case 60002: return "Timeout2";
		case 60003: return "Timeout3";
		default: return "?";
		}
	}

	const char* Helper::getLogMessage(terminals::Message message) {
		switch (message) {
		case terminals::Message::EnterSt1:             return "Enter St1";
		case terminals::Message::ExitSt1:              return "Exit St1";
		case terminals::Message::Event1InSt1:          return "Handle Event1 in St1";
		case terminals::Message::Event4InSt1:          return "Handle Event4 in St1";
		case terminals::Message::Event5InSt1:          return "Handle Event5 in St1";
		case terminals::Message::UserTimeoutInSt1:     return "Handle UserTimeout in St1";
		case terminals::Message::EnterSt2:             return "Enter St2";
		case terminals::Message::ExitSt2:              return "Exit St2";
		case terminals::Message::Event2InSt2:          return "Handle Event2 in St2";
		case terminals::Message::Event7InSt2:          return "Handle Event7 in St2";
		case terminals::Message::Event8InSt2:          return "Handle Event8 in St2";
		case terminals::Message::TimeoutAInSt2:        return "Handle TimeoutA in St2";
		case terminals::Message::TimeoutBInSt2:        return "Handle TimeoutB in St2";
		case terminals::Message::TimeoutCInSt2:        return "Handle TimeoutC in St2";
		case terminals::Message::EnterSt1a:            return "Enter St1a";
		case terminals::Message::ExitSt1a:             return "Exit St1a";
		case terminals::Message::Event0InSt1a:         return "Handle Event0 in St1a";
		case terminals::Message::Event3InSt1a:         return "Handle Event3 in St1a";
		case terminals::Message::Event5InSt1a:         return "Handle Event5 in St1a";
		case terminals::Message::UserTimeoutInSt1a:    return "Handle UserTimeout in St1a";
		case terminals::Message::SystemTimeoutInSt1a:  return "Handle SystemTimeout in St1a";
		default:                                       return "Unknown";
		}
	}
}
