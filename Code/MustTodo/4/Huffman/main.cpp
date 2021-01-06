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

map<char, int> chFreq; //存储每个字符的频率
Node *root = NULL;

//节点类
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
 * @description: 读取文件，统计字符个数
 * @param {const char} *filename 要压缩的文件
 */
int fileRead(const char *filename)
{
    ifstream in;
    in.open(filename, ios::in);
    if (in.fail())
    {
        cout << "文件打开失败！" << endl;
        exit(0);
    }
    string bufferInputStream; /* 字符串输入缓冲，一次性放入内存 */
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
 * @description: 将字符个数统计结果存入 Huffman.txt 中
 */
void outputHuffman()
{
    ofstream out("Huffman.txt", ios::out | ios::trunc);
    if (out.fail())
    {
        cout << "Huffman.txt 文件创建失败！" << endl;
        exit(0);
    }
    for (map<char, int>::iterator it = chFreq.begin(); it != chFreq.end(); ++it)
    {
        out << it->first << " " << it->second << "\n";
    }
}

/**
 * @description: 构建哈夫曼树
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

map<char, string> huffmanCode; /* 用于存储每个字符与其对应的 01 二进制 */

/*
 * @Description: 获取每个字符的 01 二进制
 * @param: 叶子节点
 * @param: 01 编码
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
 * 对 source.txt 中的字符进行编码
 * @param filename 要编码的文件名
 * @param zipfilename 编码后的文件名
 */
void outputData(const char *filename, const char *zipfilename)
{
    ofstream out(zipfilename, ios::out | ios::trunc);
    if (out.fail())
    {
        cout << "编码输出文件创建失败 " << endl;
        exit(0);
    }
    ifstream in(filename, ios::in);
    if (in.fail())
    {
        cout << "文件打开失败！" << endl;
        exit(0);
    }
    string bufferInputStream; /* 字符串输入缓冲，一次性放入内存 */
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
 * 将字符与编码的映射输出
 * @param filename 映射map文件
 * @param size 保留源文件字符的个数
 */
void outputMap(const char *filename, int size)
{
    ofstream out(filename, ios::in | ios::trunc);
    if (out.fail())
    {
        cout << "字符映射文件打开失败！" << endl;
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
 * 对unzipfilename解压文件进行解码
 * 解码操作：1. 读取映射文件
 *         2. 读取解压文件
 *         3. 读取解压
 * @param codefilename 映射文件
 * @param unzipfilename 解压文件
 * @param filename 解压输出文件
 */
void unzip(const char *codefilename, const char *unzipfilename, const char *filename)
{
    ifstream incode(codefilename, ios::in);
    if (incode.fail())
    {
        cout << "字符映射文件打开错误！" << endl;
        exit(0);
    }
    map<char, string> huffmancode;
    char ch;
    string code;
    string line;
    getline(incode, line);
    int count = atoi(line.c_str()); //读取字符个数
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
        cout << "解压输出文件打开失败！" << endl;
        exit(0);
    }

    ifstream inzip(unzipfilename, ios::in | ios::binary);
    if (inzip.fail())
    {
        cout << "编码文件打开失败" << endl;
        exit(0);
    }
    unsigned char content;
    int cur_count = 0; //统计已经读了几个字符
    string res = "";
    while (!inzip.eof())
    {
        inzip.read((char *)&content, sizeof(content));
        for (int i = 0; i < 8; i++)
        {
            if ((content & 0x80) == 0x80) //从左往右依次与10000000取与操作
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
 * @description: 压缩操作
 */
void zip()
{
    string filename = "source.txt";  //目标文件
    string zipfilename = "code.bat"; //输出文件
    string map = "map.txt";          //映射文件
    int size = fileRead(filename.c_str());
    outputHuffman();
    createHuffmanTree();
    makeHuffmanCode(root, "");
    outputData(filename.c_str(), zipfilename.c_str());
    outputMap(map.c_str(), size);
}

/**
 * @description: 解压操作
 */
void unzip()
{
    string filename = "uncode.txt";  //输出目标文件
    string zipfilename = "code.bat"; //解压文件
    string map = "map.txt";          //映射文件
    unzip(map.c_str(), zipfilename.c_str(), filename.c_str());
}

int main()
{
    cout << "开始编码。。。。。"
         << "\n\n";
    zip();
    Sleep(2000);
    cout << "编码完成！" << endl;
    Sleep(2000);

    cout << "\n正在解码。。。。。"
         << "\n\n";
    unzip();
    Sleep(2000);
    cout << "解码完成!请查看  uncode.txt  文件"
         << "\n\n";
    return 0;
}