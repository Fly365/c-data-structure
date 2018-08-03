//AVL 平衡二叉树
#include <stdio.h>
#include <malloc.h>

typedef int KeyType;//关键字类型
typedef char InfoType;
typedef struct node {
  KeyType key;//关键字项
  int bf;//平衡因子
  InfoType data;//其他数据域
  struct node *lchild,*rchild;//左右孩子指针
} BSTNode;

//对以指针p所指结点为根的二叉树作左平衡旋转处理，本算法结束时，指针p指向新的根节点
void leftProcess(BSTNode *&p, int &taller){
  BSTNode *p1,*p2;
  if(p->bf == 0){
    //原本左右子树等高，现因左子树增高而使树增高
    p->bf = 1;
    taller = 1;
  }else if(p->bf == -1){
    //原本右子树比左子树高，现左、右子树等高
    p->bf = 0;
    taller=0;
  }else{
    p1 = p->lchild;//p1指向结点p的左孩子
    if(p1->bf == 1){
      //新结点插入在结点b的左孩子的左子树上，要做LL调整
      p->lchild = p1->rchild;
      p1->rchild=p;
      p->bf=p1->bf=0;
      p=p1;
    }else if(p1->bf == -1){
      //新结点插入在结点b的左孩子的右子树上，要做LR调整
      p2=p1->rchild;
      p1->rchild=p2->lchild;
      p2->lchild=p1;
      p->lchild=p2->rchild;
      p2->rchild=p;
      if(p2->bf == 0)
        p->bf=p1->bf=0;//新结点插在p2处作为叶子结点情况
      else if(p2->bf == 1){
        //新结点插在p2的左子树上的情况
        p1->bf=0;
        p->bf=-1;
      }else{
        //新结点插在p2的右子树上情况
        p1->bf=1;p2->bf=0;
      }
      p=p2;p->bf=0;//扔将p指向新的根结点，并置其bf值为0
    }
    taller=0;
  }
}
