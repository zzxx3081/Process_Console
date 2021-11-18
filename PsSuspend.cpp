#include "Main.h"
#include "PsSuspend.h"

BOOL PsSuspend(void)
{
	DWORD Return = FALSE;
	string name;

	cout << endl;
	cout << "�ߴ��� ���μ����� �̸� �Ǵ� ID�� �Է��ϼ���(����: exit): ";
	getline(cin, name);

	CString ProcessName(name.c_str());
	ProcessName.MakeLower();

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
				Suspend(PID);
				cout << "\n==============================================\n\n";

				_tprintf(TEXT("        %s (%d)"), pe32.szExeFile, pe32.th32ProcessID);
				cout << " �Ͻ� ����\n";

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

	return Return;
}

void Suspend(DWORD processId)
{
	HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	THREADENTRY32 threadEntry;
	threadEntry.dwSize = sizeof(THREADENTRY32);

	Thread32First(hThreadSnapshot, &threadEntry);

	do
	{
		if (threadEntry.th32OwnerProcessID == processId)
		{
			HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, threadEntry.th32ThreadID);

			SuspendThread(hThread);
			CloseHandle(hThread);
		}
	} while (Thread32Next(hThreadSnapshot, &threadEntry));

	CloseHandle(hThreadSnapshot);
}