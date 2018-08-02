#include <stdio.h>
#define MAXL 100 //最大长度
typedef int KeyType; //关键字类型为int
typedef char InfoType;

typedef struct {
  KeyType key;//关键字项
  InfoType data;//其他数据项，类型为InfoType
} RecType;//查找元素的类型

//顺序表基本运算算法
void createList(RecType R[], KeyType keys[], int n){
  for(int i=0; i<n; i++){
    R[i].key = keys[i];
  }
}

//输出顺序表
void dispList(RecType R[], int n){
  for(int i=0; i<n; i++)
    printf("%d ",R[i].key);
  printf("\n");
}


//----------顺序查找算法-----------------------
int seqSearch(RecType R[],int n, KeyType k){
  int i = 0;
  while(i < n && R[i].key != k)
    i++;
  if(i>=n)
    return 0;
  else
    return i+1;
}

//顺序查找，增加哨兵,这样可以减少判断条件
int seqSearch2(RecType R[], int n, KeyType k){
  int i = 0;
  R[n].key = k;
  while(R[i].key != k)
    i++;
  if(i == n)
    return 0;//未找到
  else
    return i+1;
}

//顺序表校验
void cheackSeqSearch(){
  int n = 0;
  RecType R[MAXL];
  KeyType a[] = {2,3,1,8,5,4,9,0,7,6},k=9;
  createList(R,a,n);
  printf("查找表:");
  dispList(R,n);
  printf("R[%d]=%d\n",seqSearch(R,n,k),k);
}

//----------二分查找--------------
int binSearch(RecType R[], int n, KeyType k){
  int low =0,high = n-1,mid;
  while(low <= high){//当前区间存在元素时循环
    mid = (low+high)/2;
    if(k == R[mid].key)
      return mid+1;//成功查找到
    if(k < R[mid].key)
      high = mid-1;
    else
      low=mid+1;
  }
  return 0;
}

//二分查找校验
void checkBinSearch(){
  int n=11;
	RecType R[MAXL];
	KeyType a[]={2,3,10,15,20,25,28,29,30,35,40},k=20;
	createList(R,a,n);
	printf("查找表："); dispList(R,n);
	printf("R[%d]=%d\n",binSearch(R,n,k),k);
}

//---------分块查找算法-----------
#define MAXI 20//索引表的最大长度
typedef struct{
  KeyType key;//KeyType为关键字的类型
  int link;//指向对应块的起始下标
} IdxType;//索引表元素类型

//分块查找
// b-所分块数  n-元素的总个数
int idxSearch(IdxType I[],int b, RecType R[], int n, KeyType k){
  int s = (n+b-1)/b;//s为每块的元素个数，因为n/b的向上取整
  int low=0,high=b-1,mid,i;
  while(low <= high){
    mid = (low+high)/2;
    if(I[mid].key >= k)
      high = mid+1;
    else
      low = mid+1;
  }
  //应在索引表的high+1块中，再在主数据表中进行顺序查找
  i = I[high+1].link;
  while(i <= I[high+1].link+s-1 && R[i].key != k)
    i++;
  if(i <= I[high+1].link+s-1)
    return i+1;
  else
    return 0;
}

//校验分块查找
void checkIdxSearch(){
  int n=25,b=5,j;
	RecType R[MAXL];
	IdxType I[MAXI]={{14,0},{34,5},{66,10},{85,15},{100,20}};
	KeyType a[]={8,14,6,9,10,22,34,18,19,31,40,38,54,66,46,71,78,68,80,85,100,94,88,96,87};
	KeyType k=85;
	createList(R,a,n);
	printf("查找表："); dispList(R,n);
	j=idxSearch(I,b,R,n,k);
	if (j!=-1)
		printf("R[%d]=%d\n",j,k);
	else
		printf("未找到%d\n",k);
}
