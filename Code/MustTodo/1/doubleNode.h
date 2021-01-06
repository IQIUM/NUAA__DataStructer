#pragma once
#include "Process.h"

/* 循环链表节点类 */
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