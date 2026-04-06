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
