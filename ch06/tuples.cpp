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
bool value(TSMatrix &t, ElemType x, int i, int j){
  int k =0, k1;
  if(i > t.nums || j >= t.cols)
    return false;
  while(k < t.nums && i > t.data[k].r) k++; //查找元素所对应的行
  while(k < t.nums && i == t.data[k].r && j > t.data[k].c) k++;//查找元素所在行后对应的列
  if(t.data[k].r == i && t.data[k].c == j){
    t.data[k].d = x;//存在元素
  }else{//不存在元素时，新增加入一个元素
    for(k1=t.nums-1; k1>=k; k1--){
      t.data[k1+1].r = t.data[k1].r;
      t.data[k1+1].c = t.data[k1].c;
      t.data[k1+1].d = t.data[k1].d;
    }
    t.data[k].r = i;
    t.data[k].c = j;
    t.data[k].d = x;
    t.nums++;
  }
  return true;
}

//将指定位置的元素赋给变量
bool assign(TSMatrix t, ElemType &x, int i, int j){
  int k = 0;
  if(i > t.rows || j > t.cols)
    return false;
  while(k < t.nums && i > t.data[k].r) k++;//查找元素所对应的行
  while(k < t.nums && i == t.data[k].r && j > t.data[k].c) k++;//查找元素所在行后对应的列
  if(t.data[k].r == i && t.data[k].c == j)
    x = t.data[k].d;
  else
    x = 0; //没有找到
  return true;
}

//输出三元组
void dispMat(TSMatrix t){
  int i;
  if(t.nums <= 0)
    return;
  printf("\t%d\t%d\t%d\n",t.rows,t.cols,t.nums);
  for(i = 0; i < t.nums; i++){
    printf("\t%d\t%d\t%d\n",t.data[i].r,t.data[i].c,t.data[i].d);
  }
}

//矩阵转置
void tranTat(TSMatrix t, TSMatrix &tb){
  int p,q=0,v; //q为 tb.data的下标
  tb.rows = t.cols;
  tb.cols = t.rows;
  tb.nums = t.nums;
  if(t.nums > 0){//当存在非零元素时执行转置
    for(v=0; v < t.cols; v++){
      for(p=0; p < t.nums;p++){
        if(t.data[p].c == v){
          tb.data[q].r = t.data[p].c;
          tb.data[q].c = t.data[p].r;
          tb.data[q].d = t.data[p].d;
          q++;
        }
      }
    }
  }
}

int main(){
  TSMatrix t, tb;
  int x,y=10;
  int A[6][7]={
    {0,0,1,0,0,0,0},
		{0,2,0,0,0,0,0},
		{3,0,0,0,0,0,0},
		{0,0,0,5,0,0,0},
		{0,0,0,0,6,0,0},
		{0,0,0,0,0,7,4}
  };
  creatMat(t,A);
  printf("b:\n");
  dispMat(t);
  if(assign(t,x,2,5) == true){
    printf("assign(t,x,2,5)=>x=%d\n", x);
  }else{
    printf("assign(t,x,2,5)=>参数错误\n");
  }

  value(t,y,2,5);
  printf("执行value(t,10,2,5)\n");

  dispMat(t);
  tranTat(t,tb);
  printf("tb:\n");
  dispMat(tb);
  return 1;
}
