//循环单链表基本运算算法
#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LinkNode;

//头插法建立循环单链表
void createListF(LinkNode * &L, ElemType a[], int n){
  LinkNode *s;
  int i;
  L = (LinkNode *)malloc(sizeof(LinkNode));//创建头结点
  L -> next = NULL;
  for(i = 0; i < n; i++){
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = a[i];
    if(L -> next == NULL){
      s -> next = L;
    }else{
      s -> next = L -> next;
    }
    L -> next = s;
  }
}

//尾插法建立玄幻链表
void createListR(LinkNode * &L, ElemType a[], int n){
  LinkNode *s, *r;
  int i;
  L = (LinkNode *)malloc(sizeof(LinkNode));
  L -> next = NULL;
  r = L;//r始终指向终端结点,开始指向头结点
  for(i = 0; i < n; i++){
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = a[i];
    r -> next = s;
    r = s;
  }
  r -> next = L;
}

//初始化链表
void initList(LinkNode * &L){
  L = (LinkNode *)malloc(sizeof(LinkNode));
  L -> next = L;
}

//销毁链表
void destoryList(LinkNode * &L){
  LinkNode *p = L, *q = p -> next;//记录当前结点和下一个结点
  while(q != L){
    free(p);
    p = q;
    q = p -> next;
  }
  free(q);
}

//链表是否为空
bool listEmpty(LinkNode *L){
  return (L -> next == L);
}

//链表的长度
int listLength(LinkNode *L){
  LinkNode *p = L;
  int i = 0;
  while(p -> next != L){
    i++;
    p = p -> next;
  }
  return i;
}

//输出链表
void dispList(LinkNode *L){
  LinkNode *p = L -> next;
  while(p != L){
    printf("%d ", p -> data);
    p = p -> next;
  }
  printf("\n");
}

//获取指定位置元素
bool getElem(LinkNode *L, int i, ElemType &e){
  if(i < 0) return false;
  LinkNode *p;
  int j = 0;
  if(L -> next != L){ //链表不为空时
    if(i == 1){
      e = L -> next -> data;
      return true;
    }else{
      p = L -> next;
      while(j < i-1 && p != L){
        j++;
        p = p -> next;
      }
      if(p == L){
        return false;
      }else{
        e = p -> data;
        return true;
      }
    }
  }
  return false;
}

//获取某个元素的相等第一个匹配的索引位置
int locateElem(LinkNode *L, ElemType e){
  LinkNode *p = L -> next;
  int n = 1;
  while(p != L && p -> data != e){
    n++;
    p = p -> next;
  }
  if(p == L)
    return 0;
  else
    return n;
}

//元素新增
bool listInsert(LinkNode * &L, int i, ElemType e){
  int j = 0;
  LinkNode *p = L, *s;
  if(p -> next == L || i == 1){
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = e;
    s -> next = p -> next;
    L -> next = s;
    return true;
  }else{
    p = L -> next;
    while(p != L && j < i - 2){
      p = p -> next;
      j++;
    }
    if(p == L){//未找到 i-1 个结点
      return false;
    }
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = e;
    s -> next = p -> next;
    p -> next = s;
    return true;
  }
}

//删除指定位置元素的结点
bool listDelete(LinkNode * &L, int i, ElemType &e){
  int j = 0;
  LinkNode *p = L,*q;
  if(p -> next != L){
    if(i == 1){
      q = L -> next;
      e = q -> data;
      p -> next = q -> next;
      free(q);
      return true;
    }else{
      p = p -> next;
      while(p != L && j < i-2){
        p = p -> next;
        j++;
      }
      if(p == L){
        return false;
      }
      q = p -> next;
      e = q -> data;
      p -> next = q -> next;
      free(q);
      return true;
    }
  }
  return false;
}
