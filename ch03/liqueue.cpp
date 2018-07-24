//链队运算算法
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;

typedef struct DataNode {
  ElemType data;
  struct DataNode *next;
} DataNode;//链队数据结点类型

typedef struct {
  DataNode *front;//指向队首结点
  DataNode *rear;//指向队尾结点
}LinkQuNode; //链队类型

void initQueue(LinkQuNode * &q){
  q = (LinkQuNode *)malloc(sizeof(LinkQuNode));
  q -> front = q -> rear = NULL;
}

void destoryQueue(LinkQuNode * &q){
  DataNode *p = q -> front, *r;
  if(p != NULL){
    r = p -> next;
    while(r != NULL){
      free(p);
      p = r;
      r = p -> next;
    }
  }
  free(p);
  free(q);
}

bool queueEmpty(LinkQuNode *q){
  return (q -> rear == NULL);
}

void enQueue(LinkQuNode *&q, ElemType e){
  DataNode *p;
  p = (DataNode *)malloc(sizeof(DataNode));
  p -> data = e;
  p -> next = NULL;
  if(q -> rear == NULL){//队列为空
    q -> front = q -> rear = p;
  }else{
    q -> rear -> next = p;
    q -> rear = p;
  }
}

bool deQueue(LinkQuNode * &q, ElemType &e){
  DataNode *t;
  if(q -> rear == NULL)
    return false;
  t = q -> front;
  if(q -> front == q -> rear){//只有一个结点
    q -> front = q -> rear = NULL;
  }else{
    q -> front = q -> front -> next;
  }
  e = t -> data;
  free(t);
  return true;
}
