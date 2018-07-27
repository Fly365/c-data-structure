//先序、中序和后序 递归 遍历算法
//二叉树的基本运算
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100

typedef char ElemType;
typedef struct node {
  ElemType data;
  struct node *lchild;//左孩子
  struct node *rchild;//右孩子
} BTNode;

//创建二叉树
//括号表示法，根(子树1，子树2，...,子树m) 的字符串
//各子树之间用逗号分开，结点之间关系是通过括号嵌套表示的
//A(B(D(,G)), C(E,F))--先根遍历
void createBTree(BTNode * &b, char *str){
  BTNode *st[MaxSize],*p = NULL;
  int top = -1, k,j = 0;
  char ch;
  b = NULL;
  ch = str[j];
  while(ch != '\0'){
    switch(ch){
      case '(' : top++;st[top]=p;k=1;break;//左孩子结点
      case ')' : top--;break;
      case ',' : k = 2; break; //为孩子右结点
      default:
        p = (BTNode *)malloc(sizeof(BTNode));
        p -> data = ch;
        p -> lchild = p -> rchild = NULL;
        if(b== NULL){
          b = p;
        }else{
          switch(k){
            case 1: st[top] -> lchild = p; break;
            case 2: st[top] -> rchild = p; break;
          }
        }
    }
    j++;
    ch = str[j];
  }
}

//销毁二叉树
void destoryBTree(BTNode * &b){
  if(b != NULL){
    destoryBTree(b -> lchild);
    destoryBTree(b -> rchild);
    free(b);
  }
}

void dispBTree(BTNode *b){
  if(b != NULL){
    printf("%c", b -> data);
    if(b -> lchild != NULL || b -> rchild != NULL){
      printf("(");
      dispBTree(b -> lchild);
      if(b -> rchild != NULL) printf(",");
      dispBTree(b -> rchild);
      printf(")" );
    }
  }
}

//先序遍历
void preOrder(BTNode *b){
  if(b != NULL){
    printf("%c ",b -> data);
    preOrder(b -> lchild);
    preOrder(b -> rchild);
  }
}

//中序遍历
void inOrder(BTNode *b){
  if(b != NULL){
    inOrder(b -> lchild);
    printf("%c ", b -> data);
    inOrder(b -> rchild);
  }
}

//后序遍历
void postOrder(BTNode *b){
  if(b != NULL){
    postOrder(b -> lchild);
    postOrder(b -> rchild);
    printf("%c ", b -> data);
  }
}

//多个文件同时编译: g++ -g -Wall -std=c++11 -o recuorder btree.cpp recuorder.cpp
int main(){
  BTNode *b;
  createBTree(b,"A(B(D(,G)),C(E,F))");
  printf("b:");
  dispBTree(b);
  printf("\n");
  printf("先序遍历:");
  preOrder(b);
  printf("\n");
  printf("中序遍历:");
  inOrder(b);
  printf("\n");
  printf("后序遍历:");
  postOrder(b);
  printf("\n");
  destoryBTree(b);
  return 1;
}
