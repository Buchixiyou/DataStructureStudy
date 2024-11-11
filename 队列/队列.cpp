//
// Created by Webster on 24-11-11.
//

#include "DataStructure.h"
#define ElymentType int
#define Position int
typedef struct QNode* Queue;

Queue CreatQueue(int Maxsize); //生成长度的为MaxSize的队列
bool isFull(Queue Q, int Maxsize); //判断队列是否满
bool addQ(Queue Q, ElymentType item); //队尾入队
bool isempty(Queue Q); //判空
ElymentType Delete(Queue Q); //队首出队

//队列结构体
struct QNode {
    ElymentType* Data;
    Position front,rear;
    int Maxsize;
};



Queue CreatQueue(int Maxsize) {
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->Data = (ElymentType*)malloc(Maxsize * sizeof(ElymentType));
    q->front = q->rear = 0;
    q->Maxsize = Maxsize;
    return q;
}

bool isFull(Queue q) {
    return ((q->rear + 1) % q->Maxsize == q->front);
}

bool isEmpty(Queue q) {
    return (q->front == q->rear);
}

bool addQ(Queue q, ElymentType item) {
    if (isFull(q)) return -1;
    else {
        q->rear = (q->rear + 1) % q->Maxsize;
        q->Data[q->rear] = item;
        return true;
    }
}


ElymentType Delete(Queue q) {
    if (isempty(q)) return -1;
    else {
        q->front = (q->front + 1) % q->Maxsize;
        return q->Data[q->front];
    }
}