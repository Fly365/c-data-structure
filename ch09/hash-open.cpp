//开放地址法构造哈希表
#include <stdio.h>
#define MaxSize 100 //定义哈希表长度
#define NULLKEY -1 //定义空关键字值
#define DELKEY -2 //定义被删除关键字值

typedef int KeyType; //关键字类型
typedef struct {
  KeyType key;//关键字域
  int count;//探测次数域
} HashTable;

//将关键字 k 插入到哈希表中
void insertHT(HashTable ha[], int &n, int m,int p, KeyType k){
  int i,adr;
  adr = k % p; //计算哈希函数值
  if(ha[adr].key == NULLKEY || ha[adr].key == DELKEY){
    //k直接放在哈希表中
    ha[adr].key = k;
    ha[adr].count = 1;
  }else{
    //发生冲突时采用线性探测法解决冲突
    i = 1;//i记录k发生冲突次数
    do {
      adr = (adr+1) % m; //线性探测
      i++;
    }while(ha[adr].key != NULLKEY && ha[adr].key != DELKEY);
    ha[adr].key = k;
    ha[adr].count = i;
  }
  n++; //关键字个数增1
}

void createHT(HashTable ha[], int &n, int m, int p, KeyType keys[], int n1){
  for(int i=0;i<m;i++){
    //哈希表置空并设置初值
    ha[i].key = NULLKEY;
    ha[i].count = 0;
  }
  n = 0;
  for(int i=0;i < n1; i++){
    insertHT(ha,n,m,p,keys[i]);//插入n1个关键字
  }
}
