//树的几种存储结构
#include <stdio.h>
#define MaxSize 100
typedef char ElemType;

//双亲存储结构
typedef struct {
  ElemType data;//结点的值
  int parent;//存放双亲的位置
} PTree[MaxSize];//PTree为双亲存储结构类型

#define MaxSons 3
//孩子链存储结构
typedef struct node {
  ElemType data;
  struct node * sons[MaxSons]; //指向孩子结点
} TSonNode;//孩子链存储结构中的结点类型

//孩子链表存储，求树的高度
int treeHeight1(TSonNode *t){
  TSonNode *p;
  int i,h,maxh=0;
  if(t == NULL)
    return 0;
  else {
    for(i = 0; i < MaxSons;i++){
      p = t -> sons[i];
      if(p != NULL){
        h = treeHeight1(p);
        if(maxh < h) maxh = h;
      }
    }
    return (maxh+1);
  }
}

//孩子兄弟链存储结构
typedef struct tnode {
  ElemType data;
  struct tnode *hp;//指向兄弟
  struct tnode *vp;//指向孩子结点
} TSBNode;

//孩子兄弟存储，树的高度
int treeHeight2(TSBNode *t){
  TSBNode *p;
  int h,maxh =0;
  if(t == NULL) return 0;
  else{
    p = t -> vp;//指向第一个孩子结点
    while(p != NULL){
      h = treeHeight2(p);
      if(maxh < h) maxh = h;
      p = p -> hp;
    }
    return (maxh+1);
  }
}
