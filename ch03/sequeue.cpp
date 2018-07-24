//顺序队列(非环形队列)基本运算算法
#include <stdio.h>
#include <malloc.h>

#define MaxSize 100
typedef char ElemType;
typedef struct {
  ElemType data[MaxSize];
  int front,rear;
} SqQueue;

void initQueue(SqQueue * &q){
  q = (SqQueue *)malloc(sizeof(SqQueue));
  q -> front = q -> rear = -1;
}

void destoryQueue(SqQueue * &q){
  free(q);
}

bool queueEmpty(SqQueue *q){
  return (q -> front == q -> rear);
}

bool enQueue(SqQueue *&q, ElemType e){
  if(q -> rear == MaxSize-1)
    return false;
  q -> rear++;
  q -> data[q->rear] = e;
  return true;
}

bool deQueue(SqQueue * &q, ElemType &e){
  if(q -> front == q -> rear)
    return false;
  q -> front++;
  e = q -> data[q-> front];
  return true;
}
