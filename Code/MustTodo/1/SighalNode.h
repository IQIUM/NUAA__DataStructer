#pragma once
#include "Process.h"

/* ������ڵ��� */
class SighalNode {
public:
	Process pro;
	SighalNode* next;
	SighalNode() : next(NULL) {}
	void setProcess(const Process& tmp) {
		pro = tmp;
	}
};