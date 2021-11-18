#ifndef __PsSuspend_H_
#define __PsSuspend_H_

#include <iostream>
#include <Windows.h>
#include <Tlhelp32.h>
#include <tchar.h>
#include <wchar.h>
#include <string>
#include <atlstr.h>

using namespace std;

BOOL PsSuspend(void);
void Suspend(DWORD processId);

#endif