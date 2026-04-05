#pragma once

#include <cstdint>
#include <list>
#include "anonys/FsmId.h"
#include "anonys/Types.h"
#include "Terminals/LogService.h"

namespace env {
	class Expected {
	public:
		static void enable(bool enabled);

		// Record expected calls
		static void logWrite(terminals::Message message);
		static void logWrite(terminals::Message message, int32_t value);
		static void timerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs);
		static void timerStopTimers(anonys::FsmId fsmId, int16_t depth);
		static void eventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size);
		static void tracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId);
		static void tracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId);
		static void tracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId);
		static void tracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId);

		// Check actual calls against expected
		static bool checkLogWrite(terminals::Message message);
		static bool checkLogWrite(terminals::Message message, int32_t value);
		static bool checkTimerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs);
		static bool checkTimerStopTimers(anonys::FsmId fsmId, int16_t depth);
		static bool checkEventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size);
		static bool checkTracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId);
		static bool checkTracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId);
		static bool checkTracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId);
		static bool checkTracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId);

	private:
		enum class Kind {
			LogWrite1,
			LogWrite2,
			TimerStartTimer,
			TimerStopTimers,
			EventSenderDoSend,
			TracingTraceHandledEvent,
			TracingTraceUnhandledEvent,
			TracingTraceEnterState,
			TracingTraceExitState,
		};

		struct Entry {
			Kind kind;
			union {
				struct { terminals::Message message; } logWrite1;
				struct { terminals::Message message; int32_t value; } logWrite2;
				struct { anonys::FsmId fsmId; int16_t depth; uint16_t eventIdValue; uint32_t timeoutMs; } timerStartTimer;
				struct { anonys::FsmId fsmId; int16_t depth; } timerStopTimers;
				struct { anonys::FsmId fsmId; uint16_t eventIdValue; uint16_t size; } eventSenderDoSend;
				struct { anonys::FsmId fsmId; uint16_t stateId; uint16_t eventIdValue; } tracingTraceHandledEvent;
				struct { anonys::FsmId fsmId; uint16_t stateId; uint16_t eventIdValue; } tracingTraceUnhandledEvent;
				struct { anonys::FsmId fsmId; uint16_t stateId; } tracingTraceEnterState;
				struct { anonys::FsmId fsmId; uint16_t stateId; } tracingTraceExitState;
			} data;
		};

		static Entry getLogWrite1(terminals::Message message);
		static Entry getLogWrite2(terminals::Message message, int32_t value);
		static Entry getTimerStartTimer(anonys::FsmId fsmId, int16_t depth, anonys::EventId eventId, uint32_t timeoutMs);
		static Entry getTimerStopTimers(anonys::FsmId fsmId, int16_t depth);
		static Entry getEventSenderDoSend(anonys::FsmId fsmId, anonys::EventId eventId, uint16_t size);
		static Entry getTracingTraceHandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId);
		static Entry getTracingTraceUnhandledEvent(anonys::FsmId fsmId, uint16_t stateId, anonys::EventId eventId);
		static Entry getTracingTraceEnterState(anonys::FsmId fsmId, uint16_t stateId);
		static Entry getTracingTraceExitState(anonys::FsmId fsmId, uint16_t stateId);

		static void printEntry(bool expected, Entry const& entry);
		static void printEmpty();

		static bool check(Entry const& actual);

		static std::list<Entry> m_entries;
		static bool m_enabled;
	};
}
