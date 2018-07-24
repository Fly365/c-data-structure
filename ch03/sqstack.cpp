//顺序栈基本运算算法
#include <stdio.h>
#include <malloc.h>

#define MaxSize 100
typedef char ElemType;

typedef struct {
  ElemType data[MaxSize];
  int top;
} SqStack; //顺序栈类型

void initStack(SqStack * &s){
  s = (SqStack *)malloc(sizeof(SqStack));
  s -> top = -1;
}

void destoryStack(SqStack * &s){
  free(s);
}

bool stackEmpty(SqStack *s){
  return (s -> top == -1);
}

bool push(SqStack * &s, ElemType &e){
  if(s -> top == MaxSize-1)
    return false;
  s -> top++;
  s -> data[s -> top] = e;
  return true;
}

bool pop(SqStack * &s, ElemType &e){
  if(s -> top == -1)
    return false;

  e = s -> data[s -> top];
  s -> top--;
  return true;
}

bool getTop(SqStack *s, ElemType &e){
  if(s -> top == -1)
    return false;

  e = s -> data[s -> top];
  return true;
}
