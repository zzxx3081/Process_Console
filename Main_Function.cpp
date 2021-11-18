#include "Main.h"
#include "PsFind.h"
#include "PsKill.h"
#include "PsList.h"
#include "PsResume.h"
#include "PsSuspend.h"

void Process_Console(void)
{
	string command;

	do
	{
		cout << "명령어 입력 (설명: -t , exit: 종료): ";
		getline(cin, command);
		Command_Execution(command);

	} while (command != "Exit");
}

void Command_list(void)
{
	cout << endl << endl;
	cout << "★ 명령어 목록 ★\n" << endl << endl;
	cout << "1. 현재 실행중인 모든 프로세스 출력: PsList\n" << endl;
	cout << "2. 특정 프로세스 종료: PsKill\n" << endl;
	cout << "3. 특정 프로세스 일시중단: PsSuspend\n" << endl;
	cout << "4. 특정 프로세스 일시중단 해제: PsResume\n" << endl;
	cout << "5. 특정 프로세스 찾기: PsFind\n" << endl;
	cout << "6. 프로그램 종료: Exit\n" << endl << endl;
	cout << "※ 모든 명령어는 대소문자 구분 없이 입력 가능" << endl << endl << endl;
}

void Command_Execution(string command)
{
	CString Command(command.c_str());
	Command.MakeLower();

	if (Command == "-t")
		Command_list();

	if (Command == "pskill")
	{
		BOOL VALUE = PsKill();

		if (VALUE == (DWORD)INVALID_HANDLE_VALUE)
			cout << "권한 요청 실패" << endl;
		cout << endl;
	}

	if (Command == "pslist")
		PsList();

	if (Command == "pssuspend")
	{
		BOOL VALUE = PsSuspend();

		if (VALUE == (DWORD)INVALID_HANDLE_VALUE)
			cout << "권한 요청 실패" << endl;
		cout << endl;
	}

	if (Command == "psresume")
	{
		BOOL VALUE = PsResume();

		if (VALUE == (DWORD)INVALID_HANDLE_VALUE)
			cout << "권한 요청 실패" << endl;
		cout << endl;
	}

	if (Command == "psfind")
	{
		BOOL VALUE = PsFind();

		if (VALUE == (DWORD)INVALID_HANDLE_VALUE)
			cout << "권한 요청 실패" << endl;
		cout << endl;
	}

	if (Command == "exit")
		exit(0);
}

BOOL isNumber(const string& str) // 문자열 숫자 검사 함수
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return FALSE;
	}
	return TRUE;
}