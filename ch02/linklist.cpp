// 单链表的基本运算
#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct LNode {
  ElemType data;
  struct LNode *next; //指向后继结点
} LinkNode; // 单链表结点类型

//头插法建立单链表
void createListF(LinkNode * &L, ElemType a[], int n){
  LinkNode *s;
  L = (LinkNode *)malloc(sizeof(LinkNode));// 创建头结点
  L -> next = NULL;
  for(int i = 0; i < n; i++){
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = a[i];
    s -> next = L -> next;// 将结点s插在原始结点之前，头结点之后
    L -> next = s;
  }
}

//尾插法建立单链表
void createListR(LinkNode * &L, ElemType a[], int n){
  LinkNode *s,*r; //新结点s，尾指针r
  L = (LinkNode *) malloc(sizeof(LinkNode));
  L -> next = NULL;
  r = L; //r始终指向终端结点，开始时指向头结点
  for(int i = 0; i < n; i++){
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = a[i];
    r -> next = s;// 将结点s 插入结点 r 之后
    r = s;
  }
  r -> next = NULL;//终端结点next域置为NULL
}

//初始化
void initList(LinkNode * &L){
  L = (LinkNode *)malloc(sizeof(LinkNode));//创建头结点
  L -> next = NULL;
}

//销毁链表
void destoryList(LinkNode * &L){
  LinkNode *pre = L, *p = pre -> next;
  while(p != NULL){
    free(pre);
    pre = p;
    p = p -> next;
  }
  free(pre);//此时p为NULL，pre指向尾结点，释放它
}

//链表是否为空
bool listEmpty(LinkNode *L){
  return (L -> next == NULL);
}

//链表长度
int listLength(LinkNode *L){
  LinkNode *p = L;
  int i = 0;
  while(p -> next != NULL){
    i++;
    p = p -> next;
  }
  return i;
}

void dispList(LinkNode *L){
  LinkNode *p = L-> next;
  while(p != NULL){
    printf("%d ", p -> data);
    p = p -> next;
  }
  printf("\n");
}

bool getElem(LinkNode *L, int i, ElemType &e){
  int j = 0;
  LinkNode *p = L;
  if(i < 0) return false;
  while(j < i && p != NULL){
    j++;
    p = p -> next;
  }
  if(p == NULL)
    return false;
  else {
    e = p -> data;
    return true;
  }
}

int locateElem(LinkNode *L, ElemType e){
  LinkNode *p = L -> next;
  int n = 1;
  while(p != NULL && p -> data != e){
    p = p -> next;
    n++;
  }
  if(p == NULL){
    return 0;
  }else{
    return n;
  }
}

bool listInsert(LinkNode * &L, int i, ElemType e){
  int j = 0;
  LinkNode *p = L, *s;
  if(i < 0) return false;
  while(j < i-1 && p != NULL){
    j++;
    p = p -> next;
  }
  if(p == NULL){
    return false;
  }else{
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = e;
    s -> next = p -> next;
    p -> next = s;
    return true;
  }
}

bool listDelete(LinkNode * &L, int i, ElemType &e){
  int j = 0;
  LinkNode *p = L, *q;
  if(i < 0) return false;
  while(j < i -1 && p != NULL){
    j++;
    p = p -> next;
  }
  if(p == NULL){
    return false;
  }else{
    q = p -> next;
    if(q == NULL){//未找到位序为 i-1的结点
      return false;
    }
    e = q -> data;
    p -> next = q -> next;
    free(q);
    return true;
  }
}
