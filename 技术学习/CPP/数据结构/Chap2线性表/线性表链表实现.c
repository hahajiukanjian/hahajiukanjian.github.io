#include "c1.h"
typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node * pNext;
}* PNODE, NODE;

//基本操作
PNODE InitList(void);
void CreatListHead(PNODE pL, int n);    //头插法创建单向链表
void CreatListTail(PNODE pL, int n);    //尾插法创建单向链表
bool IsEmpty(PNODE pL);                 //判断链表是否为空
bool DestroyList(PNODE pL);             //销毁链表
int GetListLength(PNODE pL);            //获取链表长度
bool GetListElem(PNODE pL, int pos, ElemType *elem);//获取第pos个结点的数据域的值


int main(void)
{
    PNODE pL;
    pL = InitList();


    return 0;
}

PNODE InitList(void)
{
    
}
