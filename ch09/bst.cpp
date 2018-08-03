//二叉排序树算法
#include <stdio.h>
#include <malloc.h>

typedef int KeyType;
typedef char InfoType[10];
typedef struct node {
  KeyType key;//关键字项
  InfoType data;//其他数据域
  struct node *lchild,*rchild;//左右孩子指针
} BSTNode;//二叉排序树结点类型

bool insertBST(BSTNode *bt, KeyType k){
  if(bt == NULL){
    bt = (BSTNode *)malloc(sizeof(BSTNode));
    bt -> key = k;
    bt -> lchild = bt -> rchild = NULL;
    return true;
  }
  else if(k == bt-> key)
    return false;
  else if(k < bt -> key)
    return insertBST(bt->lchild,k);//插入到左子树
  else
    return insertBST(bt -> rchild, k);//插入到右子树
}

//创建二叉排序树
BSTNode * createBST(KeyType A[], int n){
  BSTNode *bt = NULL;
  int i = 0;
  while(i < n){
    insertBST(bt, A[i]);
    i++;
  }
  return bt;
}

//输出二叉排序树
void dispBST(BSTNode *bt){
  if(bt != NULL){
    printf("%d", bt->key);
    if(bt->lchild != NULL || bt->rchild != NULL){
      printf("(");
      dispBST(bt -> lchild);
      if(bt->rchild != NULL) printf(",");
      dispBST(bt->rchild);
      printf(")");
    }
  }
}

//查找
BSTNode * searchBST(BSTNode *bt, KeyType k){
  if(bt == NULL || bt->key==k)
    return bt;
  if(k < bt->key)
    return searchBST(bt->lchild,k);
  else
    return searchBST(bt->rchild,k);
}

/*
  在bt中查找关键字为k的结点，若查找成功，该函数返回该结点的指针，
  f返回其双亲结点；否则，该函数返回NULL。
  其调用方法如: searchBST2(bt,x,NULL,f);
  这里的第三个参数f1仅作中间参数，用于求f，初始值为NULL
*/
BSTNode * searchBST2(BSTNode *bt,KeyType k, BSTNode *f1, BSTNode *&f){
  if(bt == NULL){
    f = NULL;
    return NULL;
  }else if(k == bt->key){
    f = f1;
    return bt;
  }else if(k < bt->key){
    return searchBST2(bt->lchild,k,bt,f);//左子树查找
  }
  else
    return searchBST2(bt->rchild,k,bt,f);
}

//删除的p结点有左右子树时的情况
void deleteContainLAndRChild(BSTNode *p, BSTNode *&r){
  BSTNode *q;
  if(r->rchild != NULL)
    deleteContainLAndRChild(p,p->rchild);//递归找到最右下结点r
  else{
    p->key=r->key;//将结点的值赋给结点p
    q = r;
    r = r->lchild;//直接将其右子树的根节点放在被删结点的位置上
    free(q);
  }
}

//二叉树中删除P结点
void deleteOpt(BSTNode *&p){
  BSTNode *q;
  if(p->rchild == NULL){
    //p结点没有右子树情况
    q = p;
    p = p->lchild;//直接将其右子树的根节点放在被删结点的位置上
    free(q);
  }else if(p->lchild == NULL){
    //p结点没有左子树
    q = p;
    p = p -> rchild;//将p结点的右子树作为双亲结点的相应子树
    free(q);
  }else
    deleteContainLAndRChild(p,p->lchild);//p结点既没有左子树又没有右子树情况
}

int deleteBST(BSTNode *&bt, KeyType k){
  if(bt == NULL)
    return 0;
  else{
    if(k < bt->key)
      return deleteBST(bt->lchild,k);//递归左子树中删除为k的结点
    else if(k > bt->key)
      return deleteBST(bt->rchild,k);
    else{
      deleteOpt(bt);
      return 1;
    }
  }
}

void destoryBST(BSTNode *&bt){
  if(bt != NULL){
    destoryBST(bt->lchild);
    destoryBST(bt->rchild);
    free(bt);
  }
}

/*int main(){
  BSTNode *bt,*p,*f;
	int n=12,x=46;
	KeyType a[]={25,18,46,2,53,39,32,4,74,67,60,11};
	bt=createBST(a,n);
	printf("BST:");dispBST(bt);printf("\n");
	printf("删除%d结点\n",x);
	if (searchBST(bt,x)!=NULL)
	{
		deleteBST(bt,x);
		printf("BST:");dispBST(bt);printf("\n");
	}
	x=18;
	p=searchBST2(bt,x,NULL,f);
	if (f!=NULL)
		printf("%d的双亲是%d\n",x,f->key);
	destoryBST(bt);
	return 1;
}*/
