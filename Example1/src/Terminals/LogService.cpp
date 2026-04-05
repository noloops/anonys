#include "Terminals/LogService.h"

namespace terminals {
	const char* LogService::resolve(Message message) {
		switch (message) {
		case Message::EnterSt1:             return "Enter St1";
		case Message::ExitSt1:              return "Exit St1";
		case Message::Event1InSt1:          return "Handle Event1 in St1";
		case Message::Event4InSt1:          return "Handle Event4 in St1";
		case Message::Event5InSt1:          return "Handle Event5 in St1";
		case Message::UserTimeoutInSt1:     return "Handle UserTimeout in St1";
		case Message::EnterSt2:             return "Enter St2";
		case Message::ExitSt2:              return "Exit St2";
		case Message::Event2InSt2:          return "Handle Event2 in St2";
		case Message::Event7InSt2:          return "Handle Event7 in St2";
		case Message::Event8InSt2:          return "Handle Event8 in St2";
		case Message::TimeoutAInSt2:        return "Handle TimeoutA in St2";
		case Message::TimeoutBInSt2:        return "Handle TimeoutB in St2";
		case Message::TimeoutCInSt2:        return "Handle TimeoutC in St2";
		case Message::EnterSt1a:            return "Enter St1a";
		case Message::ExitSt1a:             return "Exit St1a";
		case Message::Event0InSt1a:         return "Handle Event0 in St1a";
		case Message::Event3InSt1a:         return "Handle Event3 in St1a";
		case Message::Event5InSt1a:         return "Handle Event5 in St1a";
		case Message::UserTimeoutInSt1a:    return "Handle UserTimeout in St1a";
		case Message::SystemTimeoutInSt1a:  return "Handle SystemTimeout in St1a";
		default:                            return "Unknown";
		}
	}
}
