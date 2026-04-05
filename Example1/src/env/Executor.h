#pragma once

#include "Terminals/EventSenderService.h"

namespace anonys { class FsmPool; struct Event; }

namespace env {
	class TestEventSenderService;
	class TestTimerService;

	class Executor : public terminals::EventSenderService {
	public:
		Executor(anonys::FsmPool& fsmPool, TestEventSenderService& testEventSender, TestTimerService& testTimerService);

		bool sendNextEvent();
		bool sendNextTimeout();
		bool sendNext();

	protected:
		void doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) override;

	private:
		static void printEvent(char const* pPrefix, anonys::Event const& event);

		anonys::FsmPool& m_fsmPool;
		TestEventSenderService& m_testEventSender;
		TestTimerService& m_testTimerService;
	};
}
