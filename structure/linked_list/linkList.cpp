// 单向链表
#include <iostream>
#include<cstdio>
#include<typeinfo>
using namespace std;

typedef struct LNode
{
    char data;           // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList;

LinkList listHeadInsert(LinkList &);
LinkList listTailInsert(LinkList &);
void destoryList(LinkList &);
bool initList(LinkList &);
bool isEmpty(LinkList);
LNode *getElem(LinkList, int);
LNode *locateElem(LinkList, int);
bool deleteNode(LNode *);
bool listDelete(LinkList &, int, int &);
bool insertPriorNode(LNode *, LNode *);
bool insertNextNode(LNode *, int);
bool listInsert(LinkList &, int, int);
int length(LinkList L);

int main(){
    LinkList L;
    L = listTailInsert(L);
    // listHeadInsert(L);
    int len = length(L);
    cout << len << endl;
    for (int i = 1; i <= len; ++i)
    {
        cout << getElem(L,i)->data;
    }
    destoryList(L);
    system("pause");
    return 0;
}

LinkList listHeadInsert(LinkList &L)
{ // 逆向建立单链表
    initList(L);
    cout<< "输入类型为char的数据(退出按<ctrl>+<z><enter>):";
    char ch;
    LNode *s;
    while (cin.get(ch))
    {
        s = new LNode;
        s->data = ch;
        s->next = L->next;
        L->next = s;
    }
    return L;
}

LinkList listTailInsert(LinkList &L)
{ // 正向建立单链表
    cout<< "输入类型为char的数据(退出按<ctrl>+<z><enter>):";
    char x;
    initList(L);
    LNode *s, *r = L;
    while (cin.get(x))
    {
        s = new LNode;
        s->data = x;
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}

void destoryList(LinkList &L){
    if(L) delete L;
}

// bool InitList(LinkList &L) { //不带头结点
//	L = NULL;
//	return true;
// }

bool initList(LinkList &L)
{ // 带头结点
    L = new LNode;
    if (L == NULL)
        return false;
    L->next = NULL;
    return true;
}

bool isEmpty(LinkList L)
{
    if (L->next == NULL)
        return true;
    else
        return false; // 带头结点
    //	return (L==NULL);//不带头结点
}

// 按位查找，返回第i个元素（带头结点）
LNode *getElem(LinkList L, int i)
{
    if (i < 0)
        return NULL;
    int j = 0;
    LNode *p = L;
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找，找到数据域==e的结点
LNode *locateElem(LinkList L, int e)
{
    LNode *p = L->next;
    while (p != NULL && p->data != e)
        p = p->next;
    return p;
}

// 求表的长度
int length(LinkList L)
{
    LNode *p = L;
    int len = 0;
    while (p->next != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

// bool ListInsert(LinkList &L, int i, int e){//不带头结点
//	if(i<1) return false;
//	if(i==1){
//		LNode *s=(LNode *)malloc(sizeof(LNode));
//		s->data = e;
//		s->next = L;
//		L = s;
//		return true;
//	}
//	LNode *p;
//	int j=1;
//	p = L;
//	while (p!=NULL && j<i-1) {
//		p=p->next;
//		j++;
//	}
//	if(p==NULL) return false;
//	LNode *s = (LNode *)malloc(sizeof(LNode));
//	s->data=e;
//	s->next=p->next;
//	p->next=s;
//	return ture;
// }

bool listInsert(LinkList &L, int i, int e)
{ // 带头结点
    // LNode *p = GetElem(L, i-1)
    if (i < 1)
        return false;
    LNode *p;
    int j = 0;
    p = L;
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    // return InsertNextNode(p, e) 封装的好处
    if (p == NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

// 后插操作：在p结点之后插入e
bool insertNextNode(LNode *p, int e)
{
    if (p == NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

// 前插操作：在p结点之前插入结点s
bool insertPriorNode(LNode *p, LNode *s)
{
    if (p == NULL)
        return false;
    if (s == NULL)
        return false;
    s->next = p->next;
    p->next = s;
    int temp = p->data;
    p->data = s->data;
    s->data = temp;
    return true;
}
// 按位序删除（带头结点）
bool listDelete(LinkList &L, int i, int &e)
{
    if (i < 1)
        return false;
    LNode *p;
    int j = 0;
    p = L;
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL)
        return false;
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return true;
}

// 删除指定结点p
bool deleteNode(LNode *p)
{
    if (p == NULL)
        return false;
    LNode *q = p->next;
    p->data = q->data;
    p->next = q->next;
    free(q);
    return true;
}
