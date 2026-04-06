// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#pragma once

struct Start {};

namespace signals {
	struct Stop {};
}

namespace signals::alert {
	struct Emergency {};
}

namespace ctrl {
	class Proceed {};
}

namespace ctrl::cmd {
	struct Reset {};
}

namespace io {
	struct SensorTriggered {};
}

namespace io::data {
	struct Tick {};
}
