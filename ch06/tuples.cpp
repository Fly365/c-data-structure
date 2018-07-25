//稀疏矩阵三元组表示
#include <stdio.h>
#define M 6 //稀疏矩阵行数
#define N 7 //稀疏矩阵列数
#define MaxSize 100  //稀疏矩阵中非零元素最多的个数

typedef int ElemType;

typedef struct {
  int r; //行号
  int c;//列号
  ElemType d; //元素值
} TupNode; //三元组定义
typedef struct {
  int rows; //行数
  int cols;//列数
  int nums;//非零元素个数
  TupNode data[MaxSize];
} TSMatrix; //三元组顺序表

//从一个二维稀疏矩阵创建其三元组表示
void creatMat(TSMatrix &t, ElemType A[M][N]){
  int i,j;
  t.rows=M;
  t.cols=N;
  t.nums=0;
  for(i=0; i < M; i++){//只存储非零元素
    for(j=0; j < N; j++){
      if(A[i][j] != 0){
        t.data[t.nums].r = i;
        t.data[t.nums].c = j;
        t.data[t.nums].d = A[i][j];
        t.nums++;
      }
    }
  }
}

//三元组元素赋值
