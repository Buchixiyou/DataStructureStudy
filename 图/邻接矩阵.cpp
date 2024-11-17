//
// Created by Webster on 24-11-14.
//


#include "DataStructure.h"
#define ElymentType int
#define MaxVertexNum 1000
#define INFINITY 65535
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