#include "anonys/fsm/Washer.h"
#include "Events.h"
#include "Terminals.h"

namespace {
	struct Me {
	};
}

// Generated code, do not edit:
namespace anonys_2_10 {
    anonys::State* handleEvent(void* pMembers, anonys::Event& event) {
        return &anonys::DummyStates::Unhandled;
    }

    void liveCycle(bool create, void* pTerminals, void* pMembers) {
        if (create) {
            ::new (pMembers) Me{};
        }
        else {
            Me& me{ *static_cast<Me*>(pMembers) };
            me.~Me();
        }
    }

    uint16_t getMembersSize() {
        return anonys::getAlignedSize<Me>();
    }
}
