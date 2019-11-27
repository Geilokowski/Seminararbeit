#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

DWORD getProcID(const wchar_t* proc);
DWORD getModuleBaseAdress(DWORD procID, const wchar_t* moduleName);