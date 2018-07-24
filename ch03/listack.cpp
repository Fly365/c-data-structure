//链栈的基本运算算法
#include <stdio.h>
#include <malloc.h>

typedef char ElemType;

typedef struct linknode {
  ElemType data;
  struct linknode *next;
} LinkStNode; //链栈类型

void initStack(LinkStNode * &s){
  s = (LinkStNode *)malloc(sizeof(LinkStNode));
  s -> next = NULL;
}

void destoryStack(LinkStNode * &s){
  LinkStNode *p = s -> next;
  while(p != NULL){
    free(s);
    s = p;
    p = p -> next;
  }
  free(s);
}

bool stackEmpty(LinkStNode *s){
  return (s -> next == NULL);
}

void push(LinkStNode * &s, ElemType e){
  LinkStNode *p;
  p = (LinkStNode *)malloc(sizeof(LinkStNode));
  p -> data = e;
  p -> next = s -> next;
  s -> next = p;
}

bool pop(LinkStNode * &s, ElemType &e){
  if(s -> next == NULL)
    return false;
  LinkStNode *p;
  p = s -> next;
  e = p -> data;
  s -> next = p -> next;
  free(p);
  return true;
}

bool getTop(LinkStNode *s, ElemType &e){
  if(s -> next == NULL)
    return false;
  e = s -> next -> data;
  return true;
}
