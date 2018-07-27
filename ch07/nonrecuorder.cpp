//先序、中序和后序 非递归 遍历 算法
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

//---------------stack-------------
typedef struct {
  BTNode * data[MaxSize]; //存放栈中的数据元素
  int top;//存放栈顶指针，即栈顶元素在data数组中的下标
} SqStack;//顺序栈类型

void initStack(SqStack *&s){
  s = (SqStack *)malloc(sizeof(SqStack));
  s -> top = -1;
}

void destoryStack(SqStack *&s){
  free(s);
}

bool stackEmpty(SqStack *s){
  return (s -> top == -1);
}

bool push(SqStack *&s, BTNode *e){
  if(s -> top == MaxSize - 1)
    return false;
  s -> top++;
  s -> data[s -> top] = e;
  return true;
}

bool pop(SqStack *&s, BTNode *&e){
  if(s -> top == -1)
    return false;
  e = s -> data[s -> top];
  s -> top--;
  return true;
}

bool getTop(SqStack *s, BTNode *&e){
  if(s -> top == -1)
    return false;
  e = s -> data[s -> top];
  return true;
}

//------------------树 非递归遍历---------------------
void preOrder1(BTNode *b){
  BTNode *p;
  SqStack *st;
  initStack(st);
  push(st, b);//根节点进栈
  while(!stackEmpty(st)){
    pop(st, p);//退栈 p 并访问
    printf("%c ", p -> data);
    if(p -> rchild != NULL){//有右孩子时将其进栈
      push(st, p -> rchild);
    }
    if(p -> lchild != NULL){//有左孩子时将其进栈
      push(st, p -> lchild);
    }
  }
  printf("\n");
  destoryStack(st);
}

void preOrder2(BTNode *b){
  BTNode *p;
  SqStack *st;
  initStack(st);
  p = b;
  while(!stackEmpty(st) || p != NULL){
    while(p != NULL){
      printf("%c ", p -> data );
      push(st, p);
      p = p -> lchild; //移动到左孩子
    }
    if(!stackEmpty(st)){
      pop(st,p);
      p = p -> rchild; //转向处理右孩子
    }
  }
  printf("\n");
  destoryStack(st);
}

//中序遍历，左子树 根节点  右子树
void inOrder(BTNode *b){
  BTNode *p;
  SqStack *st;
  initStack(st);
  if(b != NULL){
    p = b;
    while(!stackEmpty(st) || p != NULL){
      while(p != NULL){
        push(st,p);
        p = p -> lchild;//移动到左孩子
      }
      if(!stackEmpty(st)){
        pop(st,p);
        printf("%c ", p -> data);
        p = p -> rchild;//转向处理右子树
      }
    }
    printf("\n");
  }
  destoryStack(st);
}

//后序遍历
void postOrder(BTNode *b){
  BTNode *p,*r;
  bool flag;
  SqStack *st;
  initStack(st);
  p = b;
  do{
    while(p != NULL){
      push(st,p);
      p = p -> lchild;
    }
    r = NULL;//r指向刚刚访问的结点，初始时为空
    flag = true; //flag为真表示正在处理栈顶结点
    while(!stackEmpty(st) && flag){
      getTop(st,p);
      if(p -> rchild == r){
        printf("%c ", p -> data );
        pop(st,p);
        r = p;
      }else{
        p = p -> rchild;
        flag = false;
      }
    }
  } while(!stackEmpty(st));
  printf("\n");
  destoryStack(st);
}

int main(){
	BTNode *b;
	createBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");dispBTree(b);printf("\n");
	printf("先序遍历序列1:");preOrder1(b);
	printf("先序遍历序列2:");preOrder2(b);
	printf("中序遍历序列:");inOrder(b);
	printf("后序遍历序列:");postOrder(b);
	destoryBTree(b);
	return 1;
}
