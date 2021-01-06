#pragma once
#include "Process.h"

/* 单链表节点类 */
class SighalNode {
public:
	Process pro;
	SighalNode* next;
	SighalNode() : next(NULL) {}
	void setProcess(const Process& tmp) {
		pro = tmp;
	}
};