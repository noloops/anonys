// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "Executor.h"
#include "TestEventSenderService.h"
#include "TestTimerService.h"
#include "Expected.h"
#include "Helper.h"
#include "anonys/FsmPool.h"
#include <iostream>

namespace env {
	Executor::Executor(anonys::FsmPool& fsmPool, TestEventSenderService& testEventSender, TestTimerService& testTimerService)
		: m_fsmPool{fsmPool}
		, m_testEventSender{testEventSender}
		, m_testTimerService{testTimerService}
	{}

	void Executor::clear() {
		Expected::clear();
		m_hasWarnings = false;
	}

	void Executor::printEvent(char const* pPrefix, anonys::FsmId fsmId, anonys::Event const& event) {
		std::cout << pPrefix << Helper::getEventName(event.eventId);
		std::cout << " -> " << Helper::getFsmName(fsmId) << std::endl;
	}

	void Executor::doSend(anonys::FsmId fsmId, anonys::EventId eventId, const void* pData, uint16_t size) {
		if (!m_testEventSender.isEmpty()) {
			std::cout << "WARNING: TestEventSenderService is not empty" << std::endl;
			m_hasWarnings = true;
		}
		anonys::Event event{eventId, const_cast<void*>(pData)};
		printEvent(">>>> EVENT: ", fsmId, event);
		m_fsmPool.handleEvent(fsmId, event);
	}

	bool Executor::sendNextEvent() {
		TestEventSenderService::Buffer buffer;
		auto result{m_testEventSender.getEvent(buffer)};
		if (!result.valid) {
			return false;
		}
		printEvent(">> EVENT: ", result.fsmId, result.event);
		m_fsmPool.handleEvent(result.fsmId, result.event);
		return true;
	}

	bool Executor::sendNextTimeout() {
		auto result{m_testTimerService.getNextTimeout()};
		if (!result.valid) {
			return false;
		}
		std::cout << ">> TIMEOUT: " << Helper::getEventName(result.timeout.eventId) << " -> " << Helper::getFsmName(result.timeout.fsmId) << " @" << result.systemTimeMs << "ms" << std::endl;
		m_fsmPool.handleTimeoutEvent(result.timeout.fsmId, result.timeout.depth, result.timeout.eventId);
		return true;
	}

	bool Executor::sendNext() {
		if (sendNextEvent()) {
			return true;
		}
		if (sendNextTimeout()) {
			return true;
		}
		return false;
	}
}
