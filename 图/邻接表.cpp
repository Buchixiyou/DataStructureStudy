//
// Created by Webster on 24-11-16.
//

#include "DataStructure.h"
#define MaxVertexNum 1000
typedef int Vertex; //顶点下标
typedef int WeightType; //边的权值
typedef char DataType; //顶点的数据类型

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