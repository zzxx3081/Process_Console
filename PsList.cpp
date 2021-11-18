#include "PsList.h"

BOOL PsList(void)
{
	HANDLE hProcessSnap = NULL;
	DWORD Return = FALSE;
	PROCESSENTRY32 pe32 = { 0 };

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return (DWORD)INVALID_HANDLE_VALUE;

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32))
	{
		int len = 0;
		cout << "===============================================================" << endl;
		cout << "       Process Name                        Process ID" << endl;
		cout << "===============================================================" << endl;

		do
		{
			_tprintf(TEXT("     %s"), pe32.szExeFile);
			len = 37 - wcslen(pe32.szExeFile);

			for (int i = 0; i < len; i++)
				cout << ' ';

			_tprintf(TEXT("%7d\n"), pe32.th32ProcessID);

		} while (Process32Next(hProcessSnap, &pe32));
		Return = TRUE;
	}

	CloseHandle(hProcessSnap);

	cout << endl << endl;
	return Return;
}