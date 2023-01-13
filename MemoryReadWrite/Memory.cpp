#include "Memory.h"
#include <TlHelp32.h>

Memory::Memory(const char* nameOfProcess)
{
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32); // We have to set size before using it

	const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // Gives us all processes in the system snapshot

	while (Process32Next(snapshot, &processEntry)) // Loop until not found an process
	{
		if (!strcmp(nameOfProcess, processEntry.szExeFile)) // If we find our searched file
		{
			// Settings variables
			this->processId = processEntry.th32ProcessID;
			this->processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, this->processId);

			break;
		}
	}

	// Closing snapshot that we just create
	if (snapshot)
	{
		CloseHandle(snapshot);
	}
}

Memory::~Memory()
{
	if (this->processHandle)
	{
		CloseHandle(this->processHandle);
	}
}

DWORD Memory::GetProcessId()
{
	return this->processId;
}
HANDLE Memory::GetProcessHandle()
{
	return this->processHandle;
}

uintptr_t Memory::GetModuleAddress(const char* moduleName)
{
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32); // We have to set size before using it

	const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->processId); // Creating snapshot

	uintptr_t result = 0;

	while (Module32Next(snapshot, &entry))
	{
		if (!strcmp(moduleName, entry.szExePath))
		{
			result = (uintptr_t)(entry.modBaseAddr);
			break;
		}
	}


	// Closing snapshot that we just create
	if (snapshot)
	{
		CloseHandle(snapshot);
	}

	return result;
}

template <typename T>
T Memory::ReadMemory(uintptr_t address)
{
	T value;

	ReadProcessMemory(this->processHandle, static_cast<LPCVOID>(address), &value, sizeof(T), NULL);

	return value;
}

template <typename T>
bool Memory::WriteMemory(uintptr_t address, T value)
{
	return WriteProcessMemory(this->processHandle, static_cast<LPCVOID>(address), &value, sizeof(T), NULL);
}