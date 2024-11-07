//
// Created by Webster on 24-11-4.
//

#include "DataStructure.h"
#define ElymentType int
typedef struct AVLNode *Position;
typedef Position AVLTree;

struct AVLNode {
    ElymentType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};


int Max(int a,int b) {
    return (a>b)?a:b;
}

//获取树高
int GetHeight (AVLTree A) {
    if(A==NULL)return 0;
    return A->Height;
}


//平衡因子
int balanceFactor(AVLNode *T) {
    if(T==nullptr) return 0;
    else return GetHeight(T->Left)-GetHeight(T->Right);
}



//右单旋(LL)
AVLTree RightRotation(AVLTree A) {
    AVLTree B = A-> Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left),GetHeight(A->Right));
    B->Height=Max(GetHeight(B->Left),A->Height)+1;

    return B;
}


// 左单旋(RR)
AVLTree LeftRotation(AVLTree A) {
    AVLTree B = A->Right;
    A->Left = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left),GetHeight(A->Right))+1;
    B->Height= Max(GetHeight(B->Right),A->Height)+1;
    return B;
}

//右-左旋转(LR)
AVLTree LeftRightRotation(AVLTree A) {
    A->Left=RightRotation(A->Left);
   return LeftRotation(A);
}

//左-右旋转

AVLTree RightLeftRotation(AVLTree A) {
    A->Right= LeftRotation(A->Right);
    return RightRotation(A);
}


AVLTree rotate(AVLTree T) {
    T->Height = Max(GetHeight(T->Left),GetHeight(T->Right));

    int Factor=balanceFactor(T);

    if(Factor>1) {
        // LR情况
        if(balanceFactor(T->Left)<0)
            T->Left = LeftRightRotation(T->Left);
        // LL情况
        return RightRotation(T);
    }

    if(Factor<-1) {
        //RL情况
        if(balanceFactor(T->Right)>0) {
            T->Right=RightLeftRotation(T->Right);
        }
        //RR情况
        return LeftRotation(T);
    }
    return T;
}


 //插入
AVLTree Insert(AVLTree T,ElymentType x) {
    if (!T) {
        T=(AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = x;
        T-> Height = 0;
        T->Left=T->Right = NULL;
    }

    // 插入左子树
    else if(T->Data > x) {
        T->Left = Insert(T->Left,x);
        //如果需要右旋
        if(GetHeight(T->Left)-GetHeight(T->Right)==2) {

            //右单旋(LL)
            if(T->Left->Data>x) {
                 T=RightRotation(T);
            }
            //先左旋再右旋(LR)
            else {
                T=LeftRightRotation(T);
            }
        }
    }
    else if(T->Data <x) {
        //插入右子树
        T->Right = Insert(T->Right,x);

        //如果需要左旋
        if(GetHeight(T->Left)-GetHeight(T->Right)==-2) {

            //左单旋
            if(T->Data<x) {
                T=LeftRotation(T);
            }
            else {
                T=RightLeftRotation(T);
            }
        }
    }

    T->Height=Max(GetHeight(T->Left),GetHeight(T->Right))+1;

    return T;
}

//删除

AVLTree Delete(AVLTree T,ElymentType Val) {
    if(!T) return nullptr;

    //查找节点
    if(Val<T->Data) {
        T->Left=Delete(T->Left,Val);
    }

    else if(Val>T->Data) {
        T->Right = Delete(T->Right,Val);
    }

    else {
        //如果是只有单子结点或空子节点
        if(!T->Left||!T->Right) {
            AVLNode* tmp = T->Left?T->Left:T->Right;
            delete T;
            return tmp;
        }
        //双结点
        else {
            AVLNode* tmp = T->Right;
            while(tmp->Left!=nullptr) {
                tmp = tmp->Left;
            }
            T->Data = tmp->Data;
            T->Right = Delete(T->Right,tmp->Data);
        }
    }

    T->Height = Max(GetHeight(T->Left),GetHeight(T->Right))+1;
    return rotate(T);
}

