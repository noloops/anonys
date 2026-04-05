#pragma once

#include <cstdint>

namespace events {
	struct Event0 {

	};

	struct Event1 {
		uint8_t dummies[1]{};
	};

	struct Event2 {
		uint8_t dummies[2]{};
	};

	struct Event3 {
		uint8_t dummies[3]{};
	};

	struct Event4 {
		uint8_t dummies[4]{};
	};

	struct Event5 {
		uint8_t dummies[5]{};
	};

	struct Event6 {
		uint8_t dummies[6]{};
	};

	struct Event7 {
		uint8_t dummies[7]{};
	};

	struct Event8 {
		uint8_t dummies[8]{};
	};

	struct EventInt0 {
		int32_t value{};
	};

	struct EventInt1 {
		int32_t value{};
		uint8_t dummies[1]{};
	};

	struct EventInt2 {
		int32_t value{};
		uint8_t dummies[2]{};
	};
}