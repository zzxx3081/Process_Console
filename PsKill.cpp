#include "Main.h"
#include "PsKill.h"

BOOL PsKill(void)
{
	DWORD Return = FALSE;
	string name;

	cout << endl;
	cout << "������ ���μ����� �̸� �Ǵ� ID�� �Է��ϼ���(����: exit): ";
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

	ProcessName.MakeLower(); // ��� ���ڿ��� �ҹ��ڷ�

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // ���� �������� ���μ������� ������ �˱� ���� �ü������ �����ϱ� ���� ����

	if (hProcessSnap == INVALID_HANDLE_VALUE) // ���� ������ ���ҽ� ��û�� �����Ѵٸ�,
		return (DWORD)INVALID_HANDLE_VALUE; // ��ȿ���� ���� �ڵ鰪 ��ȯ (-1)

	pe32.dwSize = sizeof(PROCESSENTRY32); // ����ü�� ũ�� �ʱ�ȭ

	if (Process32First(hProcessSnap, &pe32)) // ���μ����� ������ ó�� �����ϴ� �Լ�
	{
		DWORD Code = 1; // ���α׷� ���� ������ 0���� �ٲ�
		DWORD dwPriorityClass;

		do {
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); // ���μ����� �ڵ��� ��ȯ(���μ����� ���� ������ ����)
			dwPriorityClass = GetPriorityClass(hProcess); // �켱���� Ŭ���� ��ȯ

			CString Temp = pe32.szExeFile; // ���μ����� ���������� �̸�
			Temp.MakeLower(); // ��� ���ڿ��� �ҹ��ڷ�

			DWORD PID = pe32.th32ProcessID;

			if (Temp == ProcessName || PID == ProcessID)
			{
				if (TerminateProcess(hProcess, 0)) // ����� ���μ����� �����ڵ� 0�� ������ �ǹ�
				{
					cout << "\n==============================================\n\n";
					GetExitCodeProcess(hProcess, &Code); // ������� �˻� �Լ� ���������� ����� Code�� 0�� ����
					_tprintf(TEXT("     %s (%d)"), pe32.szExeFile, pe32.th32ProcessID);
					cout << " ���� ����\n";
					cout << "\n==============================================\n";
				}
				else
					return GetLastError();
			}
			CloseHandle(hProcess); // �ش� ���μ����� ���� �ݳ�
		} while (Process32Next(hProcessSnap, &pe32)); // ���� ���μ����� ���� ����

		if (Code == 0)
			Return = TRUE;
		else
			cout << "�ش� ���μ����� ���������� �ʰų� ������ �� �����ϴ�." << endl << endl;
	}
	else
		Return = FALSE;

	CloseHandle(hProcessSnap); // ������ �ڵ� �ݳ�

	return Return;
}
