#include "Main.h"
#include "PsSuspend.h"

BOOL PsSuspend(void)
{
	DWORD Return = FALSE;
	string name;

	cout << endl;
	cout << "중단할 프로세스의 이름 또는 ID를 입력하세요(종료: exit): ";
	getline(cin, name);

	CString ProcessName(name.c_str());
	ProcessName.MakeLower();

	DWORD ProcessID = atol(name.c_str());

	if (ProcessName == "exit")
		return Return;

	if (!isNumber(name))
		ProcessID = -1;

	HANDLE hProcessSnap = NULL;

	PROCESSENTRY32 pe32 = { 0 }; // 프로세스의 정보들이 담겨질 구조체

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 현재 실행중인 프로세스들의 정보를 알기 위해 운영체제에게 접근하기 위한 수단

	if (hProcessSnap == INVALID_HANDLE_VALUE) // 만약 스냅샷 리소스 요청이 실패한다면,
		return (DWORD)INVALID_HANDLE_VALUE; // 유효하지 않은 핸들값 반환 (-1)

	pe32.dwSize = sizeof(PROCESSENTRY32); // 구조체의 크기 초기화

	if (Process32First(hProcessSnap, &pe32)) // 프로세스의 정보를 처음 추출하는 함수
	{
		DWORD Code = 1;
		do
		{
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); // 프로세스의 핸들을 반환(프로세스의 접근 권한을 얻음)
			CString Temp = pe32.szExeFile; // 프로세스의 실행파일의 이름
			Temp.MakeLower(); // 모든 문자열을 소문자로

			DWORD PID = pe32.th32ProcessID;

			if (Temp == ProcessName || PID == ProcessID)
			{
				Code = 0;
				Suspend(PID);
				cout << "\n==============================================\n\n";

				_tprintf(TEXT("        %s (%d)"), pe32.szExeFile, pe32.th32ProcessID);
				cout << " 일시 중지\n";

				cout << "\n==============================================\n";
			}
			CloseHandle(hProcess); // 해당 프로세스의 권한 반납

		} while (Process32Next(hProcessSnap, &pe32)); // 다음 프로세스의 정보 추출

		if (Code == 0)
			Return = TRUE;
		else
			cout << "\n해당 프로세스가 존재하지 않거나 현재 실행중이지 않습니다." << endl;
	}
	else
		Return = FALSE;

	CloseHandle(hProcessSnap); // 스냅샷 핸들 반납

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