#include "ProcessHelper.h"

DWORD getProcID(const wchar_t* proc) {
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap != INVALID_HANDLE_VALUE) {
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (!Process32First(hProcessSnap, &pe32)) {
			std::wcout << "Fehler beim Lesen des ersten Prozesses, Abbruch";
			CloseHandle(hProcessSnap);
			return 0;
		}

		do {
			if (!_wcsicmp(pe32.szExeFile, proc)) {
				std::wcout << "Prozess " << proc << " mit der PID " << pe32.th32ProcessID << " gefunden\n";
				CloseHandle(hProcessSnap);
				return pe32.th32ProcessID;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}
	else {
		std::wcout << "Fehler beim Erstellen eines Snapshots";
		CloseHandle(hProcessSnap);
	}

	CloseHandle(hProcessSnap);
	return 0;
}

DWORD getModuleBaseAdress(DWORD procID, const wchar_t* moduleName) {
	HANDLE hProcessSnap;
	MODULEENTRY32 me32;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
	if (hProcessSnap != INVALID_HANDLE_VALUE) {
		me32.dwSize = sizeof(MODULEENTRY32);

		if (!Module32First(hProcessSnap, &me32)) {
			std::wcout << "Fehler beim Lesen des ersten Modules";
			CloseHandle(hProcessSnap);
			return 0;
		}

		do {
			if (!_wcsicmp(me32.szModule, moduleName)) {
				std::wcout << "Hauptmodul des Prozesses " << me32.szModule << "[" << me32.th32ProcessID << "] mit der ID " << me32.th32ModuleID << " und Adresse " << std::hex << "0x" << me32.modBaseAddr << " gefunden\n";
				return (DWORD)me32.modBaseAddr;
			}
		} while (Module32Next(hProcessSnap, &me32));
	}
}