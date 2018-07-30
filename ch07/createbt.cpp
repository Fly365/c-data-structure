#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node{
	ElemType data;			//数据元素
	struct node *lchild;	//指向左孩子节点
	struct node *rchild;	//指向右孩子节点
} BTNode;
void createBTree(BTNode * &b,char *str)	//创建二叉树
{
	BTNode *St[MaxSize],*p=NULL;
	int top=-1,k,j=0;
	char ch;
	b=NULL;				//建立的二叉树初始时为空
	ch=str[j];
	while (ch!='\0')  	//str未扫描完时循环
	{
   	   	switch(ch)
		{
		case '(':top++;St[top]=p;k=1; break;		//为左孩子节点
		case ')':top--;break;
		case ',':k=2; break;                      		//为孩子节点右节点
		default:p=(BTNode *)malloc(sizeof(BTNode));
				p->data=ch;p->lchild=p->rchild=NULL;
				if (b==NULL)                    	 	//*p为二叉树的根节点
					b=p;
				else  								//已建立二叉树根节点
				{
					switch(k)
					{
					case 1:St[top]->lchild=p;break;
					case 2:St[top]->rchild=p;break;
					}
				}
		}
		j++;
		ch=str[j];
	}
}
void destroyBTree(BTNode *&b)
{	if (b!=NULL)
	{	destroyBTree(b->lchild);
		destroyBTree(b->rchild);
		free(b);
	}
}

void dispBTree(BTNode *b) {
	if (b!=NULL)
	{	printf("%c",b->data);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{	printf("(");						//有孩子节点时才输出(
			dispBTree(b->lchild);				//递归处理左子树
			if (b->rchild!=NULL) printf(",");	//有右孩子节点时才输出,
			dispBTree(b->rchild);				//递归处理右子树
			printf(")");						//有孩子节点时才输出)
		}
	}
}

//先序中序构建二叉树
//pre存放先序，in存放中序,n为二叉树结点个数
//算法执行后返回构造二叉链的根结点指针
BTNode * createBT1(char *pre, char *in, int n){
  BTNode *s;
  char *p;
  int k;
  if(n <= 0) return NULL;
  s = (BTNode*)malloc(sizeof(BTNode));
  s -> data = *pre; //先序遍历首结点是根结点
  for(p = in; p < in + n; p++){//在中序序列中找到等于*ppos的位置k，即根结点在中序中的位置
    if(*p == *pre){
      break;//在中序in中找到后退出循环
    }
  }
  k = p - in; //确定根结点在中序in中的位置
  s -> lchild = createBT1(pre+1,in, k); //递归构造左子树
  s -> rchild = createBT1(pre+k+1,p+1,n-k-1);
  return s;
}

//中序、后序构造二叉树
//post存放后序序列，in存放中序序列
//n为二叉树结点个数
BTNode * createBT2(char *post, char *in, int n){
  BTNode *s;
  char r,*p;
  int k;
  if(n <= 0) return NULL;
  r = *(post+n-1);//根结点值
  s = (BTNode *)malloc(sizeof(BTNode));
  s -> data = r;
  for(p = in; p < in+n; p++){
    //在in中查找根结点
    if(*p == r)
      break;
  }
  k = p - in;//k为根结点在in中的下标
  s -> lchild = createBT2(post,in,k);//左子树
  s -> rchild = createBT2(post+k,p+1,n-k-1);
  return s;
}

int main(){
  ElemType pre[] = "ABDGCEF",in[]="DGBAECF",post[]="GDBEFCA";
  BTNode *b1,*b2;
  b1 = createBT1(pre,in,7);
  b2 = createBT2(post,in,7);
  printf("b1:");
  dispBTree(b1);
  printf("\n");
  printf("b2:");
  dispBTree(b2);
  printf("\n");
  destroyBTree(b1);
  destroyBTree(b2);
  return 1;
}
