#include <iostream>
#include <type_traits>
#include "anonys/StateMachineBase.h"
#include "AnonysConfig.h"
#include "States/A.h"
#include "StateMachines/StateMachineId.h"

int main()
{
	auto const id{ StateMachines::StateMachineId::A };
	anonys_1::Terminals terminals{};
	constexpr size_t bufferSize{ 512 };
    std::aligned_storage_t<bufferSize, anonys::StdAlign> buffer;
	uint8_t* pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&buffer)) };
    anonys::StateMachineBase smb{ id, &terminals, pBuffer, bufferSize };

    std::cout << "Hello World!\n";
}
