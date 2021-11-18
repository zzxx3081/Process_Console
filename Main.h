#ifndef __Main_H_
#define __Main_H_

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

void Process_Console(void);
void Command_list(void);
void Command_Execution(string command);
BOOL isNumber(const string& str);

#endif