//中序线索二叉树
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100

typedef char ElemType;
typedef struct node {
  ElemType data;
  int ltag,rtag;//线索标记
  struct node *lchild;
  struct node *rchild;
} TBTNode;

void createTBTree(TBTNode * &b, char *str){
  TBTNode *st[MaxSize],*p=NULL;
  int top= -1,k,j=0;
  char ch;
  b = NULL;
  ch = str[j];
  while(ch != '\0'){
    switch(ch){
      case '(': top++;st[top]=p;k=1;break;
      case ')':top--;break;
      case ',':k=2;break;
      default:
        p=(TBTNode*)malloc(sizeof(TBTNode));
        p -> data = ch;
        p -> lchild = p -> rchild = NULL;
        if(p==NULL)
          b = p;
        else{
          switch(k){
            case 1:st[top]->lchild=p;break;
            case 2:st[top]->rchild=p;break;
          }
        }
    }
    j++;
    ch=str[j];
  }
}

void dispTBTree(TBTNode *b){
  if(b != NULL){
    printf("%c", b -> data);
    if(b -> lchild != NULL || b -> rchild != NULL){
      printf("(");
      dispTBTree(b -> lchild);
      if(b -> rchild != NULL) printf(",");
      dispTBTree(b -> rchild);
      printf(")");
    }
  }
}

TBTNode *pre;//全局变量
void thread(TBTNode * &p){
  if(p != NULL){
    thread(p -> lchild);
    if(p -> lchild == NULL){
      p -> lchild = pre;//建立当前结点前驱线索
      p -> ltag = 1;
    }else{
      p -> ltag = 0;
    }
    if(pre -> rchild == NULL){
      pre -> rchild = p;
      pre -> rtag = 1;
    }else{
      pre -> rtag = 0;
    }
    pre = p;
    thread(p -> rchild);//右子树线索化
  }
}

//中序线索化二叉树
TBTNode *createThread(TBTNode *b){
  TBTNode *root;
  root = (TBTNode *)malloc(sizeof(TBTNode));
  root -> ltag = 0;
  root -> rtag = 1;
  root -> rchild = b;
  if(b == NULL){
    root -> lchild = root;
  }else{
    root -> lchild = b;
    pre = root;//pre是*p的前驱结点，供加线索用
    thread(b);
    pre -> rchild = root;//最后处理，加入指向根结点的线索
    pre -> rtag = 1;
    root -> rchild = pre;//根结点右线索化
  }
  return root;
}

void destoryTBTree(TBTNode * &b){
  if(b -> ltag == 0){//结点有左孩子，释放左子树
    destoryTBTree(b -> lchild);
  }
  if(b -> rtag == 0){
    destoryTBTree(b -> rchild);
  }
  free(b);
}

void thInOrder(TBTNode *tb){
  TBTNode *p = tb -> lchild;//指向根结点
  printf("%c ", p -> data);
  while(p -> rtag == 1 && p -> rchild != tb){
    p = p -> rchild;
    printf("%c ",p -> data);
  }
  p = p -> rchild;
}

int main(){
  TBTNode *b,*tb;
  createTBTree(b,"A(B(D(,G)),C(E,F))");
	printf(" 二叉树:");dispTBTree(b);printf("\n");
	tb=createThread(b);
	printf(" 线索中序序列:");thInOrder(tb);printf("\n");
	destoryTBTree(tb);
	return 1;
}
