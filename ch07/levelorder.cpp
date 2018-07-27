//层次遍历算法
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

//--------循环队列---------------
typedef struct {
  BTNode *data[MaxSize];
  int front, rear; //队头和队尾指针
} SqQueue; //顺序队列类型

void initQueue(SqQueue *&q){
  q = (SqQueue *)malloc(sizeof(SqQueue));
  q -> front = q -> rear = 0;
}

void destoryQueue(SqQueue *&q){
  free(q);
}

bool queueEmpty(SqQueue *q){
  return (q -> front == q -> rear);
}

bool enQueue(SqQueue *&q, BTNode *e){
  if((q -> rear + 1) % MaxSize == q -> front)
    return false;
  q -> rear = (q -> rear + 1) % MaxSize;
  q -> data[q -> rear] = e;
  return true;
}

bool deQueue(SqQueue *&q, BTNode *&e){
  if(q -> front == q -> rear)
    return false;
  q -> front = (q -> front + 1) % MaxSize;
  e = q -> data[q -> front];
  return true;
}

//------------level order -----
void levelOrder(BTNode *b){
  BTNode *p;
  SqQueue *qu;
  initQueue(qu);
  enQueue(qu, b);
  while(!queueEmpty(qu)){
    deQueue(qu,p);
    printf("%c ", p -> data);
    if(p -> lchild != NULL){
      enQueue(qu, p-> lchild);
    }
    if(p -> rchild != NULL){
      enQueue(qu, p -> rchild);
    }
  }
}

int main(){
	BTNode *b;
	createBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");dispBTree(b);printf("\n");
	printf("层次遍历序列:");levelOrder(b);printf("\n");
	destoryBTree(b);
	return 1;
}
