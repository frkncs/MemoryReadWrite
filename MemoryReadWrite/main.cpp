#include <iostream>
#include "Memory.h"

int main()
{
	Memory memory = Memory("processName.exe"); // like "csgo.exe"
	uintptr_t clientAddress = memory.GetModuleAddress("moduleName.exe"); // like "client.dll"

	std::cout << "Process Id: " << memory.GetProcessId() << std::endl;
	std::cout << "Client Address: " << "0x" << std::hex << clientAddress << std::dec << std::endl;

	std::cout << "Press enter to close..." << std::endl;
	std::cin.get();
}