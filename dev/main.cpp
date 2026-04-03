#include <iostream>
#include <type_traits>
#include "anonys/FsmBase.h"
#include "Fsm/A.h"
#include "anonys/FsmId.h"
#include "Terminals/Terminals.h"

int main()
{
	terminals::EventSender eventSender{};
	terminals::TimerMngr timerMngr{};
	terminals::Log log{"A:"};
	terminals::Std stdTerminal{ eventSender, timerMngr, log };

	auto const id{ anonys::FsmId::A };
	anonys_1::Terminals terminals{ &stdTerminal };
	constexpr size_t bufferSize{ 512 };
    std::aligned_storage_t<bufferSize, anonys::StdAlign> buffer;
	uint8_t* pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&buffer)) };
    anonys::FsmBase smb{ id, &terminals, pBuffer, bufferSize };

    std::cout << "Hello World!\n";
}
