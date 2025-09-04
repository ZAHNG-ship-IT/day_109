#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>//包含bool的头文件
typedef struct Node
{
    int data;
    struct Node *pNext;
}NODE,*PNODE;//typedef 起别名：
// NODE 等价于 struct Node
// PNODE 等价于 struct Node*（指向节点的指针）
void traverse_list(PNODE pHead);
PNODE create_list(void);
bool is_empty(PNODE pHead);
int length_list(PNODE pHead);
bool insert_list(PNODE,int,int);//插入
bool delete_list(PNODE,int,int*);
void sort_list(PNODE);

int main()
{

    PNODE pHead = NULL;
    pHead = create_list();//创建一个肺循环链表，并将该链表的首地址赋予pHead
    int val;

    traverse_list(pHead);
    int len = length_list(pHead);

    if(is_empty(pHead)) printf("链表为空");
    else printf("不是空");
    printf("\n");
    printf("链表长度是:%d",len);
    sort_list(pHead);
    printf("\n");
    insert_list(pHead,3,100);
    printf("\n");
    if(delete_list(pHead,2,&val)) printf("success,%d",val);
    else printf("fail");
    printf("\n");
    traverse_list(pHead);
    return 0;


    
}
PNODE create_list(void)
{
    int len;
    int i;
    int val;


    PNODE pHead = (PNODE)malloc(sizeof(NODE));
    PNODE pTail = pHead;//定义一个中间变量
    pHead->pNext = NULL;
    if(NULL == pHead)
    {
        printf("内存分配失败，已退出");
        exit(-1);
    }
    printf("请输入链表节点个数：");
    scanf("%d",&len);

    for(i = 0;i<len;++i)
    {
        printf("第%d个节点的值",i+1);
        scanf("%d",&val);
        PNODE pNew = (PNODE)malloc(sizeof(NODE));
        if(NULL == pHead)
        {
            printf("内存分配失败，已退出");
            exit(-1);
        }
        pNew->data = val;

        pTail->pNext = pNew;//新建一个指针,
        //
        //
        //
        //
        //这一个过程要好好理解
        pNew->pNext = NULL;
        pTail = pNew;

    }

    return pHead;


}
void traverse_list(PNODE pHead)//遍历
{
    PNODE p = pHead -> pNext;

    while(NULL != p)//尾结点地址是NULL;
    {
        printf("%d ",p->data);
        p = p->pNext;

    }
    printf("\n");

}

bool is_empty(PNODE pHead)
{
    if(pHead->pNext == NULL) return true;
    else return false;
}

int length_list(PNODE pHead)
{
    int num = 0;
    PNODE p = pHead->pNext;
    while(NULL != p)//尾结点地址是NULL;
    {

        p = p->pNext;
        num ++;

    }
    return num;


}

void sort_list(PNODE pHead)
{
    //选择排序
    int i,j,k;
    PNODE p,q;
    int len = length_list(pHead);
    for(i = 0,p = pHead ->pNext;i< len - 1;++i,p = p ->pNext)
    {
        for(j = i+1,q = p->pNext;j<len;++j,q = q ->pNext)
        {
            if(p ->data > q ->data)
            {
                k = p ->data;
                p ->data = q ->data;
                q ->data = k;

            }
        }

    }
}

bool insert_list(PNODE pHead,int pos,int val)//插入，首节点。位置从一开始，插入的值
{
    int i = 0;
    PNODE p = pHead;

    while(NULL != p && i<pos - 1)//与条件控制while循环这个操作非常不错
    {//该循环在i= pos -2中断，但是，由于++i在后面，所以，p的位置是pos-1
        p = p ->pNext;
        ++i;
    }
    if(i >pos - 1 || NULL ==p) return false;
    
    PNODE pNew = (PNODE)malloc(sizeof(NODE));

    if(NULL == pNew)
    {
        printf("分配失败");
        exit(-1);
    }

    pNew->data =val;//新建的结构停地址数据是值

    PNODE q = p->pNext;//新建一个只想pos位置的指针
    p->pNext = pNew;//pNew是p的下一个节点
    pNew ->pNext = q;//pNew指向原先节点的位置

    return true;


}

bool delete_list(PNODE pHead,int pos,int* pVal)//此函数第三个返回值，闻所未闻，简直太厉害了，直接传入一个地址，但是地址的值在函数内部确定了，之后，我们调用的时候，直接返回该地址的值
{
    int i = 0;
    PNODE p = pHead;

    while(NULL != p && i<pos - 1)//与条件控制while循环这个操作非常不错
    {//该循环在i= pos -2中断，但是，由于++i在后面，所以，p的位置是pos-1
        p = p ->pNext;
        ++i;
    }
    if(i >pos - 1 || NULL ==p) return false;


    PNODE q = p->pNext;
    * pVal = q ->data;

    p->pNext = p -> pNext -> pNext;//p直接指向下一个节点的位置
    free(q);
    q = NULL;//释放内存
    return true;

}