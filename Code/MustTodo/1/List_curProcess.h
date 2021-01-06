#pragma once
#include <iostream>
#include "Process.h"
#include "SighalNode.h"
using namespace std;

/*
	��ǰ��������
*/
class List_curProcess
{
public:
	List_curProcess();
	~List_curProcess();
	SighalNode* head;		//ͷ�ڵ�

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
/* �����ڴ��ʹ�����Խ��̽������� */
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
		cout << "����ID: " << p->pro.id << "\n�������� : " << p->pro.name
			<< "\n����ʱ�䣺 " << p->pro.lastTime   << " ��"
			<< "\n�ڴ�ռ�ã�  " << p->pro.memory << "  Mb\n\n";
		p = p->next;
	}
}
