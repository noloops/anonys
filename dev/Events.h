#pragma once

#include <cstdint>

namespace events {
	struct Event0 {

	};

	struct Event1 {
		uint8_t m_dummies[1]{};
	};

	struct Event2 {
		uint8_t m_dummies[2]{};
	};

	struct Event3 {
		uint8_t m_dummies[3]{};
	};

	struct Event4 {
		uint8_t m_dummies[4]{};
	};

	struct Event5 {
		uint8_t m_dummies[5]{};
	};

	struct Event6 {
		uint8_t m_dummies[6]{};
	};

	struct Event7 {
		uint8_t m_dummies[7]{};
	};

	struct Event8 {
		uint8_t m_dummies[8]{};
	};
}