//
// Created by Webster on 24-11-11.
//

#include "DataStructure.h"

//链表线性表
#define  ElymentType int
typedef struct Lnode* List;
struct Lnode {
    ElymentType data;
    List Next;
};

//表长
int Llength(List PtrL) {
    List p = PtrL;
    int j = 0;
    while (p!= NULL) {
        p = p->Next;
        j++;
    }
    return j;
}

//按序号查找值
List findK_1(ElymentType k, List PtrL) {
    List p = PtrL;
    int i = 1;
    while (p != NULL && i < k) {
        i++;
        p = p->Next;
    }
    if (i == k) return p;
    else return NULL;
}

//按值查找位置
List findK_2(ElymentType x, List PtrL) {
    List p = PtrL;
    while (p != NULL && p->data != x) {
        p = p->Next;
    }
    return p;
}


//在指定位置插入
List insertL(int pos,ElymentType x, List PtrL) {

    List p,s;

    //判断是否是表头插入
    if (pos == 1) {
        p = (List)malloc(sizeof(struct Lnode));
        p->data = x;
        p->Next = PtrL;
        return p;
    }

    s = findK_1(pos - 1, PtrL);
    if (s == NULL) {
        std::cout << "参数错误";
        return NULL;
    }

    else {
        p = (List)malloc(sizeof(struct Lnode));
        p->data = x;
        p->Next = s->Next;
        s->Next = p;
        return PtrL;
    }
}


//删除下标为pos的结点
List DeleteL(int pos, List PtrL) {
    List p, s;
    if (pos == 1) {
        if (PtrL != NULL) PtrL = PtrL->Next;
        else return NULL;
        return PtrL;
    }
    p = findK_1(pos, PtrL);
    if (p == NULL) {
        std::cout << "结点不存在";
        return NULL;
    }
    else {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}