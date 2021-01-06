#pragma once
#include <string>
using namespace std;

//���� ��
class Process
{
public:
	int id;				//���̱��
	string name;		//��������
	int memory;			//�洢�ڴ��С����MΪ��λ
	int lastTime;		//����ʱ�䣬�Ժ���Ϊ��λ

	Process();
	~Process();
	Process(int id, string name, int memory, int lastTime) :id(id), name(name), memory(memory), lastTime(lastTime) {}

	Process(const Process& tmp) {
		this->id = tmp.id;
		this->name = tmp.name;
		this->memory = tmp.memory;
		this->lastTime = tmp.lastTime;
	}
	bool operator==(const Process& p) {
		return id == p.id && name == p.name && memory == p.memory && lastTime == p.lastTime;
	}
};

Process::Process()
{
}

Process::~Process()
{
}