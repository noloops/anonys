// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "env/Tester.h"
#include "env/Demo.h"
#include "anonys/BufferCalc.h"
#include <iostream>

int main()
{
    auto const bufferCalcResult{anonys::calcBuffer()};
    std::cout << "BufferCalc: ok=" << bufferCalcResult.ok
              << " sizeJukebox=" << bufferCalcResult.sizeJukebox << std::endl;
    if (!bufferCalcResult.ok) {
        return 2;
    }
    if (!env::Tester::runAllTests()) {
        return 1;
    }
    env::Demo::run();
    return 0;
}
