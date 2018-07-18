//双链表基本运算算法
#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct DNode {
  ElemType data;
  struct DNode *prior;//前驱结点
  struct DNode *next;//后继结点
} DLinkNode;

//头插法建双链表
void createListF(DLinkNode * &L, ElemType a[], int n){
  DLinkNode *s; //当前的结点
  L = (DLinkNode *)malloc(sizeof(DLinkNode)); //创建头结点
  L -> prior = L -> next = NULL;
  for(int i = 0; i < n; i++){
    s = (DLinkNode *)malloc(sizeof(DLinkNode));
    s -> data = a[i];
    s -> next = L -> next;//结点s插在原开始结点之前，头结点之后
    if(L -> next != NULL){
      L -> next -> prior = s;
    }
    L -> next = s;
    s -> prior = L;
  }
}

//尾插法建双链表
void createListR(DLinkNode * &L, ElemType a[], int n){
  DLinkNode *s,*r;
  L = (DLinkNode *)malloc(sizeof(DLinkNode));
  L -> prior = L -> next = NULL;
  r = L; //r结点始终指向终端结点，开始时指向头结点
  for(int i = 0; i < n; i++){
    s = (DLinkNode *)malloc(sizeof(DLinkNode));
    s -> data = a[i];
    r -> next = s;
    s -> prior = r; //结点s插入结点r之后
    r = s; //将新加入的结点作为尾结点s
  }
  r -> next = NULL;//尾结点next域置为NULL
}

//初始化双链表
void iniitList(DLinkNode * &L){
  L = (DLinkNode *)malloc(sizeof(DLinkNode)); //创建头结点
  L -> prior = L -> next = NULL;
}

//销毁双链表
void destoryList(DLinkNode *L){
  DLinkNode *pre = L, *p = pre -> next;
  while(p != NULL){
    free(pre);
    pre = p;
    p = pre -> next;
  }
  free(pre);
}

//链表是否为空
bool listEmpty()
