#include "ProcessHelper.h"

int main()
{
	SetConsoleTitleA("External Cheat");
	const wchar_t* exeName = L"GameSim.exe";

	DWORD procID = getProcID(exeName);

	if (!procID) {
		std::cout << "Es wird auf den Prozes gewartet... \n";
		while (!procID) {
			procID = getProcID(exeName);
			Sleep(250);
		}
	}

	HANDLE hProcHandle = OpenProcess(PROCESS_ALL_ACCESS, false, procID);
	DWORD baseAdress = getModuleBaseAdress(procID, exeName);

	DWORD ptrHealth = baseAdress + 0x5018;

	std::cout << "Handle zum Prozess offen\n\n";
	std::cout << std::hex << "Adresse der Lebensvariable: 0x" << ptrHealth << "\n\n";

	while (true)
	{
		int currentHealth;
		ReadProcessMemory(hProcHandle, (BYTE*)ptrHealth, &currentHealth, sizeof(currentHealth), nullptr);
		std::cout << std::dec << "Derzeitige Leben: " << currentHealth << "\n";

		int newHealth = 0;
		std::cout << "Bitte gebe die neue Anzahl an Leben ein: ";
		std::cin >> newHealth;
		WriteProcessMemory(hProcHandle, (BYTE*)ptrHealth, (BYTE*)&newHealth, sizeof(newHealth), nullptr);
		std::cout << "\n";
	}
}
