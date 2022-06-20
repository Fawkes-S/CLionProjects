#include"SList.h"

//初始化
void InitList(List *list)
{
    //创建头结点（此时头结点也是尾结点）
    list->first = list->last = (Node*)malloc(sizeof(Node));
    assert(list->first != NULL);
    //为该结点赋值
    list->first->next = NULL;
    list->size = 0;
}
//尾插
//void push_back(List *list, ElemType x)
//{
//    insert(list,end(list),x);
//}


//尾插
void push_back(List *list, ElemType x)
{
    //Node *s = _buynode(x);
    //创建尾插结点
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    //为尾插结点赋值
    s->data = x;
    s->next = NULL;

    //将尾插结点连接到链表尾部
    list->last->next = s;
    //更改管理结点中last的指向
    list->last = s;
    //更改有效结点个数
    list->size++;
}

//头插
//void push_front(List *list, ElemType x)
//{
//    insert(list,begin(list),x);
//}


//头插
void push_front(List *list, ElemType x)
{
    //Node *s = _buynode(x);
    //创建头插结点
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    s->data = x;
    //将头插结点连接到链表中
    s->next = list->first->next;
    list->first->next = s;
    //如果这个是插入的第一个有效结点，需要更改尾指针的指向
    if(list->size == 0)
    {
        list->last = s;
    }
    //更改有效结点个数
    list->size++;
}

//打印链表中的数据
void show_list(List *list)
{
    Node *p = list->first->next;
    while(p != NULL)
    {
        printf("%d-->",p->data);
        p = p->next;
    }
    printf("Nul.\n");
}

//尾部删除
void pop_back(List *list)
{
    //链表是否还有结点？
    if(list->size == 0)
        return;
    //寻找倒数第二个结点
    Node *p = list->first;
    while(p->next != list->last)
        p = p->next;
    //删除尾结点
    free(list->last);
    //更改尾指针的指向
    list->last = p;
    //更改现在尾结点的指针域
    list->last->next = NULL;
    //更改有效结点数
    list->size--;
}

//头部删除
void pop_front(List *list)
{
    //链表中是否有元素？
    if(list->size == 0)
        return;
    //临时保存要删除结点的地址
    Node *p = list->first->next;
    //删除该结点与链表的连接
    list->first->next = p->next;
    //删除结点
    free(p);
    //该链表是否只有一个有效结点
    if(list->size == 1)
    {
        //更改尾指针的指向
        list->last = list->first;
    }
    //更改有效结点个数
    list->size--;
}

//按值插入（前提是链表内的数据从小到大排序）
void insert_val(List *list, ElemType x)
{
    Node *s = _buynode(x);
    /*
    //创建要插入的链表结点
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    s->data = x;
    s->next = NULL;
    */
    //查找要插入的位置
    Node *p = list->first;
    while(p->next!=NULL && p->next->data<x)
        p = p->next;

    //这个位置是否为尾部？
    if(p->next == NULL)
    {
        //如果为尾部修改尾指针位置
        list->last = s;
    }
    //将结点插入
    s->next = p->next;
    p->next = s;
    //更改有效结点个数
    list->size++;
}

//查找数据
Node* find(List *list, ElemType key)
{
    Node *p = list->first->next;
    while(p!=NULL && p->data!=key)
        p = p->next;
    return p;
}

//查找有效结点的个数
int  length(List *list)
{
    return list->size;
}
/*
//按照值来删除方法一：查找要删除结点位置来进行删除
void delete_val(List *list, ElemType key)
{
    //链表是否为空？
    if(list->size==0)
        return;
    //查找到要删除结点的位置
    Node *p = find(list,key);
    //如果没有找到
    if(p == NULL)
    {
        printf("要删除的数据不存在.\n");
        return;
    }
    //如果找到，且这个结点是尾结点
    if(p == list->last)
    {
        //对这个结点进行尾删
        pop_back(list);
    }
    else//删除方法：拷贝下一结点到当前结点，删除下一结点
    {
        //保存下一结点指针
        Node *q = p->next;
        //拷贝下一结点
        p->data = q->data;
        p->next = q->next;
        //删除下一结点
        free(q);
        //更改有效结点数
        list->size--;
    }
}
*/


//按照值来删除方法二：查找要删除结点的前驱结点位置来进行删除
void delete_val(List *list, ElemType key)
{
    //链表是否为空？
    if(list->size==0)
        return;
    //查找到要删除结点的前驱位置
    Node *p = list->first;
    while(p->next!=NULL && p->next->data!=key)
        p=p->next;
    //如果没有找到
    if(p->next== NULL)
    {
        printf("要删除的数据不存在.\n");
        return;
    }
    //如果找到，且这个结点是尾结点
    if(p->next == list->last)
    {
        //对这个结点进行尾删
        pop_back(list);
    }
    else
    {
        //保存要删除结点的指针
        Node *q = p->next;
        //删除结点与链表的连接
        p->next = q->next;
        //删除结点
        free(q);
        //更改有效结点数
        list->size--;
    }
}


//排序(从小到大排序)
void sort(List *list)
{
    //有效的链表个数<=1？
    if(list->size==0 || list->size==1)
        return;

    /*  将链表分成两个链表s和q  */
    Node *s = list->first->next; //保存第一个链表的指针
    Node *q = s->next;  //保存第二个链表的指针

    /*断开两个链表的连接*/
    list->last = s;
    list->last->next = NULL;

    //第二个链表是否还有结点？
    while(q != NULL)
    {
        /*从第二个链表中不断取出结点，插入第一个链表*/
        s = q; //从第二个链表中取出一个结点
        q = q->next;//取出一个结点后q后移一位

        //在第一个链表中查找要插入结点的前驱结点
        Node *p = list->first;
        while(p->next!=NULL && p->next->data<s->data)
            p = p->next;

        //如果要插入结点的位置在第一个链表尾部
        if(p->next == NULL)
        {
            //修改尾指针
            list->last = s;
        }
        //插入
        s->next = p->next;
        p->next = s;
    }
}

//逆置
void resver(List *list)
{
    if(list->size==0 || list->size==1)
        return;
    /*  将链表分成两个链表s和q  */
    Node *p = list->first->next;
    Node *q = p->next;
    /*断开两个链表的连接*/
    list->last = p;
    list->last->next = NULL;

    /*从第二个链表中不断取出结点，头插到第一个链表*/
    while(q != NULL)
    {
        //从第二个链表中取出结点
        p = q;
        q = p->next;
        //头插到第一个链表
        p->next =list->first->next;
        list->first->next = p;
    }
}

//清除单链表(释放所有的有效结点)
void clear(List *list)
{
    //是否有有效结点?
    if(list->size == 0)
        return;

    Node *p = list->first->next;
    //将有效结点全部释放
    while(p != NULL)
    {
        list->first->next = p->next;
        free(p);
        p = list->first->next;
    }
    //有效结点删除完成之后，更新尾指针和有效结点个数
    list->last = list->first;
    list->size = 0;
}
//销毁(释放所有结点即包括头结点和有效结点)
void destroy(List *list)
{
    //释放有效结点
    clear(list);
    //释放头结点
    free(list->first);
    //将头结点和尾结点置空
    list->first = list->last = NULL;
}

void split(List *list,List *left){
    Node *slow,*fast;
    slow = list->first->next;
    fast = list->first->next->next;
    while(fast!=NULL &&fast->next != NULL){
        slow =slow->next;
        fast = fast->next->next;
    }
    left->first->next=slow->next;
    slow->next = NULL;

}


//代码优化
//生成结点
Node* _buynode(ElemType x)
{
    //为结点分配空间
    Node *s = (Node *)malloc(sizeof(Node));
    assert(s != NULL);
    //为该结点的数据域赋值
    s->data = x;
    //对应指针域，当结点插入链表时再对其进行赋值，目前先置空
    s->next = NULL;
    return s;
}
//返回第一个有效结点
It begin(List *list)
{
    return list->first->next;
}
//返回尾结点的下一结点(空结点)
It end(List *list)
{
    return list->last->next;
}
//在链表的某个结点前面插入结点
void insert(List *list, It pos, ElemType x)
{
    //找到结点要插入的位置
    Node *p = list->first;
    while(p->next != pos)
    {
        p = p->next;
    }
    //获取一个结点
    Node *s = _buynode(x);
    //将该结点插入链表
    s->next = p->next;
    p->next = s;
    //如果插入结点的位置在尾部，需要更改尾指针的值
    if(pos == NULL)
        list->last = s;
    //更改有效结点个数
    list->size++;
}
