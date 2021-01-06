/***
 * @Author         : IQIUM
 * @Date           : 2020-11-28 13:59:41
 * @LastEditors    : IQIUM
 * @LastEditTime   : 2020-11-29 01:04:40
 * @FilePath       : \CouseDesign\MustTodo\4\huffmanCode.cpp
 */
#include <cstdlib>
#include <string>
#include <map>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>

using namespace std;

class Node;

map<char, int> chFreq; //�洢ÿ���ַ���Ƶ��
Node *root = NULL;

//�ڵ���
class Node
{
public:
    char ch;
    int freq;
    string huffcode;
    Node *left;
    Node *right;

    Node() : left(NULL), right(NULL) {}

    friend ostream &operator<<(ostream &cout, Node &node);
};

ostream &operator<<(ostream &cout, Node &node)
{
    cout << node.ch << "  " << node.freq;
    return cout;
}

class Mycompare
{
public:
    bool operator()(const Node *node1, const Node *node2)
    {
        return node1->freq > node2->freq;
    }
};

/**
 * @description: ��ȡ�ļ���ͳ���ַ�����
 * @param {const char} *filename Ҫѹ�����ļ�
 */
int fileRead(const char *filename)
{
    ifstream in;
    in.open(filename, ios::in);
    if (in.fail())
    {
        cout << "�ļ���ʧ�ܣ�" << endl;
        exit(0);
    }
    string bufferInputStream; /* �ַ������뻺�壬һ���Է����ڴ� */
    int countTmp = 0;
    while (getline(in, bufferInputStream))
    {
        countTmp++;
        for (int i = 0; i < bufferInputStream.size(); i++)
        {
            if (chFreq.find(bufferInputStream[i]) != chFreq.end())
            {
                chFreq[bufferInputStream[i]]++;
            }
            else
            {
                chFreq[bufferInputStream[i]] = 1;
            }
        }
    }
    in.close();
    int count = 0;
    for (auto it = chFreq.begin(); it != chFreq.end(); ++it)
    {
        count += it->second;
    }
    return count;
}

/**
 * @description: ���ַ�����ͳ�ƽ������ Huffman.txt ��
 */
void outputHuffman()
{
    ofstream out("Huffman.txt", ios::out | ios::trunc);
    if (out.fail())
    {
        cout << "Huffman.txt �ļ�����ʧ�ܣ�" << endl;
        exit(0);
    }
    for (map<char, int>::iterator it = chFreq.begin(); it != chFreq.end(); ++it)
    {
        out << it->first << " " << it->second << "\n";
    }
}

/**
 * @description: ������������
 */
void createHuffmanTree()
{
    priority_queue<Node *, vector<Node *>, Mycompare> que;

    for (map<char, int>::iterator it = chFreq.begin(); it != chFreq.end(); ++it)
    {
        Node *tmp = new Node();
        tmp->ch = it->first;
        tmp->freq = it->second;
        que.push(tmp);
    }
    while (que.size() > 1)
    {
        Node *left = que.top();
        que.pop();
        Node *right = que.top();
        que.pop();
        Node *tmp = new Node();
        tmp->freq = left->freq + right->freq;
        tmp->left = left;
        tmp->right = right;
        que.push(tmp);
    }
    root = que.top();
}

map<char, string> huffmanCode; /* ���ڴ洢ÿ���ַ������Ӧ�� 01 ������ */

/*
 * @Description: ��ȡÿ���ַ��� 01 ������
 * @param: Ҷ�ӽڵ�
 * @param: 01 ����
 * @return: void
*/
void makeHuffmanCode(Node *node, string codestr)
{
    node->huffcode += codestr;
    if (node->left != NULL)
    {
        makeHuffmanCode(node->left, codestr + "0");
    }
    if (node->right != NULL)
    {
        makeHuffmanCode(node->right, codestr + "1");
    }
    if (node->left == NULL && node->right == NULL)
    {
        huffmanCode.insert(make_pair(node->ch, node->huffcode));
    }
}

/**
 * �� source.txt �е��ַ����б���
 * @param filename Ҫ������ļ���
 * @param zipfilename �������ļ���
 */
void outputData(const char *filename, const char *zipfilename)
{
    ofstream out(zipfilename, ios::out | ios::trunc);
    if (out.fail())
    {
        cout << "��������ļ�����ʧ�� " << endl;
        exit(0);
    }
    ifstream in(filename, ios::in);
    if (in.fail())
    {
        cout << "�ļ���ʧ�ܣ�" << endl;
        exit(0);
    }
    string bufferInputStream; /* �ַ������뻺�壬һ���Է����ڴ� */
    string res = "";
    while (getline(in, bufferInputStream))
    {
        for (int i = 0; i < bufferInputStream.size(); i++)
        {
            res += huffmanCode[bufferInputStream[i]];
        }
    }
    char *p = new char[res.length() + 1];
    strcpy(p, res.c_str());
    int count = 0;
    int tmpCh = 0;
    while (count < res.length())
    {
        if (count % 8 == 0 && count != 0)
        {
            out.write((char *)&tmpCh, 1);
            tmpCh = 0;
        }
        tmpCh += (p[count] - '0') * (1 << (7 - count % 8));
        count++;
    }
    out.write((char *)&tmpCh, 1);
    in.close();
    out.close();
}

/**
 * ���ַ�������ӳ�����
 * @param filename ӳ��map�ļ�
 * @param size ����Դ�ļ��ַ��ĸ���
 */
void outputMap(const char *filename, int size)
{
    ofstream out(filename, ios::in | ios::trunc);
    if (out.fail())
    {
        cout << "�ַ�ӳ���ļ���ʧ�ܣ�" << endl;
        exit(0);
    }
    out << size << "\n";
    for (map<char, string>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); ++it)
    {
        out << it->first << " " << it->second << "\n";
    }
    out.close();
}

/**
 * ��unzipfilename��ѹ�ļ����н���
 * ���������1. ��ȡӳ���ļ�
 *         2. ��ȡ��ѹ�ļ�
 *         3. ��ȡ��ѹ
 * @param codefilename ӳ���ļ�
 * @param unzipfilename ��ѹ�ļ�
 * @param filename ��ѹ����ļ�
 */
void unzip(const char *codefilename, const char *unzipfilename, const char *filename)
{
    ifstream incode(codefilename, ios::in);
    if (incode.fail())
    {
        cout << "�ַ�ӳ���ļ��򿪴���" << endl;
        exit(0);
    }
    map<char, string> huffmancode;
    char ch;
    string code;
    string line;
    getline(incode, line);
    int count = atoi(line.c_str()); //��ȡ�ַ�����
    while (getline(incode, line))
    {
        ch = line[0];
        code = line.substr(2, line.size() - 2);
        huffmanCode.insert(make_pair(ch, code));
    }
    incode.close();

    ofstream out(filename, ios::out | ios::trunc);
    if (out.fail())
    {
        cout << "��ѹ����ļ���ʧ�ܣ�" << endl;
        exit(0);
    }

    ifstream inzip(unzipfilename, ios::in | ios::binary);
    if (inzip.fail())
    {
        cout << "�����ļ���ʧ��" << endl;
        exit(0);
    }
    unsigned char content;
    int cur_count = 0; //ͳ���Ѿ����˼����ַ�
    string res = "";
    while (!inzip.eof())
    {
        inzip.read((char *)&content, sizeof(content));
        for (int i = 0; i < 8; i++)
        {
            if ((content & 0x80) == 0x80) //��������������10000000ȡ�����
                res += "1";
            else
                res += "0";
            content <<= 1;
        }
    }
    string tmp = "";
    for (int i = 0; i < res.length(); ++i)
    {
        tmp += res[i];
        for (map<char, string>::iterator it = huffmanCode.begin(); it != huffmanCode.end(); ++it)
        {
            if (tmp == it->second)
            {
                out << it->first;
                tmp = "";
                cur_count++;
            }
        }
        if (cur_count == count)
        {
            break;
        }
    }
    out.close();
    inzip.close();
}

/**
 * @description: ѹ������
 */
void zip()
{
    string filename = "source.txt";  //Ŀ���ļ�
    string zipfilename = "code.bat"; //����ļ�
    string map = "map.txt";          //ӳ���ļ�
    int size = fileRead(filename.c_str());
    outputHuffman();
    createHuffmanTree();
    makeHuffmanCode(root, "");
    outputData(filename.c_str(), zipfilename.c_str());
    outputMap(map.c_str(), size);
}

/**
 * @description: ��ѹ����
 */
void unzip()
{
    string filename = "uncode.txt";  //���Ŀ���ļ�
    string zipfilename = "code.bat"; //��ѹ�ļ�
    string map = "map.txt";          //ӳ���ļ�
    unzip(map.c_str(), zipfilename.c_str(), filename.c_str());
}

int main()
{
    cout << "��ʼ���롣��������"
         << "\n\n";
    zip();
    Sleep(2000);
    cout << "������ɣ�" << endl;
    Sleep(2000);

    cout << "\n���ڽ��롣��������"
         << "\n\n";
    unzip();
    Sleep(2000);
    cout << "�������!��鿴  uncode.txt  �ļ�"
         << "\n\n";
    return 0;
}