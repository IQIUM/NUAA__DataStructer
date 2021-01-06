#ifndef READFILE_H
#define READFILE_H

#pragma once
#pragma execution_character_set("utf-8")

#include "Person.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

/**
 * 文件结构：
 *   1. 以 # 相隔，分隔两代
 *   2.每一行代表一个人，一行数据分别是：姓名，性别（string），出生日期（以0补齐）
 *      ，户籍地址（string），是否结婚（1/0），是否健在（1/0），
 *      若不健在，去世日期，若健在，dieDay = 00000000;
 *      孩子数
 */

inline void readFile(Person *&root) {
    ifstream in("E:\\\DataStructure\\CourseDesign\\CouseDesign\\Summary\\MustTodo\\3\\FamilyTree\\familytreeUTF-8.txt", ios::in);
    if (in.fail()) {
        cout << "[Error] File Open Failed" << endl;
        exit(0);
    }

    string conArr[8];
    string content;
    stringstream ss;

    int generation = 1;
    queue<Person *> que;
    while (getline(in, content, '\n')) {
        if (content.size() == 1 && content[0] == '#') {
            generation++;
            continue;
        }
        Person *parent;
        if (que.empty()) {
            parent = NULL;
        } else {
            parent = que.front();
        }

        ss << content;
        string tmp;
        int count = 0;
        while (getline(ss, tmp, ' ')) {
            conArr[count++] = tmp;
        }
        ss.clear();
        ss.str("");
        content = "";

        Person *person = new Person();
        person->name = conArr[0];
        person->sex = conArr[1];
        person->birthday.year = atoi(conArr[2].substr(0, 4).c_str());
        person->birthday.month = atoi(conArr[2].substr(4, 2).c_str());
        person->birthday.day = atoi(conArr[2].substr(6, 2).c_str());
        person->address = conArr[3];
        person->marriage = conArr[4][0] - '0';
        person->live = conArr[5][0] - '0';
        if (!person->live) {
            person->dieDay.year = atoi(conArr[6].substr(0, 4).c_str());
            person->dieDay.month = atoi(conArr[6].substr(4, 2).c_str());
            person->dieDay.day = atoi(conArr[6].substr(6, 2).c_str());
        } else {
            person->dieDay.year = 0;
            person->dieDay.month = 0;
            person->dieDay.day = 0;
        }
        person->count = conArr[7][0] - '0';
        person->generation = generation;
        person->size = 0;

        if (person->generation == 1) {
            root = person;
            person->parent = parent;
            que.push(person);
        } else {
            person->parent = parent;
            parent->children[parent->size++] = person;
            if (parent->size == parent->count) {
                que.pop();
            }
            if (person->count != 0) {
                que.push(person);
            }
        }
    }
    in.close();
}

#endif // READFILE_H
