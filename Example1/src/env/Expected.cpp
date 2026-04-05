#include "Expected.h"
#include "Helper.h"
#include <iostream>
#include <cstring>

namespace env {
	std::list<Expected::Entry> Expected::m_entries;
	bool Expected::m_enabled{false};

	// Enable / disable

	void Expected::enable(bool enabled) {
		m_entries.clear();
		m_enabled = enabled;
	}

	// Get helpers

	Expected::Entry Expected::getLogWrite1(terminals::Message message) {
		Entry entry{};
		entry.kind = Kind::LogWrite1;
		entry.data.logWrite1 = {message};
		return entry;
	}

	Expected::Entry Expected::getLogWrite2(terminals::Message message, int32_t value) {
		Entry entry{};
		entry.kind = Kind::LogWrite2;
		entry.data.logWrite2 = {message, value};
		return entry;
	}

	Expected::Entry Expected::getTimerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) {
		Entry entry{};
		entry.kind = Kind::TimerStartTimer;
		entry.data.timerStartTimer = {fsmId, depth, eventId.id, timeoutMs};
		return entry;
	}

	Expected::Entry Expected::getTimerStopTimers(anonys::FsmId fsmId, int16_t depth) {
		Entry entry{};
		entry.kind = Kind::TimerStopTimers;
		entry.data.timerStopTimers = {fsmId, depth};
		return entry;
	}

	Expected::Entry Expected::getEventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, uint16_t size) {
		Entry entry{};
		entry.kind = Kind::EventSenderDoSend;
		entry.data.eventSenderDoSend = {fsmId, eventId.id, size};
		return entry;
	}

	Expected::Entry Expected::getTracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceHandledEvent;
		entry.data.tracingTraceHandledEvent = {fsmId, stateId, eventId.id};
		return entry;
	}

	Expected::Entry Expected::getTracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceUnhandledEvent;
		entry.data.tracingTraceUnhandledEvent = {fsmId, stateId, eventId.id};
		return entry;
	}

	Expected::Entry Expected::getTracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceEnterState;
		entry.data.tracingTraceEnterState = {fsmId, stateId};
		return entry;
	}

	Expected::Entry Expected::getTracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		Entry entry{};
		entry.kind = Kind::TracingTraceExitState;
		entry.data.tracingTraceExitState = {fsmId, stateId};
		return entry;
	}

	// Print helpers

	void Expected::printEmpty() {
		std::cout << "EXPECTED: <empty>" << std::endl;
	}

	void Expected::printEntry(bool expected, Entry const& entry) {
		char const* const prefix{expected ? "EXPECTED: " : "ACTUAL: "};
		switch (entry.kind) {
		case Kind::LogWrite1:
			std::cout << prefix << "logWrite(" << Helper::getLogMessage(entry.data.logWrite1.message) << ")" << std::endl;
			break;
		case Kind::LogWrite2:
			std::cout << prefix << "logWrite(" << Helper::getLogMessage(entry.data.logWrite2.message) << ", " << entry.data.logWrite2.value << ")" << std::endl;
			break;
		case Kind::TimerStartTimer:
			std::cout << prefix << "timerStartTimer(" << Helper::getFsmName(entry.data.timerStartTimer.fsmId)
				<< ", depth=" << entry.data.timerStartTimer.depth
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.timerStartTimer.eventIdValue})
				<< ", " << entry.data.timerStartTimer.timeoutMs << "ms)" << std::endl;
			break;
		case Kind::TimerStopTimers:
			std::cout << prefix << "timerStopTimers(" << Helper::getFsmName(entry.data.timerStopTimers.fsmId)
				<< ", depth=" << entry.data.timerStopTimers.depth << ")" << std::endl;
			break;
		case Kind::EventSenderDoSend:
			std::cout << prefix << "eventSenderDoSend(" << Helper::getFsmName(entry.data.eventSenderDoSend.fsmId)
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.eventSenderDoSend.eventIdValue})
				<< ", size=" << entry.data.eventSenderDoSend.size << ")" << std::endl;
			break;
		case Kind::TracingTraceHandledEvent:
			std::cout << prefix << "tracingTraceHandledEvent(" << Helper::getFsmName(entry.data.tracingTraceHandledEvent.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceHandledEvent.fsmId, entry.data.tracingTraceHandledEvent.stateId)
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.tracingTraceHandledEvent.eventIdValue}) << ")" << std::endl;
			break;
		case Kind::TracingTraceUnhandledEvent:
			std::cout << prefix << "tracingTraceUnhandledEvent(" << Helper::getFsmName(entry.data.tracingTraceUnhandledEvent.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceUnhandledEvent.fsmId, entry.data.tracingTraceUnhandledEvent.stateId)
				<< ", " << Helper::getEventName(anonys::EventId{entry.data.tracingTraceUnhandledEvent.eventIdValue}) << ")" << std::endl;
			break;
		case Kind::TracingTraceEnterState:
			std::cout << prefix << "tracingTraceEnterState(" << Helper::getFsmName(entry.data.tracingTraceEnterState.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceEnterState.fsmId, entry.data.tracingTraceEnterState.stateId) << ")" << std::endl;
			break;
		case Kind::TracingTraceExitState:
			std::cout << prefix << "tracingTraceExitState(" << Helper::getFsmName(entry.data.tracingTraceExitState.fsmId)
				<< ", " << Helper::getStateName(entry.data.tracingTraceExitState.fsmId, entry.data.tracingTraceExitState.stateId) << ")" << std::endl;
			break;
		}
	}

	// Common check

	bool Expected::check(Entry const& actual) {
		if (!m_enabled) {
			return true;
		}
		if (m_entries.empty()) {
			printEmpty();
			printEntry(false, actual);
			return false;
		}
		Entry const expected{m_entries.front()};
		m_entries.pop_front();
		if (std::memcmp(&expected, &actual, sizeof(Entry)) == 0) {
			return true;
		}
		printEntry(true, expected);
		printEntry(false, actual);
		return false;
	}

	// Record methods

	void Expected::logWrite(terminals::Message message) {
		if (m_enabled) { m_entries.push_back(getLogWrite1(message)); }
	}

	void Expected::logWrite(terminals::Message message, int32_t value) {
		if (m_enabled) { m_entries.push_back(getLogWrite2(message, value)); }
	}

	void Expected::timerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) {
		if (m_enabled) { m_entries.push_back(getTimerStartTimer(fsmId, depth, eventId, timeoutMs)); }
	}

	void Expected::timerStopTimers(anonys::FsmId fsmId, int16_t depth) {
		if (m_enabled) { m_entries.push_back(getTimerStopTimers(fsmId, depth)); }
	}

	void Expected::eventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		if (m_enabled) { m_entries.push_back(getEventSenderDoSend(fsmId, eventId, size)); }
	}

	void Expected::tracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		if (m_enabled) { m_entries.push_back(getTracingTraceHandledEvent(fsmId, stateId, eventId)); }
	}

	void Expected::tracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		if (m_enabled) { m_entries.push_back(getTracingTraceUnhandledEvent(fsmId, stateId, eventId)); }
	}

	void Expected::tracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		if (m_enabled) { m_entries.push_back(getTracingTraceEnterState(fsmId, stateId)); }
	}

	void Expected::tracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		if (m_enabled) { m_entries.push_back(getTracingTraceExitState(fsmId, stateId)); }
	}

	// Check methods

	bool Expected::checkLogWrite(terminals::Message message) {
		return check(getLogWrite1(message));
	}

	bool Expected::checkLogWrite(terminals::Message message, int32_t value) {
		return check(getLogWrite2(message, value));
	}

	bool Expected::checkTimerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs) {
		return check(getTimerStartTimer(fsmId, depth, eventId, timeoutMs));
	}

	bool Expected::checkTimerStopTimers(anonys::FsmId fsmId, int16_t depth) {
		return check(getTimerStopTimers(fsmId, depth));
	}

	bool Expected::checkEventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		return check(getEventSenderDoSend(fsmId, eventId, size));
	}

	bool Expected::checkTracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		return check(getTracingTraceHandledEvent(fsmId, stateId, eventId));
	}

	bool Expected::checkTracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId) {
		return check(getTracingTraceUnhandledEvent(fsmId, stateId, eventId));
	}

	bool Expected::checkTracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId) {
		return check(getTracingTraceEnterState(fsmId, stateId));
	}

	bool Expected::checkTracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId) {
		return check(getTracingTraceExitState(fsmId, stateId));
	}
}
