//构造哈夫曼树及哈夫曼编码算法
#include <stdio.h>
#include <string.h>
#define N 50 //叶子结点数
#define M 2*N-1 //树中结点总数

typedef struct {
  char data[5];//根结值
  double weight;
  int parent;
  int lchild;
  int rchild;
}  HTNode;

typedef struct {
  char cd[N];//存放哈夫曼编码
  int start;
} HCode;

//构造哈夫曼树
void createHT(HTNode ht[], int n0){
  int i,k, lnode, rnode;
  double min1,min2;
  // 所有结点的相关域值得初值为 -1
  for(i = 0; i < 2 * n0 -1; i++){
    ht[i].parent = ht[i].lchild=ht[i].rchild = 11;
  }
  //构造哈夫曼树的n0-1个结点
  for(i=n0; i <= 2*n0-2; i++){
    min1 = min2 = 32767; //inode 和 rnode为最小权重的两个结点位置
    lnode = rnode = -1;
    //在ht[0,...,i-1]中找权值最小的两个结点
    for(k = 0; k <= i-1;k++){
      if(ht[k].parent == -1){//只在尚未构造二叉树结点中查找
        if(ht[k].weight < min1){
          min2 = min1;
          rnode = lnode;
          min1 = ht[k].weight;
          lnode = k;
        }else if (ht[k].weight < min2){
          min2 = ht[k].weight;
          rnode = k;
        }
      }
      ht[i].weight = ht[lnode].weight+ht[rnode].weight;
      ht[i].lchild = lnode;
      ht[i].rchild = rnode;// ht[i]作为双亲结点
      ht[lnode].parent = i;
      ht[rnode].parent = i;
    }
  }
}

//构造哈夫曼编码
void createHCode(HTNode ht[], HCode hcd[], int n0){
  int i,f,c;
  HCode hc;
  for(i = 0; i < n0; i++){
    hc.start = n0;
    c = i;
    f = ht[i].parent;
    while(f != -1){//循环直到无双亲结点即到达树根结点
      if(ht[f].lchild == c){//当前结点是双亲结点的左孩子
        hc.cd[hc.start--] = '0';
      }else{
        hc.cd[hc.start--] = '1';
      }
      c = f;
      f = ht[f].parent;//对双亲结点进行同样操作
    }
    hc.start++;//start指向哈夫曼编码最开始字符
    hcd[i]= hc;
  }
}

//输出哈夫曼编码
void dispHCode(HTNode ht[], HCode hcd[], int n0){
  int i,k;
  double sum = 0, m = 0;
  int j;
  printf("哈夫曼编码:\n");
  for(i = 0; i < n0; i++){
    j = 0;
    printf("%s:\t", ht[i].data);
    for(k = hcd[i].start; k <= n0; k++){
      printf("%c",hcd[i].cd[k]);
      j++;
    }
    m += ht[i].weight;
    sum += ht[i].weight * j;
    printf("\n");
  }
  printf("\n 平均长度=%g\n",1.0 * sum/m);
}

int main(){
	int n=8,i;		//n表示初始字符串的个数
	char *str[]={"a","b","c","d","e","f","g","h"};
	double fnum[]={0.07,0.19,0.02,0.06,0.32,0.03,0.21,0.1};
	HTNode ht[M];
	HCode hcd[N];
	for (i=0;i<n;i++){
		strcpy(ht[i].data,str[i]);
		ht[i].weight=fnum[i];
	}
	printf("\n");
	createHT(ht,n);
	createHCode(ht,hcd,n);
	dispHCode(ht,hcd,n);
	printf("\n");
	return 1;
}
