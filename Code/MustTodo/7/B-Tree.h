#include <bits/stdc++.h>
using namespace std;

const int m = 3; //设定每个节点的最大分支为 3
const int KEY_MAX = m - 1;
const int KEY_MIN = m / 2;

class Node
{
public:
    int keynum;
    int key[m]; 
    bool is_leaf;
    Node *ptr[m + 1];
    Node *parent;
    Node()
    {
        for (int i = 0; i < m; i++)
        {
            key[i] = 0;
            ptr[i] = NULL;
        }
        ptr[m] = NULL;
        is_leaf = true;
        keynum = 0;
        parent = NULL;
    }
};

class BTree
{
public:
    Node *root;
    BTree() { root = new Node(); } // B树初始化
    void insert(int target);
    void btree_insert(Node *&node, int target); //插入一个节点到B树

    void btree_insert_nofull(Node *p, int target);          //在某个节点未满的情况下插入
    void btree_split(Node *&parent, int pos, Node *&child); //插入时分裂
    void btree_level_traverse();                            //层次遍历
    bool contain(int key);                                  //检查是否树中有相同的键值
    bool search(Node *node, int key);

    void clear();
    void recursive_clear(Node *node);
    void deleteNode(Node *node);
    Node *findNode(int target);
    Node *findNode(Node *start, int target);
};

Node *BTree::findNode(int target) { return findNode(root, target); }

Node *BTree::findNode(Node *start, int target)
{
    int i = 0;
    for (i = 0; target > start->key[i]; ++i)
    {
    }
    if (i < start->keynum && target == start->key[i])
    {
        return start;
    }
    return findNode(start->ptr[i], target);
}

void BTree::clear()
{
    recursive_clear(root);
    root = NULL;
}

void BTree::recursive_clear(Node *node)
{
    if (node != NULL)
    {
        if (!node->is_leaf)
        {
            for (int i = 0; i <= node->keynum; i++)
            {
                recursive_clear(node->ptr[i]);
            }
        }
        deleteNode(node);
    }
}

void BTree::deleteNode(Node *node)
{
    if (node != NULL)
    {
        delete node;
        node = NULL;
    }
}

bool BTree::search(Node *node, int key)
{
    if (node != NULL)
    {
        int i = 0;
        for (i = 0; i < node->keynum && key > node->key[i]; i++)
        {
        }
        if (i < node->keynum && node->key[i] == key)
        {
            return true;
        }
        else
        {
            return node->is_leaf ? false : search(node->ptr[i], key);
        }
    }
}

bool BTree::contain(int key) { return search(root, key); }

/**
 * @description:  B树插入操作
 */
void BTree::insert(int target)
{
    if (contain(target))
    {
        cout << "键值 " << target << " 有重复！！插入失败！" << endl;
        return;
    }
    else
    {
        if (root != NULL)
        {
            btree_insert(root, target);
        }
        else
        {
            root = new Node();
        }
    }
}

/**
 * @description: 插入一个节点到B树
 */
void BTree::btree_insert(Node *&node, int target)
{
    int i = node->keynum;
    int j = node->keynum;
    int k = 0;
    int count = 0;
    int new_key;

    // 1. 如果要插入的是叶节点
    if (node->is_leaf)
    {
        // 1.1 如果这个叶子节点已满且这个节点不是根节点
        if (node->keynum == KEY_MAX && node->parent != NULL)
        {
            Node *tmp = node;
            int count = 0;
            while (j > 0 && target < node->key[j - 1])
            {
                node->key[j] = node->key[j - 1];
                j--;
            }
            node->key[j] = target;
            node->keynum++;
            count++;

            while (1)
            {
                node = node->parent;
                if (node->keynum == KEY_MAX)
                {
                    count++;
                    if (node->parent == NULL)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            node = tmp;
            for (k = 0; k < count; k++)
            {
                if (node->parent == NULL)
                {
                    Node *in = new Node();
                    in->is_leaf = false;
                    in->ptr[0] = node;
                    btree_split(in, 0, node);
                    root = in;
                }
                else
                {

                    i = node->parent->keynum;

                    new_key = node->key[node->keynum / 2];

                    while (i > 0 && new_key < node->parent->key[i - 1])
                    {
                        i--;
                    }
                    btree_split(node->parent, i, node);
                    node = node->parent;
                }
            }
        }
        else if (node->keynum == KEY_MAX && node->parent == NULL)
        {
            while (i > 0 && target < node->key[i - 1])
            {
                node->key[i] = node->key[i - 1];
                --i;
            }
            node->key[i] = target;
            node->keynum++;
            Node *tmp = new Node();
            tmp->is_leaf = false;
            tmp->ptr[0] = node;
            btree_split(tmp, 0, node);
            root = tmp;
        }
        else
        {
            while (i > 0 && target < node->key[i - 1])
            {
                node->key[i] = node->key[i - 1];
                --i;
            }
            node->key[i] = target;
            node->keynum++;
        }
    }
    else
    {
        while (i > 0 && target < node->key[i - 1])
        {
            --i;
        }
        Node *tmp = node->ptr[i];
        btree_insert(tmp, target);
    }
}

/**
 * @description: 在某个节点未满的情况下插入
 */
void BTree::btree_insert_nofull(Node *p, int target)
{
    if (p->is_leaf)
    {
        int pos = p->keynum;
        while (pos > 0 && target < p->key[pos - 1])
        {
            p->key[pos] = p->key[pos - 1];
            pos--;
        }
        p->key[pos] = target;
        p->keynum++;
    }
    else
    {
        int pos = p->keynum;
        while (pos > 0 && target < p->key[pos - 1])
        {
            pos--;
        }

        if (p->ptr[pos]->keynum == m - 1)
        {
            btree_split(p, pos, p->ptr[pos]);
            if (target > p->key[pos])
            {
                pos++;
            }
        }

        btree_insert_nofull(p->ptr[pos], target);
    }
}

/**
 * @description: 子树分裂
 */
void BTree::btree_split(Node *&parent, int pos, Node *&child)
{
    Node *rightChild = new Node();
    rightChild->keynum = KEY_MIN;
    rightChild->is_leaf = child->is_leaf;

    for (int i = 0; i < KEY_MIN; i++)
    {
        rightChild->key[i] = child->key[i + KEY_MIN + 1];
    }
    if (!child->is_leaf)
    {
        for (int i = 0; i < KEY_MIN + 1; i++)
        {
            rightChild->ptr[i] = child->ptr[i + KEY_MIN + 1];
        }
    }
    child->keynum = KEY_MIN;

    /* 更新parent */
    for (int i = parent->keynum; i > pos; --i)
    {
        parent->ptr[i + 1] = parent->ptr[i];
        parent->key[i] = parent->key[i - 1];
    }
    parent->keynum++;
    parent->ptr[pos + 1] = rightChild;
    rightChild->parent = parent;
    child->parent = parent;
    parent->key[pos] = child->key[KEY_MIN];
    if (!rightChild->is_leaf)
    {
        for (int i = 0; i < KEY_MIN + 1; ++i)
        {
            rightChild->ptr[i]->parent = rightChild;
        }
    }
}

/**
 * @description: B树的层次遍历
 */
void BTree::btree_level_traverse()
{
    queue<pair<Node *, int>> q;
    q.push(make_pair(root, 1));
    int pre_level = 0;
    while (!q.empty())
    {
        Node *front = q.front().first;
        int cur_level = q.front().second;
        q.pop();
        if (cur_level != pre_level)
        {
            cout << "\n第 " << cur_level << " 层： ";
        }
        pre_level = cur_level;
        cout << "[ ";
        for (int i = 0; i < front->keynum; i++)
        {
            cout << front->key[i] << " ";
        }
        cout << "] ";
        for (int i = 0; i < front->keynum + 1; i++)
        {
            if (front->ptr[i] != NULL)
            {
                q.push(make_pair(front->ptr[i], cur_level + 1));
            }
        }
    }

    cout << endl;
}