// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

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
		void clear();
		bool hasWarnings() const { return m_hasWarnings; }

	protected:
		void doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) override;

	private:
		static void printEvent(char const* pPrefix, anonys::FsmId fsmId, anonys::Event const& event);

		anonys::FsmPool& m_fsmPool;
		TestEventSenderService& m_testEventSender;
		TestTimerService& m_testTimerService;
		bool m_hasWarnings{false};
	};
}
