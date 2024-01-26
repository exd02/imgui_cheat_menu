#include "Memory.h"

DWORD Memory::getProcessId(const wchar_t* processName) {
    DWORD processId = 0;

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "[ERROR] CreateToolhelp32Snapshot getProcessId\n";
        return 0;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);

    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "[ERROR] Process32First\n";

        CloseHandle(hProcessSnap);
        return 0;
    }

    do {
        // _tprintf(TEXT("Checking '%s' == '%s'\n"), pe32.szExeFile, processName);
        if (!_wcsicmp(pe32.szExeFile, processName)) {
            processId = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return processId;
}

uintptr_t Memory::getModuleBaseAddress(DWORD processId, const wchar_t* moduleName) {
    uintptr_t baseAddress = 0;

    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

    if (hModuleSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "[ERROR] CreateToolhelp32Snapshot getModuleBaseAddress\n";
        return NULL;
    }

    MODULEENTRY32 me32;
    me32.dwSize = sizeof(me32);

    if (!Module32First(hModuleSnap, &me32)) {
        std::cerr << "[ERROR] Module32First\n";
        CloseHandle(hModuleSnap);
        return NULL;
    }

    do {
        if (!_wcsicmp(me32.szModule, moduleName)) {
            baseAddress = (uintptr_t)me32.modBaseAddr;
            break;
        }
    } while (Module32Next(hModuleSnap, &me32));


    CloseHandle(hModuleSnap);
    return baseAddress;
}

uintptr_t Memory::findDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
    uintptr_t addr = ptr;

    for (unsigned int i = 0; i < offsets.size(); i++) {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }

    return addr;
}