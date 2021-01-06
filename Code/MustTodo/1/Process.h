#pragma once
#include <string>
using namespace std;

//进程 类
class Process
{
public:
	int id;				//进程标号
	string name;		//进程名称
	int memory;			//存储内存大小，以M为单位
	int lastTime;		//持续时间，以毫秒为单位

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