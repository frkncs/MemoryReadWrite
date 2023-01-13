#pragma once
#include <Windows.h>
#include <iostream>

class Memory
{
private:
	DWORD processId = 0; // Id of process
	HANDLE processHandle = NULL; // Handle of process

public:
	Memory(const char* nameOfProcess);
	~Memory();

	DWORD GetProcessId();
	HANDLE GetProcessHandle();

	uintptr_t GetModuleAddress(const char* moduleName);

	template <typename T>
	T ReadMemory(uintptr_t address);

	template <typename T>
	bool WriteMemory(uintptr_t address, T value);
};