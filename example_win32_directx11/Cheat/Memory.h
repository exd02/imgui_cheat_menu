#pragma once

#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>

namespace Memory {
	DWORD getProcessId(const wchar_t* procName);

	uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modName);

	uintptr_t findDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
}