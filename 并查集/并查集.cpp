//
// Created by Webster on 24-11-10.
//

#include "DataStructure.h"
#define MAXN 1000
typedef int ElymentType;
typedef int SetName;
typedef ElymentType SetType[MAXN];


//合并
void Union(SetType S,SetName Root1,SetName Root2) {
    if(S[Root1]>S[Root2]) { //Root1节点数更少
        S[Root2]+=S[Root1]; //Root2节点数增加
        S[Root1]=Root2; //Root1根节点指向Root2
    }


    else {
        //反之同理
        S[Root1]+=S[Root2];
        S[Root2]=Root1;
    }
}

SetName Find(SetType S,ElymentType X) {
    int root = X;
    while(root>=0) {
        root=S[root];
    }
    while(X!=root) {
        int t=S[X];
        S[X]=root;
        X=t;
    }
    return root;
}