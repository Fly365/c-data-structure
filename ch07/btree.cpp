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

//查找结点
BTNode * findNode(BTNode *b, ElemType x){
  BTNode *p;
  if(b == NULL){
    return NULL;
  }else if(b -> data == x){
    return b;
  }else{
    p = findNode(b -> lchild,x);
    if(p != NULL){
      return p;
    }else{
      return findNode(b -> rchild, x);
    }
  }
}

BTNode * lchildNode(BTNode *p){
  return p -> lchild;
}

BTNode * rchildNode(BTNode *p){
  return p -> rchild;
}

int heightBR(BTNode *b){
  int lchild,rchild;
  if(b == NULL) return 0;
  else{
    lchild = heightBR(b -> lchild);//求左子树的高度为lchild
    rchild = heightBR(b -> rchild);
    return (lchild > rchild) ? (lchild + 1) : (rchild + 1);
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

//查找相应的叶子结点
void dispLeaf(BTNode *b){
  if(b != NULL){
    //如果一个结点的左孩子和右孩子均为空，那么该结点为叶子结点
    if(b -> lchild == NULL && b -> rchild == NULL){
      printf("%c ", b -> data);
      dispLeaf(b -> lchild);
      dispLeaf(b -> rchild);
    }
  }
}

/*int main(){
  BTNode *b;
  createBTree(b,"A(B(D(,G)),C(E,F))");
  dispBTree(b);
  printf("\n");

  printf("%d\n", heightBR(b));
  return 1;
}*/
