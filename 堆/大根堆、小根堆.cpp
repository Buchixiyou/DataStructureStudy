//
// Created by Webster on 24-11-9.
//


#include "DataStructure.h"
#define ElymentType int
#define MaxData 1000
#define ERROR false
typedef struct HeapStruct *Heap;

struct HeapStruct {
    ElymentType* Elyments; //存储元素的数组
    int Size;   //堆的当前元素数量
    int Capacity;   //堆的最大容量
};

typedef Heap MaxHeap; //最大堆
typedef Heap MinHeap; //最小堆

Heap Creat(int MaxSize) {
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
    H->Elyments = (ElymentType*)malloc((MaxSize+1)*sizeof(ElymentType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elyments[0]=MaxData;

    return H;
}

bool isFull(MaxHeap H) {
    return (H->Size == H->Capacity);
}

bool Insert (MaxHeap H, ElymentType X) {
    if(isFull(H)) {
        std::cout << "堆已满";
        return ERROR;
    }

    int i=++H->Size;
    for(;H->Elyments[i/2]<X;i/=2) {
        H->Elyments[i]=H->Elyments[i/2];
    }
    H->Elyments[i]=X;
    return true;
}


bool isEmpty(MaxHeap H) {
    return (H->Size==0);
}

ElymentType DeleteMax(MaxHeap H) {
    int parent,child;
    ElymentType MaxItem,X;

    if(isEmpty(H)) {
        std::cout << "最大堆已空";
        return ERROR;
    }

    MaxItem = H->Elyments[1]; //取出最大堆的根节点
    X = H->Elyments[H->Size--];

    for(parent=1;parent*2<H->Size;parent=child) {
        child=parent*2;
        if((child!=H->Size)&&(H->Elyments[child]<H->Elyments[child+1]))
            child++;
        if(X>=H->Elyments[child]) break;
        else {
            H->Elyments[parent]=H->Elyments[child];
        }
    }
    H->Elyments[parent]=X;
    return MaxItem;
}


//建造最大堆
void PercDown(MaxHeap H,int p) {
    int parent,child;
    ElymentType X;

    X=H->Elyments[p]; //取出根节点值
    for(parent = p;parent*2<H->Size;parent=child) {
        child = parent*2 ;
        if((child!=H->Size)&&(H->Elyments[child]<H->Elyments[child+1]))
            child ++;

        if(X>=H->Elyments[child]) break;
        else
            H->Elyments[parent]=H->Elyments[child];
    }
    H->Elyments[parent]=X;
}

void BuildHeap(MaxHeap H) {
    for(int i = H->Size/2;i>0;i--) {
        PercDown(H,i);
    }
}


//小根堆操作相反即可

