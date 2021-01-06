/*
 * @Author            : IQIUM
 * @Github            : https://github.com/IQIUM
 * @Date              : 2021-01-03 15:41:01
 * @LastEditTime      : 2021-01-06 19:27:41
 * @FilePath          : \Code\MustTodo\8\src\publicMethod.h
 * @Discription       : 
 * @Copyright 2021 IQIUM
 */
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/time.h>

using namespace std;

/**
 * @description: ��ȡ50000�� ���ݵ�������
 */
void readFile(string filename, int arr[])
{
    ifstream in(filename, ios::in);
    if (in.fail())
    {
        cout << "[Error] " + filename + " �ļ���ʧ��" << endl;
        exit(0);
    }
    string con;
    getline(in, con, '\n');
    string num;
    stringstream ss(con);
    int count = 0;
    while (getline(ss, num, ' '))
    {
        arr[count++] = atoi(num.c_str());
    }
}

/**
 * @description: ���ź�����������
 * @param {string} filename
 * @param {int} arr
 */
void writeFile(string filename, int arr[])
{
    stringstream ss;
    ofstream out(filename, ios::out | ios::trunc);
    if (out.fail())
    {
        cout << "[Error]  �ļ�����ʧ��!" << endl;
        exit(0);
    }
    string res = "";
    string tmp;
    for (int i = 0; i < 50000; i++)
    {
        ss << arr[i];
        ss >> tmp;
        res += tmp + " ";
        ss.clear();
        tmp = "";
    }
    res += "\n";
    out << res;
    out.close();
}

/**
 * @description: ����ϵͳʱ��
 */
long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/**
 * @description: ��time.txt�ļ��з�������ʱ��
 */
void writeTime(string sortname, vector<int> times)
{
    string filename = "../../Res/time.txt";
    ofstream out(filename, ios::app);
    if (out.fail())
    {
        cout << "[Error] �ļ���ʧ�ܣ�" << endl;
        exit(0);
    }
    out << sortname << "��  \n";
    int sum = 0;
    for (int i = 0; i < times.size(); i++)
    {
        out << "\t�� " << i + 1 << " ����������ʱ��Ϊ��  " << times[i]
            << " ����\n";
        sum += times[i];
    }
    out << "ƽ����ʱ��  " << sum / (float)10 << " ����\n\n";
    out.close();
}
