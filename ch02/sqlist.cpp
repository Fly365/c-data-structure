// 顺序表的基本运算算法
#include <stdio.h>
#include <malloc.h>

#define MaxSize 50
typedef int ElemType;

typedef struct{
  ElemType data[MaxSize];
  int length;
}SqList; // 顺序表类型

// 创建顺序表
/*
  当调用下面算法创建好 L 所指定的顺序表后，需要回传给对应的实参，
  也就是说， L是输出型参数，所以在形参L的前面需要加上 引用符 &
  *&符号，从右往左读 进行理解
*/
void createList(SqList * &L, ElemType a[], int n){
  int i = 0, k = 0;
  L = (SqList *)malloc(sizeof(SqList));
  while(i < n){
    L -> data[k] = a[i];
    k++;
    i++;
  }
  L -> length = k;
}

//初始化线性表,构造一个空的线性表
// 只需分配线性表的存储空间并将length域设置为0即可
void initList(SqList * &L){
  L = (SqList *)malloc(sizeof(SqList));
  L -> length = 0;
}

// 销毁线性表
// 这里是使用malloc函数分配存储空间的，当不需要顺序表时务必用
//destoryList基本运算释放其存储空间
void destoryList(SqList * &L){
  free(L);
}

// 判断线性表是否为空
bool listEmpty(SqList *L){
  return (L -> length == 0);
}

// 线性表长度
int listLength(SqList *L){
  return (L -> length);
}

// 输出打印线性表
void dispList(SqList *L){
  for(int i = 0; i < L -> length; i++){
    printf("%d\t", L -> data[i]);
  }
}

// 求线性表某个数据元素值
// 运算使用引用型参数e 返回L中第i个元素的值
bool getElem(SqList *L, int i, ElemType &e){
  if(i < 1 || i > L -> length){
    return false;
  }
  e = L -> data[i-1];
  return true;
}

// 按元素值查找第一个值与e相等的元素的逻辑序号
// 找到返回一个大于0值，否则返回0
int locateElem(SqList *L, ElemType e){
  int i = 0;
  while(i < L -> length && L -> data[i] != e)
    i++;
  if(i >= L -> length)
    return 0;
  else
    return i+1;
}

// 插入数据元素,在i位置上插入新元素e
//该算法主要时间花费在元素移动上，因此平均时间复杂度为O(n)
bool listInsert(SqList * &L, int i, ElemType e){
  int j;
  if(i < 1 || i > L -> length)
    return false;
  i--; // 将顺序表逻辑序号转化为物理序号
  for(j = L -> length; j > i; j--)
    L -> data[j] = L -> data[j - 1];
  L -> data[i] = e;
  L -> length++;
  return true;
}

// 删除元素
bool listDelete(SqList * &L, int i, ElemType &e){
  int j;
  if(i < 1 || i > L -> length)
    return false;
  i--;
  e = L -> data[i];
  for(j = i; j < L -> length-1; j++)
    L -> data[j] = L -> data[j+1];
  L -> length--;
  return true;
}

//删除元素等于x元素，要求时间复杂度为O(n),空间复杂度为 O(1)
void delNode1(SqList * &L,ElemType x){
  int k=0,i;// k记录不等于x的元素的个数，即要插入到L中的元素的个数
  for(i = 0; i < L -> length; i++){
    if(L -> data[i] != x){
      L -> data[k] = L -> data[i];
      k++;
    }
  }
  L -> length = k;
}
