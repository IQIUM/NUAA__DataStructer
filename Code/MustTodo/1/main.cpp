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

vector<Process> pros;	//�������еĽ���

void menu();
long getCurrentTime();

bool AdjustPurview()//��������Ȩ��
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
	Process curPro;	//��ǰ����
	TCHAR szProcessName[MAX_PATH];//������Ž�����
	AdjustPurview();
	//ȡ�ý��̵ľ��
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
	FILETIME starttime, exittime, ipker, ipuser;//������¼����ʱ�䣬����ʱ�䣬�����ں���ģʽ�����ĵ�ʱ�䣬�������û�ģʽ�����ĵ�ʱ��
	LPSYSTEMTIME lpSystemTime = new SYSTEMTIME;//������filetimeת��Ϊsystemtime[systemtime�������˿���]
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));//��ȡ����
	GetModuleFileNameEx(hProcess, NULL, szProcessName, MAX_PATH);//��ȡ������
	GetProcessTimes(hProcess, &starttime, &exittime, &ipker, &ipuser);//��ȡ����ʱ��
	curPro.id = processID;
	char c_char[MAX_PATH];
	sprintf(c_char, "%S", szProcessName);
	curPro.name = c_char;
	curPro.memory = pmc.WorkingSetSize / 1024 / 1024;
	FileTimeToSystemTime(&starttime, lpSystemTime);
	lpSystemTime->wHour = (lpSystemTime->wHour + 8) % 24;//��UTCʱ�仯Ϊ����ʱ�䣬����ֻת����Сʱ���������Ҫ����ת���ꡢ�¡���
	DWORD dwBeginTime =
		lpSystemTime->wHour * 60 * 60 * 1000
		+ lpSystemTime->wMinute * 60 * 1000
		+ lpSystemTime->wSecond * 1000
		+ lpSystemTime->wMilliseconds;
	curPro.lastTime = (dwEndTime - dwBeginTime) / 1000;
	CloseHandle(hProcess);
	pros.push_back(curPro);
}

/* ��ȡ�ڴ��еĽ��̲�����pros�� */
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

	//ע���˴�Ϊ��ǰ�ź���Ľ���
	sort(pros.begin(), pros.end(), myCompare);
}

int main(void) {
	int num = 0;
	while (1)
	{
		menu();
		cout << "\n\t�����������������ţ�  ";
		cin >> num;
		switch (num)
		{
		case 1: {
				while (true)
				{
					int start = getCurrentTime();

					system("cls");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					cout << "                ��ǰϵͳʱ��Ϊ��    ";
					SYSTEMTIME sys;
					GetLocalTime(&sys);
					printf("%4d/%02d/%02d %02d:%02d:%02d\n", sys.wYear, sys.wMonth, sys.wDay,
						sys.wHour, sys.wMinute, sys.wSecond);
					cout << endl;
					cout << "                      ��������˳���                  " << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
						FOREGROUND_GREEN | FOREGROUND_BLUE);
					pros.clear();
					readProcess();
					List_curProcess* list = new List_curProcess();

					//ע���˴���ֻ����10�����̣�����չ��ÿ�����
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
					cout << "                ��ǰϵͳʱ��Ϊ��    ";
					SYSTEMTIME sys;
					GetLocalTime(&sys);
					printf("%4d/%02d/%02d %02d:%02d:%02d\n", sys.wYear, sys.wMonth, sys.wDay,
						sys.wHour, sys.wMinute, sys.wSecond);
					cout << endl;
					cout << "                      ��������˳���                  " << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
						FOREGROUND_GREEN | FOREGROUND_BLUE);
					vector<Process> tmp;
					for (size_t i = 0; i < pros.size(); i++)
					{
						tmp.push_back(pros[i]);
					}
					pros.clear();
					readProcess();
					//�Ƚ�����
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
				cout << "\n\n\t ллʹ�ã�" << endl;
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
	cout << "**            ��ӭʹ�ý�����ʾϵͳ          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**            [1] ��ʾ���ڽ��еĽ���        **" << endl;
	cout << "**            [2] չʾ�Ѿ������Ľ���        **" << endl;
	cout << "**            [3] �˳�                      **" << endl;
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