#include <iostream>
#include <windows.h>
#include <thread>

void gameLoop();
void checkLoop();

int health = 100;
int valueToRemove = 0;

int main()
{
	DWORD dwModuleBase = (DWORD)GetModuleHandle(NULL);
	DWORD dwHealthAdress = (DWORD)&health;

	SetConsoleTitle(L"Game Simulation");
    std::cout << "Wilkommen! \n\n";

	std::cout << std::hex << "Die Adresse von health ist: 0x" << dwHealthAdress << "\n";

	std::cout << "Die Adresse des Basismoduls ist: 0x" << dwModuleBase << "\n";
	std::cout << "Die Differenzt betraegt: 0x" << (dwHealthAdress - dwModuleBase) << "\n\n" << std::dec;

	std::thread t1(checkLoop);
	Sleep(100);
	gameLoop();
}

void checkLoop() {
	std::cout << "Anti-Cheat gestartet\n";
	while (true){
		int oldHealth = health;

		Sleep(100);

		if (oldHealth != health && (health != (oldHealth - valueToRemove))) {
			std::cout << "\n\nWARNUNG: Die Variable Health wurde von " << oldHealth << " auf " << health << " geandert\n";
		}
	}
}

void gameLoop() {
	while (true) {
		if (health <= 0) {
			std::cout << "Du waerst jetzt Tod (" << health << " LP" << "). Reset auf 100 Leben... " << "\n\n";
			health = 100;
		}
		else
		{
			std::cout << "Du hast jetzt noch " << health << " Lebenspunkte" << "\n\n";
		}

		std::cout << "Wieviele Lebenspunkte wollen sie entfernen? ";
		std::cin >> valueToRemove;

		health = health - valueToRemove;
	}
}
