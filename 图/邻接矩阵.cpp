//
// Created by Webster on 24-11-14.
//


#include "DataStructure.h"
#define ElymentType int
#define MaxVertexNum 1000
#define INFINITY 65535
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
typedef int Vertex; //用顶点下标表示顶点
typedef int WeightType; //边的权值设为整型
typedef char DataType; // 顶点存储的数据类型设为字符型

//边的定义
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1,V2; //有向边<V1,V2>
    WeightType Weight; //权重
};
typedef PtrToENode Edge;


//图的定义
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv; //顶点数
    int Ne; //边数
    WeightType G[MaxVertexNum][MaxVertexNum]; //邻接矩阵
    DataType Data[MaxVertexNum]; //存顶点的数据
};


typedef PtrToGNode MGraph;


MGraph CreatGraph(int VertexNum) {
    Vertex V,W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv=VertexNum;

    for(V=0;V<Graph->Nv;V++)
        for(W=0;W<Graph->Nv;W++)
            Graph->G[V][W]=INFINITY;

    return Graph;
}

void InsertEdge(MGraph Graph,Edge E) {
    Graph->G[E->V1][E->V2]=E->Weight;
    //若是无向图还要添加V2到V1的边
    Graph->G[E->V2][E->V1]=E->Weight;

}

MGraph BuildGraph() {
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv;
    std::cin >> Nv;
    CreatGraph(Nv);

    std::cin >> Graph->Ne;
    if(Graph->Ne!=0) {
        E=(Edge)malloc(sizeof(struct ENode));
        for(int i=0;i<Graph->Ne;i++) {
            std::cin >> E->V1 >>E->V2 >>E->Weight;
            InsertEdge(Graph,E);
        }
    }

    return Graph;
}


//邻接矩阵实现BFS
bool visited[MaxVertexNum];
void BFS(MGraph Graph,int i) {
    visited[i]=true;
    Queue Q = CreatQueue(MaxVertexNum);
    addQ(Q,i);
    while(!isEmpty(Q)) {
        int v = Delete(Q);
        for(int w = 0; w<Graph->Nv;w++) {
            if(visited[w]==false&&Graph->G[v][w]) {
                visited[w]=true;
                addQ(Q,w);
            }
        }
    }
}