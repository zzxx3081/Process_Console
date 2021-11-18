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
		cout << "��ɾ� �Է� (����: -t , exit: ����): ";
		getline(cin, command);
		Command_Execution(command);

	} while (command != "Exit");
}

void Command_list(void)
{
	cout << endl << endl;
	cout << "�� ��ɾ� ��� ��\n" << endl << endl;
	cout << "1. ���� �������� ��� ���μ��� ���: PsList\n" << endl;
	cout << "2. Ư�� ���μ��� ����: PsKill\n" << endl;
	cout << "3. Ư�� ���μ��� �Ͻ��ߴ�: PsSuspend\n" << endl;
	cout << "4. Ư�� ���μ��� �Ͻ��ߴ� ����: PsResume\n" << endl;
	cout << "5. Ư�� ���μ��� ã��: PsFind\n" << endl;
	cout << "6. ���α׷� ����: Exit\n" << endl << endl;
	cout << "�� ��� ��ɾ�� ��ҹ��� ���� ���� �Է� ����" << endl << endl << endl;
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
			cout << "���� ��û ����" << endl;
		cout << endl;
	}

	if (Command == "pslist")
		PsList();

	if (Command == "pssuspend")
	{
		BOOL VALUE = PsSuspend();

		if (VALUE == (DWORD)INVALID_HANDLE_VALUE)
			cout << "���� ��û ����" << endl;
		cout << endl;
	}

	if (Command == "psresume")
	{
		BOOL VALUE = PsResume();

		if (VALUE == (DWORD)INVALID_HANDLE_VALUE)
			cout << "���� ��û ����" << endl;
		cout << endl;
	}

	if (Command == "psfind")
	{
		BOOL VALUE = PsFind();

		if (VALUE == (DWORD)INVALID_HANDLE_VALUE)
			cout << "���� ��û ����" << endl;
		cout << endl;
	}

	if (Command == "exit")
		exit(0);
}

BOOL isNumber(const string& str) // ���ڿ� ���� �˻� �Լ�
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return FALSE;
	}
	return TRUE;
}