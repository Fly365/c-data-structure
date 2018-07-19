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

//链表是否为空,L头结点
bool listEmpty(DLinkNode *L){
  return (L -> next == NULL);
}

//链表长度
int listLength(DLinkNode *L){
  DLinkNode *p = L;
  int i = 0;
  if(p -> next != NULL){
    i++;
    p = p -> next;
  }
  return i;
}

// 输出打印链表
void  dispList(DLinkNode *L){
  DLinkNode *p = L -> next;
  while(p != NULL){
    printf("%d ", p -> data);
    p = p -> next;
  }
  printf("\n");
}

//获取指定索引位置的元素
bool getElem(DLinkNode *L, int i, ElemType &e){
  if(i < 0) return false;
  int j = 0;
  DLinkNode *p = L;
  while(j < i && p != NULL){
    j++;
    p = p -> next;
  }
  if(p == NULL){
    return false;
  }
  e = p -> data;
  return true;
}

//获取和指定元素相等的第一个元素的索引位置
int localteElem(DLinkNode *L, ElemType e){
  int n = 1;
  DLinkNode *p = L -> next;
  while(p != NULL && p -> data != e){
    n++;
    p = p -> next;
  }

  if(p == NULL) return 0;
  return n;
}

//链表新加元素
bool listInsert(DLinkNode * &L, int i, ElemType e){
  DLinkNode *p = L, *s;
  int j = 0;
  if(i < 0) return false;
  while(p != NULL && j < i-1){
    j++;
    p = p -> next;
  }
  if(p == NULL) return false;
  s = (DLinkNode *)malloc(sizeof(DLinkNode));
  s -> data = e;
  s -> next = p -> next;//将结点s插入到结点p之后
  if(p -> next != NULL){
    p -> next -> prior = s;
  }
  s -> prior = p;
  p -> next = s;
  return true;
}

//链表删除指定索引位置的元素
bool listDelete(DLinkNode * &L, int i, ElemType &e){
  DLinkNode *p = L -> next,*q;
  int j = 0;
  if(i < 0) return false;
  if(j < i-1 && p != NULL){
      j++;
      p = p -> next;
  }
  q = p -> next;
  if(q == NULL) return false;
  e = p -> data;
  p -> next = q -> next;
  if(p -> next != NULL) p -> next -> prior = p;
  free(q);
  return true;
}
