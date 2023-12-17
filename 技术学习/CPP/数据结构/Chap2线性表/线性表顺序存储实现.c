#include "c1.h"
typedef char ElemType;

//创建抽象数据类型
typedef struct SqList
{
    ElemType *elem;
    int length;
    int cnt;
}SQ, *PSQ;

//基本操作 
Status InitList_Sq(PSQ pL);     //初始化线性表
void DestroyList(PSQ pL);       //销毁线性表
Status EmptyList(PSQ pL);       //判断线性表是否为空
void ClearList(PSQ pL);         //清空线性表
int GetListLength(PSQ pL);      //获取线性表长度
int GetListCnt(PSQ pL);         //获取线性表有效长度
int GetElem(PSQ pL, int pos);   //获取第pos个元素的值,此处的pos从1开始
int LocateElem(PSQ pL, ElemType elem);//定位某个元素的位置,elem为查找的某个元素
Status ListInsert_Sq(PSQ pL, int pos, ElemType elem);//在线性表中插入元素
Status FullList(PSQ pL);        //判断线性表是否已满
Status DeleteElem(PSQ pL, int pos, ElemType *pelem);//删除某个位置的元素

int main(void)
{
    SQ L;
    InitList_Sq(&L);

    return 0;
}

Status InitList_Sq(PSQ pL)
{
    int len;
    printf("Please Input SqList Len:");
    scanf("%d", &len);
    pL->elem = (ElemType *)malloc(sizeof(ElemType)*len);
    if(NULL == pL->elem)                                //判断是否还有剩余内存供给分配
        return OVERFLOW;
    pL->length = len;                                   //空表长度为len
    pL->cnt = 0;                                        //空表有效长度为0
    return OK;
}
void DestroyList(PSQ pL)
{
    if(!EmptyList(pL))
        free(pL->elem);//释放elem
}
Status EmptyList(PSQ pL)
{
    if(0 != pL->cnt)
        return FALSE;
    else
        return TRUE;
}
void ClearList(PSQ pL)
{
    pL->length = 0;    //将线性表的长度重置为0
}
int GetListLength(PSQ pL)
{
    return (pL->length);
}
int GetListCnt(PSQ pL)
{
    return (pL->cnt);
}
int GetElem(PSQ pL, int pos)
{
    int elem;
    if(pos<=0 || pos>=((pL->cnt)+1))    //此处pos从1开始,cnt也是从1开始,pos的值不能比cnt大.
        return ERROR;                   // 如果大于cnt,则线性表中没有与之对应的有效元素
    else
        elem = pL->elem[pos-1];
    return elem;
}
int LocateElem(PSQ pL, ElemType elem)
{
    for(int i=0; i<pL->cnt; i++)
    {
        if(elem == pL->elem[i])
        {
            break;
            return i+1; //返回的是序号,而不是下标,因此需要+1
        }
    }
    return INFEASIBLE;
    //用while实现
    // int i = 0;
    // while(i<pL->cnt && elem!=pL->elem[i])
    //     i++
    // if(cnt == i)
    //     return INFEASIBLE;
    // else
    //     return i+1;
}
Status ListInsert_Sq(PSQ pL, int pos, ElemType elem)
{
    //初始条件: 线性表已存在,给定插入的下标位置与元素的值
    //操作结果: 将元素插入到线性表中,并且该元素之后的元素保持不变
    if((pos<1 && pos>pL->cnt+1) || FullList(pL))
    //判断pos的位置是否合理,并且判断线性表是否已满
        return ERROR;
    for(int i=(pL->cnt)-1; i>pos-1; i--)
        pL->elem[i+1] = pL->elem[i];
    pL->elem[pos-1] = elem;
    pL->cnt++;
    return OK;
}
Status FullList(PSQ pL)
{
    if(pL->cnt == pL->length)
        return TRUE;
    else   
        return FALSE;
}
Status DeleteElem(PSQ pL, int pos, ElemType *pelem)
{
    if((pos<1 && pos>pL->cnt) || EmptyList(pL))
        return ERROR;
    *pelem = pL->elem[pos-1];
    for(int i=pos-1; i<=pL->cnt-1; i++)
        pL->elem[i] = pL->elem[i+1];
    pL->cnt--;
    return OK;
}