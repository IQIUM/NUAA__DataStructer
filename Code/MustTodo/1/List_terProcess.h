#pragma once
#include "doubleNode.h"
#include <math.h>

//�������� ����
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
		cout << "����ID: " << p->pro.id << "\n�������� : " << p->pro.name
			<< "\n����ʱ�䣺 " << abs(p->pro.lastTime) << " ��"
			<< "\n�ڴ�ռ�ã�  " << p->pro.memory << "  Mb\n\n";
		p = p->next;
		count++;

		//ע�⣺Ϊ�˷��㿴�仯��ֻ����10����ʾ
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
