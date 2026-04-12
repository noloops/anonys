// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

#include "Terminals/LogService.h"

namespace env {
    class TestLog : public terminals::LogService {
    public:
        TestLog(const char* pHeader) : m_pHeader{ pHeader } {}

        void write(terminals::Message message) override;
        void write(terminals::Message message, int32_t value) override;

    private:
        const char* m_pHeader;
    };
}
