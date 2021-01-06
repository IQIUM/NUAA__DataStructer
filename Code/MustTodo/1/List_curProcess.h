#pragma once
#include <iostream>
#include "Process.h"
#include "SighalNode.h"
using namespace std;

/*
	当前进程链表
*/
class List_curProcess
{
public:
	List_curProcess();
	~List_curProcess();
	SighalNode* head;		//头节点

	void insertProcess(Process pro);
	void showList();

};

List_curProcess::List_curProcess()
{
	head = new SighalNode();
}

List_curProcess::~List_curProcess()
{
	SighalNode* p = head;
	while (p->next != NULL)
	{
		SighalNode* tmp = p->next;
		p->next = tmp->next;
		delete tmp;
		tmp = NULL;
	}
	delete head;
}
/* 按照内存的使用量对进程进行排序 */
inline void List_curProcess::insertProcess(Process pro)
{
	SighalNode* p = head;
	while (p->next != NULL && p->next->pro.memory > pro.memory)
	{
		p = p->next;
	}
	SighalNode* tmp = new SighalNode();
	tmp->setProcess(pro);
	tmp->next = p->next;
	p->next = tmp;
}

inline void List_curProcess::showList()
{
	SighalNode* p = head->next;
	while (p != NULL)
	{
		cout << "进程ID: " << p->pro.id << "\n进程名称 : " << p->pro.name
			<< "\n持续时间： " << p->pro.lastTime   << " 秒"
			<< "\n内存占用：  " << p->pro.memory << "  Mb\n\n";
		p = p->next;
	}
}
