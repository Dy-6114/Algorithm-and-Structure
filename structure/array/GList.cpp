// 广义表
#include<iostream>

using namespace std;

typedef enum{ATOM,LIST} ElemTag; //ATOM == 0：原子；LIST == 1：子表
typedef char AtomType ;
typedef struct GLNode{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct{
            struct GLNode *hp, *tp; //头尾链表结构
        }ptr;
    };
}*GList,GNode;

GList createGList(GList);
void copyGList(GList, GNode *);

