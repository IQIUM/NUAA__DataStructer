#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;
#include "Date.h"

const int MAX = 10;

//Person 类
class Person {
  public:
    int generation; //代数
    string name;    //姓名
    string sex;     //性别
    Date birthday;  //出生日期
    bool marriage;  //婚否
    string address; //地址
    bool live;      //健在
    Date dieDay;    //死亡日期

    int x;      //坐标
    int y;

    int count;             //孩子数量
    int size;              //孩子存储过程变量
    Person *children[MAX]; //指向孩子数量的指针
    Person *parent;

    Person() {}
};

#endif // PERSON_H
