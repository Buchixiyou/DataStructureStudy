//
// Created by Webster on 24-11-16.
//

#include "DataStructure.h"
#define MaxVertexNum 1000
#define ElymentType int
#define Position int
typedef int Vertex; //顶点下标
typedef int WeightType; //边的权值
typedef char DataType; //顶点的数据类型
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



//边的定义
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1,V2;
    WeightType Weight;
};
typedef PtrToENode Edge;


//邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV; //邻接点下标
    WeightType Weight; //边权重
    PtrToAdjVNode Next; //指向下一个邻接点的指针
};

//顶点表头结点的定义
typedef struct Vnode {
    PtrToAdjVNode FirstEdge; //边表头指针
    DataType Data;
}AdjList[MaxVertexNum];

//图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv; //顶点数
    int Ne; //边数
    AdjList G; //邻接表
};
typedef PtrToGNode LGraph; //以邻接表方式存储的图类型


LGraph CreatGraph(int VertexNum) {
    //初始化一个只有顶点但没有边的图
    LGraph Graph;
    Vertex V;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv=VertexNum;
    Graph->Ne = 0;

    for(V=0;V<Graph->Nv;V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

void InsertEdge(LGraph Graph,Edge E) {
    PtrToAdjVNode NewNode;
    //插入<V1,V2>
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    //插入结点
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    //若是无向图则还需建立<V2,V1>
    NewNode= (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV=E->V2;
    NewNode->Weight=E->Weight;
    //插入结点
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge=NewNode;
}


LGraph BuildGraph() {
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv,i;

    std::cin >> Nv;
    Graph = CreatGraph(Nv);
    std::cin >> Graph->Ne;
    if(Graph->Ne!=0) {
        E = (PtrToENode)malloc(sizeof(struct ENode));
        for(i=0;i<Graph->Ne;i++)
            std::cin >> E->V1 >> E->V2 >> E->Weight;
            InsertEdge(Graph,E);
    }


    //如果结点有数据的话
    for(V=0;V<Graph->Nv;V++)
        std::cin >> Graph->G[V].Data;

    return Graph;
}

//邻接表实现BFS
bool visited[MaxVertexNum]

void BFS(LGraph Graph,int i) {
    PtrToAdjVNode p;
    visited[i]= true; //记录访问过的结点i
    Queue Q = CreatQueue(MaxVertexNum);
    addQ(Q,i); //入队
    while(!isEmpty(Q)) {
        Delete(Q); //队首元素出队
        //检测所有邻接点
        for(p = Graph->G[i].FirstEdge;p;p=p->Next) {
            int w = p->AdjV; //邻接点的下标
            if(!visited[w]) {
                visited[w]=true; //访问标记
                addQ(Q,w); //顶点w入队
            }
        }
    }
}