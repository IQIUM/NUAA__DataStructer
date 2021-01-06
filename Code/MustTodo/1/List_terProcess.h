#pragma once
#include "doubleNode.h"
#include <math.h>

//结束进程 链表
class List_terProcess
{
public:
	List_terProcess();
	~List_terProcess();

	DoubleNode* head;
	void insertProcess(Process pro);
	void showList();

	bool erase(string name);

	string sumName[1000];
	int length;

};

List_terProcess::List_terProcess()
{
	head = new DoubleNode();
	length = 0;
}

List_terProcess::~List_terProcess()
{
}

inline void List_terProcess::insertProcess(Process pro)
{
	DoubleNode* p = head;
	while (p->next != NULL && p->next->pro.memory > pro.memory)
	{
		p = p->next;
	}
	DoubleNode* tmp = new DoubleNode();
	tmp->setProcess(pro);
	tmp->next = p->next;
	p->next = tmp;
	if (tmp->next != NULL) {
		tmp->next->pre = tmp;
	}
	tmp->pre = p;
	sumName[length++] = pro.name;
}

inline void List_terProcess::showList()
{
	int count = 0;
	DoubleNode* p = head->next;
	while (p != NULL)
	{
		cout << "进程ID: " << p->pro.id << "\n进程名称 : " << p->pro.name
			<< "\n持续时间： " << abs(p->pro.lastTime) << " 秒"
			<< "\n内存占用：  " << p->pro.memory << "  Mb\n\n";
		p = p->next;
		count++;

		//注意：为了方便看变化，只设置10个显示
		if (count == 10) {
			break;
		}
	}
}

inline bool List_terProcess::erase(string name) {
	DoubleNode* p = head;
	DoubleNode* q = p->next;
	while (q != NULL) {
		if (q->pro.name == name) {
			break;
		}
		p = q;
		q = q->next;
	}


	DoubleNode* next = q->next;
	if (next == NULL) {
		p->next = NULL;
	}
	else {
		p->next = next;
		next->pre = p;
	}
	delete q;

	int index = -1;
	for (int i = 0; i < length; ++i) {
		if (sumName[i] == name) {
			index = i;
			break;
		}
	}
    for (int i = index + 1; i < length; ++i) {
        sumName[i - 1] = sumName[i];        
    }
	length--;

	return true;

}
