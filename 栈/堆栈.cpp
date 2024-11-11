//
// Created by Webster on 24-11-11.
//

#include "DataStructure.h"
//堆栈 (数组实现)
#define  ElymentType int
#define  Position  int

typedef struct SNode* Stack;
struct SNode {
    ElymentType* Data;
    Position top;
    int Maxsize;
};

//创建堆栈
Stack CreatStack(int Maxsize) {
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElymentType*)malloc(Maxsize * sizeof(ElymentType));
    S->Maxsize = Maxsize;
    S->top = -1;
    return S;
}

//判满
bool isFull(Stack S) {

    return(S->top == S->Maxsize - 1);
}

//入队
bool Push(Stack S, ElymentType X) {
    if (isFull(S))return false;
    else {
        S->Data[++(S->top)] = X;
        return true;
    }
}

//判空
bool isEmpty(Stack S) {
    return (S->top == -1);
}

//出队
ElymentType Pop(Stack S) {
    if (isEmpty(S)) return 0;
    else {
        return S->Data[(S->top)--];
    }
}
