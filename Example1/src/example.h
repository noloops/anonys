// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#ifndef EXAMPLE1_EXAMPLE_H
#define EXAMPLE1_EXAMPLE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void handleStartup(void);
void handleTick(uint32_t sysMs);
void handleButton(bool pressed);
void setLed(bool on);

#ifdef __cplusplus
}
#endif

#endif // EXAMPLE1_EXAMPLE_H
