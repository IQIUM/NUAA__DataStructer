#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <windows.h>
#include <psapi.h>
#include <windows.h>
#include <conio.h>
#include "List_curProcess.h"
#include "Process.h"
#include "SighalNode.h"
#include "doubleNode.h"
#include "List_terProcess.h"

using namespace std;
#pragma comment(lib, "psapi.lib")

vector<Process> pros;	//保存所有的进程

void menu();
long getCurrentTime();

bool AdjustPurview()//提升进程权限
{
	TOKEN_PRIVILEGES TokenPrivileges;
	BOOL bRet;
	HANDLE hToken;

	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &TokenPrivileges.Privileges[0].Luid);
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

	TokenPrivileges.PrivilegeCount = 1;
	TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	bRet = AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL);

	CloseHandle(hToken);
	return bRet == TRUE;
}

bool myCompare(Process p1, Process p2) {
	return p1.memory > p2.memory;
}

bool myCompare2(Process p1, Process p2) {
	return p1.id == p2.id && p1.name == p2.name;
}

void PrintMemoryInfo(DWORD processID) {
	Process curPro;	//当前进程
	TCHAR szProcessName[MAX_PATH];//用来存放进程名
	AdjustPurview();
	//取得进程的句柄
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	LPSYSTEMTIME endTime = new SYSTEMTIME;
	::GetSystemTime(endTime);
	endTime->wHour = (endTime->wHour + 8) % 24;
	DWORD dwEndTime =
		endTime->wHour * 60 * 60 * 1000
		+ endTime->wMinute * 60 * 1000
		+ endTime->wSecond * 1000
		+ endTime->wMilliseconds;
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
		return;
	FILETIME starttime, exittime, ipker, ipuser;//用来记录启动时间，结束时间，进程在核心模式下消耗的时间，进程在用户模式下消耗的时间
	LPSYSTEMTIME lpSystemTime = new SYSTEMTIME;//用来将filetime转换为systemtime[systemtime可以让人看懂]
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));//获取进程
	GetModuleFileNameEx(hProcess, NULL, szProcessName, MAX_PATH);//获取进程名
	GetProcessTimes(hProcess, &starttime, &exittime, &ipker, &ipuser);//获取进程时间
	curPro.id = processID;
	char c_char[MAX_PATH];
	sprintf(c_char, "%S", szProcessName);
	curPro.name = c_char;
	curPro.memory = pmc.WorkingSetSize / 1024 / 1024;
	FileTimeToSystemTime(&starttime, lpSystemTime);
	lpSystemTime->wHour = (lpSystemTime->wHour + 8) % 24;//将UTC时间化为北京时间，这里只转化了小时，如果有需要可以转化年、月、日
	DWORD dwBeginTime =
		lpSystemTime->wHour * 60 * 60 * 1000
		+ lpSystemTime->wMinute * 60 * 1000
		+ lpSystemTime->wSecond * 1000
		+ lpSystemTime->wMilliseconds;
	curPro.lastTime = (dwEndTime - dwBeginTime) / 1000;
	CloseHandle(hProcess);
	pros.push_back(curPro);
}

/* 读取内存中的进程并存入pros中 */
void readProcess() {
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		return;
	}
	cProcesses = cbNeeded / sizeof(DWORD);

	for (i = 0; i < cProcesses; i++) {
		PrintMemoryInfo(aProcesses[i]);
	}

	//注：此处为提前排好序的进程
	sort(pros.begin(), pros.end(), myCompare);
}

int main(void) {
	int num = 0;
	while (1)
	{
		menu();
		cout << "\n\t请输入你想操作的序号：  ";
		cin >> num;
		switch (num)
		{
		case 1: {
				while (true)
				{
					int start = getCurrentTime();

					system("cls");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					cout << "                当前系统时间为：    ";
					SYSTEMTIME sys;
					GetLocalTime(&sys);
					printf("%4d/%02d/%02d %02d:%02d:%02d\n", sys.wYear, sys.wMonth, sys.wDay,
						sys.wHour, sys.wMinute, sys.wSecond);
					cout << endl;
					cout << "                      按任意键退出！                  " << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
						FOREGROUND_GREEN | FOREGROUND_BLUE);
					pros.clear();
					readProcess();
					List_curProcess* list = new List_curProcess();

					//注：此处我只放了10个进程，便于展现每秒情况
					for (unsigned int i = 0; i < 10; i++)
					{
						list->insertProcess(pros[i]);
					}
					list->showList();

					int  end = getCurrentTime();
					while ((end - start) < 1000 )
					{
						  end = getCurrentTime();
					}
					delete list;
					if (_kbhit()) {
						_getch();
						break;
					}
				}
				system("cls");
				break;
			}
		case 2:
			{
				List_terProcess* list = new List_terProcess();
				while (true)
				{
					int start = getCurrentTime();
					
					system("cls");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					cout << "                当前系统时间为：    ";
					SYSTEMTIME sys;
					GetLocalTime(&sys);
					printf("%4d/%02d/%02d %02d:%02d:%02d\n", sys.wYear, sys.wMonth, sys.wDay,
						sys.wHour, sys.wMinute, sys.wSecond);
					cout << endl;
					cout << "                      按任意键退出！                  " << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
						FOREGROUND_GREEN | FOREGROUND_BLUE);
					vector<Process> tmp;
					for (size_t i = 0; i < pros.size(); i++)
					{
						tmp.push_back(pros[i]);
					}
					pros.clear();
					readProcess();
					//比较两者
					for (size_t i = 0; i < tmp.size(); i++)
					{
						bool flag = false;
						for (size_t j = 0; j < pros.size(); j++)
						{
							if (myCompare2(tmp[i], pros[j])) {
								flag = true;
								break;
							}
						}
						if (!flag) {
							list->insertProcess(tmp[i]);
						}
					}
                    for (int i = 0; i < list->length; ++i)
					{
                        for (int j = 0; j < pros.size(); ++j) {
                           	if(pros[j].name == list->sumName[i]) {
								list->erase(pros[j].name);
								break;
                           	}
                        }
                    }
					list->showList();
					int  end = getCurrentTime();
					while ((end - start) < 1000)
					{
						end = getCurrentTime();
					}
					if (_kbhit()) {
						_getch();
						delete list;
						break;
					}
				}
				system("cls");
				break;
			}
		case 3: {
				cout << "\n\n\t 谢谢使用！" << endl;
				exit(0);
			}
		default:
			system("cls");
			break;
		}
	}

	return 0;
}

void menu() {
	cout << "**********************************************" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**            欢迎使用进程显示系统          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**            [1] 显示正在进行的进程        **" << endl;
	cout << "**            [2] 展示已经结束的进程        **" << endl;
	cout << "**            [3] 退出                      **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**********************************************" << endl;
}


long getCurrentTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	return ((st.wHour * 60 + st.wMinute) * 60 + st.wSecond) * 1000 + st.wMilliseconds;
}