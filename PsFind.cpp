#include "Main.h"
#include "PsFind.h"

BOOL PsFind(void)
{
	DWORD Return = FALSE;

	while (1)
	{
		string name;

		cout << endl;
		cout << "ã�� ���μ����� �̸� �Ǵ� ID�� �Է��ϼ���(����: exit): ";
		getline(cin, name);

		CString ProcessName(name.c_str());
		ProcessName.MakeLower(); // ��� ���ڿ��� �ҹ��ڷ�

		DWORD ProcessID = atol(name.c_str());

		if (ProcessName == "exit")
			return Return;

		if (!isNumber(name))
			ProcessID = -1;

		HANDLE hProcessSnap = NULL;

		PROCESSENTRY32 pe32 = { 0 }; // ���μ����� �������� ����� ����ü

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // ���� �������� ���μ������� ������ �˱� ���� �ü������ �����ϱ� ���� ����

		if (hProcessSnap == INVALID_HANDLE_VALUE) // ���� ������ ���ҽ� ��û�� �����Ѵٸ�,
			return (DWORD)INVALID_HANDLE_VALUE; // ��ȿ���� ���� �ڵ鰪 ��ȯ (-1)

		pe32.dwSize = sizeof(PROCESSENTRY32); // ����ü�� ũ�� �ʱ�ȭ

		if (Process32First(hProcessSnap, &pe32)) // ���μ����� ������ ó�� �����ϴ� �Լ�
		{
			DWORD Code = 1;
			do
			{
				HANDLE hProcess;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); // ���μ����� �ڵ��� ��ȯ(���μ����� ���� ������ ����)
				CString Temp = pe32.szExeFile; // ���μ����� ���������� �̸�
				Temp.MakeLower(); // ��� ���ڿ��� �ҹ��ڷ�

				DWORD PID = pe32.th32ProcessID;

				if (Temp == ProcessName || PID == ProcessID)
				{
					Code = 0;
					cout << "\n==============================================\n";

					_tprintf(TEXT("\n        Process Name: %s\n"), pe32.szExeFile);
					_tprintf(TEXT("        Process ID: %d\n"), pe32.th32ProcessID);

					cout << "\n==============================================\n";
				}

				CloseHandle(hProcess); // �ش� ���μ����� ���� �ݳ�

			} while (Process32Next(hProcessSnap, &pe32)); // ���� ���μ����� ���� ����

			if (Code == 0)
				Return = TRUE;
			else
				cout << "\n�ش� ���μ����� �������� �ʰų� ���� ���������� �ʽ��ϴ�." << endl;
		}
		else
			Return = FALSE;

		CloseHandle(hProcessSnap); // ������ �ڵ� �ݳ�
	}
	return Return;
}