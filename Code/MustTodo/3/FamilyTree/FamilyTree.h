#ifndef FAMILYTREE_H
#define FAMILYTREE_H
#include <QPoint>
#include <QMouseEvent>

#include "Person.h"
#include <queue>
#include <QDebug>
using namespace std;

//家谱树
class FamilyTree {
  public:
    Person *root;
    FamilyTree() : root(NULL) {}
    void display();                  //家谱显示
    void displayNGener(int n);       //显示第n代所有人
    void enquiryByName(string name); //根据姓名输出本人、父亲、孩子
    void enquiryByBirthday(int year, int month,
                           int day); //按照出生日期查询成员名单

    void deletePerson(string name);       //删除
    void recusiveDelete(Person* &root);      //递归删除

};



inline void FamilyTree::enquiryByBirthday(int year, int month, int day) {
    queue<Person *> que;
    que.push(root);
    queue<Person *> list;
    while (!que.empty()) {
        Person *q = que.front();
        que.pop();
        if (q->birthday.year == year && q->birthday.month == month &&
            q->birthday.day == day) {
            list.push(q);
        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }
    while (!list.empty()) {
        Person *p = list.front();
        list.pop();
//        cout << p << endl;
    }
}


/**
 * @brief FamilyTree::deletePerson
 * @param name
 * 对家谱中的某一个进行删除操作
 */
inline void FamilyTree::deletePerson(string name)
{
    queue<Person *> que;
    que.push(root);
    Person* res = NULL;
    while (!que.empty()) {
        Person *p = que.front();
        que.pop();
        if (p->name == name) {
            res = p;
            break;
        }
        for (int i = 0; i < p->count; i++) {
            que.push(p->children[i]);
        }
    }
    if(res == root){
        recusiveDelete(root);
        return;
    }

    int index = -1;
    for (int i = 0; i < res->parent->count; ++i) {
       if(res->parent->children[i] == res){
           index = i;
           break;
       }
    }

    for (int i = index+1; i < res->parent->count; ++i) {
        res->parent->children[i-1] = res->parent->children[i];
    }

    res->parent->count -= 1;

    recusiveDelete(res);


}

inline void FamilyTree::recusiveDelete(Person *&root)
{
//    qDebug() << QString::fromStdString(root->name) << endl;
    if(root->count != 0){
        for (int i = 0; i < root->count; ++i) {
           recusiveDelete(root->children[i]);
        }
    }
    delete root;
    root = NULL;
}



inline void FamilyTree::display() {
    queue<Person *> que;
    que.push(root);
    int preGener = 1;
    while (!que.empty()) {
        Person *p = que.front();
        que.pop();
        if (p->generation != preGener) {
            preGener = p->generation;
        }
        for (int i = 0; i < p->count; i++) {
            que.push(p->children[i]);
        }
    }
}

inline void FamilyTree::displayNGener(int n) {
    queue<Person *> que;
    que.push(root);
    while (!que.empty()) {
        Person *p = que.front();
        que.pop();
        if (p->generation == n) {
//            cout << p << endl;
        } else {
            for (int i = 0; i < p->count; i++) {
                que.push(p->children[i]);
            }
        }
    }
}

inline void FamilyTree::enquiryByName(string name) {
    queue<Person *> que;
    que.push(root);
    Person *p = NULL;
    while (!que.empty()) {
        Person *q = que.front();
        que.pop();
        if (q->name == name) {
            p = q;
            break;
        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }

}


#endif // FAMILYTREE_H
