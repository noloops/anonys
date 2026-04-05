#include "Expected.h"
#include "Helper.h"
#include <iostream>

namespace env {
	std::list<Expected::Entry> Expected::m_entries;

	// Record methods

	void Expected::logWrite(terminals::Message message) {
		Entry entry{};
		entry.kind = Kind::LogWrite1;
		entry.data.logWrite1 = {message};
		m_entries.push_back(entry);
	}

	void Expected::logWrite(terminals::Message message, int32_t value) {
		Entry entry{};
		entry.kind = Kind::LogWrite2;
		entry.data.logWrite2 = {message, value};
		m_entries.push_back(entry);
	}

	void Expected::timerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) {
		Entry entry{};
		entry.kind = Kind::TimerStartTimer;
		entry.data.timerStartTimer = {fsmId, depth, eventId.id, timeoutMs};
		m_entries.push_back(entry);
	}

	void Expected::timerStopTimers(anonys::FsmId fsmId, int16_t depth) {
		Entry entry{};
		entry.kind = Kind::TimerStopTimers;
		entry.data.timerStopTimers = {fsmId, depth};
		m_entries.push_back(entry);
	}

	void Expected::eventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		Entry entry{};
		entry.kind = Kind::EventSenderDoSend;
		entry.data.eventSenderDoSend = {fsmId, eventId.id, size};
		m_entries.push_back(entry);
	}

	void Expected::tracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceHandledEvent;
		entry.data.tracingTraceHandledEvent = {fsmId, stateId, eventId.id};
		m_entries.push_back(entry);
	}

	void Expected::tracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceUnhandledEvent;
		entry.data.tracingTraceUnhandledEvent = {fsmId, stateId, eventId.id};
		m_entries.push_back(entry);
	}

	void Expected::tracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceEnterState;
		entry.data.tracingTraceEnterState = {fsmId, stateId};
		m_entries.push_back(entry);
	}

	void Expected::tracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceExitState;
		entry.data.tracingTraceExitState = {fsmId, stateId};
		m_entries.push_back(entry);
	}

	// Check methods

	const char* Expected::kindName(Kind kind) {
		switch (kind) {
		case Kind::LogWrite1:                  return "logWrite";
		case Kind::LogWrite2:                  return "logWrite";
		case Kind::TimerStartTimer:            return "timerStartTimer";
		case Kind::TimerStopTimers:            return "timerStopTimers";
		case Kind::EventSenderDoSend:          return "eventSenderDoSend";
		case Kind::TracingTraceHandledEvent:   return "tracingTraceHandledEvent";
		case Kind::TracingTraceUnhandledEvent: return "tracingTraceUnhandledEvent";
		case Kind::TracingTraceEnterState:     return "tracingTraceEnterState";
		case Kind::TracingTraceExitState:      return "tracingTraceExitState";
		default: return "?";
		}
	}

	void Expected::printExpected(Entry const& entry) {
		switch (entry.kind) {
		case Kind::LogWrite1:
			std::cout << "EXPECTED: logWrite(" << Helper::getLogMessage(entry.data.logWrite1.message) << ")" << std::endl;
			break;
		case Kind::LogWrite2:
			std::cout << "EXPECTED: logWrite(" << Helper::getLogMessage(entry.data.logWrite2.message) << ", " << entry.data.logWrite2.value << ")" << std::endl;
			break;
		case Kind::TimerStartTimer:
			std::cout << "EXPECTED: timerStartTimer(" << Helper::getFsmName(entry.data.timerStartTimer.fsmId)
				<< ", depth=" << entry.data.timerStartTimer.depth
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.timerStartTimer.eventIdValue})
				<< ", " << entry.data.timerStartTimer.timeoutMs << "ms)" << std::endl;
			break;
		case Kind::TimerStopTimers:
			std::cout << "EXPECTED: timerStopTimers(" << Helper::getFsmName(entry.data.timerStopTimers.fsmId)
				<< ", depth=" << entry.data.timerStopTimers.depth << ")" << std::endl;
			break;
		case Kind::EventSenderDoSend:
			std::cout << "EXPECTED: eventSenderDoSend(" << Helper::getFsmName(entry.data.eventSenderDoSend.fsmId)
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.eventSenderDoSend.eventIdValue})
				<< ", size=" << entry.data.eventSenderDoSend.size << ")" << std::endl;
			break;
		case Kind::TracingTraceHandledEvent:
			std::cout << "EXPECTED: tracingTraceHandledEvent(" << Helper::getFsmName(entry.data.tracingTraceHandledEvent.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceHandledEvent.fsmId, entry.data.tracingTraceHandledEvent.stateId)
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.tracingTraceHandledEvent.eventIdValue}) << ")" << std::endl;
			break;
		case Kind::TracingTraceUnhandledEvent:
			std::cout << "EXPECTED: tracingTraceUnhandledEvent(" << Helper::getFsmName(entry.data.tracingTraceUnhandledEvent.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceUnhandledEvent.fsmId, entry.data.tracingTraceUnhandledEvent.stateId)
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.tracingTraceUnhandledEvent.eventIdValue}) << ")" << std::endl;
			break;
		case Kind::TracingTraceEnterState:
			std::cout << "EXPECTED: tracingTraceEnterState(" << Helper::getFsmName(entry.data.tracingTraceEnterState.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceEnterState.fsmId, entry.data.tracingTraceEnterState.stateId) << ")" << std::endl;
			break;
		case Kind::TracingTraceExitState:
			std::cout << "EXPECTED: tracingTraceExitState(" << Helper::getFsmName(entry.data.tracingTraceExitState.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceExitState.fsmId, entry.data.tracingTraceExitState.stateId) << ")" << std::endl;
			break;
		}
	}

	bool Expected::checkLogWrite(terminals::Message message) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: logWrite(" << Helper::getLogMessage(message) << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::LogWrite1 && entry.data.logWrite1.message == message) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: logWrite(" << Helper::getLogMessage(message) << ")" << std::endl;
		return false;
	}

	bool Expected::checkLogWrite(terminals::Message message, int32_t value) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: logWrite(" << Helper::getLogMessage(message) << ", " << value << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::LogWrite2 && entry.data.logWrite2.message == message && entry.data.logWrite2.value == value) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: logWrite(" << Helper::getLogMessage(message) << ", " << value << ")" << std::endl;
		return false;
	}

	bool Expected::checkTimerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: timerStartTimer(" << Helper::getFsmName(fsmId)
				<< ", depth=" << depth << ", " << Helper::getEventName(eventId)
				<< ", " << timeoutMs << "ms)" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::TimerStartTimer
			&& entry.data.timerStartTimer.fsmId == fsmId
			&& entry.data.timerStartTimer.depth == depth
			&& entry.data.timerStartTimer.eventIdValue == eventId.id
			&& entry.data.timerStartTimer.timeoutMs == timeoutMs) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: timerStartTimer(" << Helper::getFsmName(fsmId)
			<< ", depth=" << depth << ", " << Helper::getEventName(eventId)
			<< ", " << timeoutMs << "ms)" << std::endl;
		return false;
	}

	bool Expected::checkTimerStopTimers(anonys::FsmId fsmId, int16_t depth) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: timerStopTimers(" << Helper::getFsmName(fsmId) << ", depth=" << depth << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::TimerStopTimers
			&& entry.data.timerStopTimers.fsmId == fsmId
			&& entry.data.timerStopTimers.depth == depth) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: timerStopTimers(" << Helper::getFsmName(fsmId) << ", depth=" << depth << ")" << std::endl;
		return false;
	}

	bool Expected::checkEventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: eventSenderDoSend(" << Helper::getFsmName(fsmId)
				<< ", " << Helper::getEventName(eventId) << ", size=" << size << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::EventSenderDoSend
			&& entry.data.eventSenderDoSend.fsmId == fsmId
			&& entry.data.eventSenderDoSend.eventIdValue == eventId.id
			&& entry.data.eventSenderDoSend.size == size) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: eventSenderDoSend(" << Helper::getFsmName(fsmId)
			<< ", " << Helper::getEventName(eventId) << ", size=" << size << ")" << std::endl;
		return false;
	}

	bool Expected::checkTracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: tracingTraceHandledEvent(" << Helper::getFsmName(fsmId)
				<< ", " << Helper::getStateName(fsmId, stateId)
				<< ", " << Helper::getEventName(eventId) << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::TracingTraceHandledEvent
			&& entry.data.tracingTraceHandledEvent.fsmId == fsmId
			&& entry.data.tracingTraceHandledEvent.stateId == stateId
			&& entry.data.tracingTraceHandledEvent.eventIdValue == eventId.id) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: tracingTraceHandledEvent(" << Helper::getFsmName(fsmId)
			<< ", " << Helper::getStateName(fsmId, stateId)
			<< ", " << Helper::getEventName(eventId) << ")" << std::endl;
		return false;
	}

	bool Expected::checkTracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: tracingTraceUnhandledEvent(" << Helper::getFsmName(fsmId)
				<< ", " << Helper::getStateName(fsmId, stateId)
				<< ", " << Helper::getEventName(eventId) << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::TracingTraceUnhandledEvent
			&& entry.data.tracingTraceUnhandledEvent.fsmId == fsmId
			&& entry.data.tracingTraceUnhandledEvent.stateId == stateId
			&& entry.data.tracingTraceUnhandledEvent.eventIdValue == eventId.id) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: tracingTraceUnhandledEvent(" << Helper::getFsmName(fsmId)
			<< ", " << Helper::getStateName(fsmId, stateId)
			<< ", " << Helper::getEventName(eventId) << ")" << std::endl;
		return false;
	}

	bool Expected::checkTracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: tracingTraceEnterState(" << Helper::getFsmName(fsmId)
				<< ", " << Helper::getStateName(fsmId, stateId) << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::TracingTraceEnterState
			&& entry.data.tracingTraceEnterState.fsmId == fsmId
			&& entry.data.tracingTraceEnterState.stateId == stateId) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: tracingTraceEnterState(" << Helper::getFsmName(fsmId)
			<< ", " << Helper::getStateName(fsmId, stateId) << ")" << std::endl;
		return false;
	}

	bool Expected::checkTracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		if (m_entries.empty()) {
			std::cout << "EXPECTED: <empty>" << std::endl;
			std::cout << "ACTUAL: tracingTraceExitState(" << Helper::getFsmName(fsmId)
				<< ", " << Helper::getStateName(fsmId, stateId) << ")" << std::endl;
			return false;
		}
		Entry const entry{m_entries.front()};
		m_entries.pop_front();
		if (entry.kind == Kind::TracingTraceExitState
			&& entry.data.tracingTraceExitState.fsmId == fsmId
			&& entry.data.tracingTraceExitState.stateId == stateId) {
			return true;
		}
		printExpected(entry);
		std::cout << "ACTUAL: tracingTraceExitState(" << Helper::getFsmName(fsmId)
			<< ", " << Helper::getStateName(fsmId, stateId) << ")" << std::endl;
		return false;
	}
}
