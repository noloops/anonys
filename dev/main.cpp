#include <iostream>
#include <type_traits>
#include "anonys/StateMachineBase.h"
#include "AnonysConfig.h"
#include "States/A.h"


int main()
{
	anonys_1::Terminals terminals{};
	constexpr size_t bufferSize{ 512 };
    std::aligned_storage_t<bufferSize, anonys::StdAlign> buffer;
	uint8_t* pBuffer{ std::launder(reinterpret_cast<uint8_t*>(&buffer)) };
    anonys::StateMachineBase smb{ &terminals, pBuffer, bufferSize };

    std::cout << "Hello World!\n";
}
