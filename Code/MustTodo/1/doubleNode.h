#pragma once
#include "Process.h"

/* ѭ������ڵ��� */
class DoubleNode {
public:
	Process pro;
	DoubleNode* next;
	DoubleNode* pre;
	DoubleNode() : next(NULL),pre(NULL) {}
	void setProcess(const Process& tmp) {
		pro = tmp;
	}
};