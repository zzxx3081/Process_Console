## 자기주도연구I
Process_Console.exe 프로그램의 소스코드입니다.

### Process_Console 설명
Process_Console은 마이크로소프트에서 제공하는 Process Explorer의 일부 기능을 구현한 C++ 기반 콘솔프로그램입니다. Process_Console은 다음과 같은 기능을 포함하고 있습니다.

1. Process Kill(PsKill) : 특정 프로세스를 종료하는 기능
2. Process List(PsList) : 현재 실행중인 모든 프로세스의 정보를 출력하는 기능
3. Process Suspend(PsSuspend) : 특정 프로세스를 일시 중단하는 기능
4. Process Resume(PsResume) : 일시 중단된 프로세스를 다시 실행시키는 기능
5. Process Find(PsFind) : 특정 프로세스의 이름과 ID를 출력하는 기능
6. Exit : 나가기/종료 기능
7. -t : 프로그램 기능 설명서

### Main.cpp
Process_Console 프로그램의 메인함수(진입점)입니다.

```c++
int main(void)
{
	Process_Console();
	return 0;
}
```

## 소스 설명 및 콘솔 화면

### Main_Function.cpp
사용자가 프로그램을 쉽게 사용할 수 있도록 해주는 인터페이스 함수들의 소스입니다.

* Process_Console : 프로그램을 시작하는 함수
```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료):
```

* Command_list : 프로그램 기능 설명서 출력 함수(-t)
```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료): -t

★ 명령어 목록 ★

1. 현재 실행중인 모든 프로세스 출력: PsList
2. 특정 프로세스 종료: PsKill
3. 특정 프로세스 일시중단: PsSuspend
4. 특정 프로세스 일시중단 해제: PsResume
5. 특정 프로세스 찾기: PsFind
6. 프로그램 종료: Exit

※ 모든 명령어는 대소문자 구분 없이 입력 가능
```

* Command_Execution : 명령어 입력시 해당 기능창으로 전환하는 함수
```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료): PsList or PsKill or PsSuspend or PsResume or PsFind or Exit
```

* isNumber : 입력한 문자열이 숫자인지 검사하는 함수(프로세스의 ID를 판별)
```c++
BOOL isNumber(const string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return FALSE;
	}
	return TRUE;
}
```


### PsKill.cpp
특정 프로세스의 이름 또는 ID를 입력하면 해당 프로세스를 종료시키는 PsKill 함수의 소스입니다.

```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료): pskill
종료할 프로세스의 이름 또는 ID를 입력하세요(종료: exit): 이름 or ID
```

### PsList.cpp
현재 실행중인 모든 프로세스의 이름과 ID를 출력하는 PsList 함수의 소스입니다.

```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료): pslist
```

### PsSuspend.cpp
특정 프로세스의 이름 또는 ID를 입력하면 해당 프로세스를 일시 중단시키는 PsSuspend 함수의 소스입니다.

```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료): pssuspend
중단할 프로세스의 이름 또는 ID를 입력하세요(종료: exit): 이름 or ID
```

### PsResume.cpp
일시 중단된 프로세스의 이름 또는 ID를 입력하면 해당 프로세스를 다시 실행시키는 PsResume 함수의 소스입니다.

```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료): psresume
일시중지된 프로세스의 이름 또는 ID를 입력하세요(종료: exit): 이름 or ID
```

### PsFind.cpp
특정 프로세스의 이름 또는 ID를 입력하면 해당 프로세스의 이름과 ID를 모두 출력하는 기능입니다. 주로 프로세스 ID를 찾을 때 사용합니다.

```
/* 콘솔 화면 */

명령어 입력 (설명: -t , exit: 종료): psfind
찾을 프로세스의 이름 또는 ID를 입력하세요(종료: exit): 이름 or ID
```
