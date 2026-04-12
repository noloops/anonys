// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "TestLog.h"
#include "Expected.h"
#include "Helper.h"
#include <iostream>

namespace env {
    void TestLog::write(terminals::Message message) {
        Expected::checkLogWrite(message);
        std::cout << m_pHeader << " " << Helper::getLogMessage(message) << std::endl;
    }

    void TestLog::write(terminals::Message message, int32_t value) {
        Expected::checkLogWrite(message, value);
        std::cout << m_pHeader << " " << Helper::getLogMessage(message) << " (" << value << ")" << std::endl;
    }
}
