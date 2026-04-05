#include "Helper.h"

namespace env {
	const char* Helper::getFsmName(anonys::FsmId fsmId) {
		switch (fsmId) {
		case anonys::FsmId::Jukebox: return "Jukebox";
		default: return "?";
		}
	}

	const char* Helper::getStateName(anonys::FsmId fsmId, uint16_t stateId) {
		switch (fsmId) {
		case anonys::FsmId::Jukebox:
			switch (stateId) {
			case 1: return "Off";
			case 2: return "Idle";
			case 3: return "Playing";
			case 4: return "Normal";
			case 5: return "Paused";
			case 6: return "Error";
			case 7: return "AutoPause";
			case 8: return "On";
			default: return "?";
			}
		default: return "?";
		}
	}

	const char* Helper::getEventName(anonys::EventId eventId) {
		switch (eventId.id) {
		case 0: return "PowerOn";
		case 1: return "PowerOff";
		case 2: return "InsertCoin";
		case 3: return "Play";
		case 4: return "Pause";
		case 5: return "Skip";
		case 6: return "Eject";
		case 7: return "Diagnostic";
		case 8: return "Malfunction";
		case 9: return "Reset";
		case 10: return "AutoPause";
		case 11: return "ConfigureAutoPause";
		case 60001: return "TrackTimer";
		case 60002: return "SleepTimer";
		case 60003: return "RecoveryTimer";
		case 60004: return "PauseCountdownTimer";
		default: return "?";
		}
	}

	const char* Helper::getLogMessage(terminals::Message message) {
		switch (message) {
		case terminals::Message::EnterOff:                return "Enter Off";
		case terminals::Message::ExitOff:                 return "Exit Off";
		case terminals::Message::PowerOnInOff:            return "PowerOn in Off";
		case terminals::Message::EnterOn:                 return "Enter On";
		case terminals::Message::ExitOn:                  return "Exit On";
		case terminals::Message::PowerOffInOn:            return "PowerOff in On";
		case terminals::Message::MalfunctionInOn:         return "Malfunction in On";
		case terminals::Message::EnterIdle:               return "Enter Idle";
		case terminals::Message::ExitIdle:                return "Exit Idle";
		case terminals::Message::InsertCoinInIdle:        return "InsertCoin in Idle";
		case terminals::Message::DiagnosticInIdle:        return "Diagnostic in Idle";
		case terminals::Message::SleepTimeoutInIdle:      return "SleepTimeout in Idle";
		case terminals::Message::MalfunctionStoppedInIdle: return "Malfunction stopped in Idle";
		case terminals::Message::EnterPlaying:            return "Enter Playing";
		case terminals::Message::ExitPlaying:             return "Exit Playing";
		case terminals::Message::EjectInPlaying:          return "Eject in Playing";
		case terminals::Message::AutoPauseInPlaying:      return "AutoPause in Playing";
		case terminals::Message::EnterNormal:             return "Enter Normal";
		case terminals::Message::ExitNormal:              return "Exit Normal";
		case terminals::Message::PauseInNormal:           return "Pause in Normal";
		case terminals::Message::SkipInNormal:            return "Skip in Normal";
		case terminals::Message::TrackEndInNormal:        return "TrackEnd in Normal";
		case terminals::Message::EnterPaused:             return "Enter Paused";
		case terminals::Message::ExitPaused:              return "Exit Paused";
		case terminals::Message::PlayInPaused:            return "Play in Paused";
		case terminals::Message::ConfigureAutoPauseInPaused: return "ConfigureAutoPause in Paused";
		case terminals::Message::EnterAutoPause:          return "Enter AutoPause";
		case terminals::Message::ExitAutoPause:           return "Exit AutoPause";
		case terminals::Message::PauseInAutoPause:        return "Pause in AutoPause";
		case terminals::Message::CountdownTimerInAutoPause: return "CountdownTimer in AutoPause";
		case terminals::Message::CountdownReachedZero:    return "Countdown reached zero";
		case terminals::Message::EnterError:              return "Enter Error";
		case terminals::Message::ExitError:               return "Exit Error";
		case terminals::Message::ResetInError:            return "Reset in Error";
		case terminals::Message::RecoveryTimeoutInError:  return "RecoveryTimeout in Error";
		default:                                          return "Unknown";
		}
	}
}
