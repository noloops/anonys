// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#include "example.h"

namespace {
	enum class Mode { Off, Blinking };
	Mode s_mode{ Mode::Off };
	bool s_ledState{ false };
}

void handleTick() {
	if (s_mode == Mode::Blinking) {
		s_ledState = !s_ledState;
		setLed(s_ledState);
	}
}

void handleClick() {
	if (s_mode == Mode::Off) {
		s_mode = Mode::Blinking;
	}
	else {
		s_mode = Mode::Off;
		s_ledState = false;
		setLed(false);
	}
}
