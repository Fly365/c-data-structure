//稀疏矩阵十字链表表示
#include <stdio.h>
#include <malloc.h>
#define M 3 //矩阵行
#define N 4 //矩阵列
#define Max ((M) > (N) ? (M) : (N)) //三目运算符，矩阵行列较大者

typedef int ElemType;

typedef struct mtxn{
  int row;
  int col;
  struct mtxn *right, *down; //向右和 向下的指针
  union {
    ElemType value;
    struct mtxn *link;
  }tag;
} MatNode; //十字链表类型

//创建十字链表
void creatMat(MatNode * &mh, ElemType a[M][N]){
  int i, j;
  MatNode * h[Max],*p,*q,*r;
  mh = (MatNode *)malloc(sizeof(MatNode));//十字链表头结点
  mh -> row = M;
  mh -> col = N;
  r = mh;// r指向尾结点
  for(i=0; i< Max; i++){//尾插法创建头结点h1,h2...循环链表
    h[i] = (MatNode *)malloc(sizeof(MatNode));
    h[i] -> down = h[i] -> right = h[i];//将down和right方向置为循环的
    r -> tag.link = h[i]; //将h[i]加到链表
    r = h[i];
  }
  r -> tag.link = mh; //置为循环链表
  for(i=0; i < M; i++){
    for(j=0; j < N; j++){
      if(a[i][j] != 0){
        p = (MatNode *)malloc(sizeof(MatNode));
        p -> row = i;
        p -> col = j;
        p -> tag.value = a[i][j];
        q = h[i];
        while(q -> right != h[i] && q -> right -> col < j){
          q = q -> right;
        }
        p -> right = q -> right;
        q -> right = p;
        q = h[j];
        while(q -> down != h[j] && q -> down -> row < i){
          q = q -> down;
        }
        p -> down = q -> down;
        q -> down = p;
      }
    }
  }
}
