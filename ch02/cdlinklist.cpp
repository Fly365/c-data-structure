//循环双链表基本运算算法
#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct DNode {
  ElemType data;
  struct DNode *prior; //前驱结点
  struct DNode *next;
} DLinkNode;

void createListF(DLinkNode * &L, ElemType a[], int n){
  DLinkNode *s;
  int i;
  L = (DLinkNode *)malloc(sizeof(DLinkNode));
  L -> next = NULL;
  for(i = 0; i < n; i++){
    s = (DLinkNode *)malloc(sizeof(DLinkNode));
    s -> data = a[i];
    s -> next = L -> next;
    if(L -> next != NULL){
      L -> next -> prior = s;
    }
    L -> next = s;
    s -> prior = L;
  }
  s = L -> next;
  while(s -> next != NULL){
    s = s -> next;
  }
  s -> next = L;
  L -> prior = s;
}
//尾插法创建循环双链表
void createListR(DLinkNode * &L, ElemType a[], int n){
  DLinkNode *s, *r;
  int i;
  L = (DLinkNode *)malloc(sizeof(DLinkNode));
  L -> next = NULL;
  r = L;//r 始终指向尾结点，开始时指向头结点
  for(i = 0; i < n; i++){
    s = (DLinkNode *)malloc(sizeof(DLinkNode));
    s -> data = a[i];
    r -> next = s;
    s -> prior = r;
    r = s;
  }
  r -> next = L;
  L -> prior = r;
}

void initList(DLinkNode * &L){
  L = (DLinkNode *)malloc(sizeof(DLinkNode));
  L -> prior = L -> next = L;
}

void destoryList(DLinkNode * &L){
  DLinkNode *p = L, *q = L -> next;
  while(q != L){
    free(p);
    p = q ;
    q = p -> next;
  }
  free(q);
}

bool listEmpty(DLinkNode *L){
  return (L -> next == L);
}

int listLength(DLinkNode *L){
  DLinkNode *p = L;
  int i = 0;
  while(p -> next != L){
    p = p -> next;
    i++;
  }
  return i;
}

void dispList(DLinkNode *L){
  DLinkNode *p = L -> next;
  while(p != L){
    printf("%d ",  p -> data);
    p = p -> next;
  }
  printf("\n");
}

bool getElem(DLinkNode *L, int i, ElemType &e){
  int j = 0;
  DLinkNode *p;
  if(L -> next != L){
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

int locateElem(DLinkNode *L, ElemType e){
  int i = 1;
  DLinkNode *p = L -> next;
  while(p != L && p -> data != e){
    i++;
    p = p -> next;
  }
  if(p == L){
    return 0;
  }else{
    return i;
  }
}

bool listInsert(DLinkNode *L, int i, ElemType e){
  int j = 0;
  DLinkNode *p = L, *s;
  if(p -> next == L){
    s = (DLinkNode *)malloc(sizeof(DLinkNode));
    s -> data = e;
    p -> next = s;
    s -> next = p;
    p -> prior = s;
    s -> prior = p;
    return true;
  }else if(i == 1){
    s = (DLinkNode *)malloc(sizeof(DLinkNode));
    s -> data = e;
    s -> next = p -> next;
    p -> next = s;
    s -> next -> prior = s;
    s -> prior = p;
    return true;
  }else{
    p = L -> next;
    while(j < i -2 && p != L){
      j++;
      p = p -> next;
    }
    if(p == L){
      return false;
    }else{
      s = (DLinkNode *)malloc(sizeof(DLinkNode));
      s -> data = e;
      s -> next = p -> next;
      if(p -> next != NULL) p -> next -> prior = s;
      s -> prior = p;
      p -> next = s;
      return true;
    }
  }
}

bool listDelete(DLinkNode *L, int i, ElemType &e){
  int j = 0;
  DLinkNode *p = L,*q;
  if(p -> next != L){
    if(i == 1){
      q = L -> next;
      e = q -> data;
      L -> next = q -> next;
      q -> next -> prior = L;
      free(q);
      return true;
    }else{
      p = L -> next;
      while(j < i -2 && p != L){
        j++;
        p = p -> next;
      }
      if(p == L){
        return false;
      }else{
        q = p -> next;
        if(q == L) return false;
        e = q -> data;
        p -> next = q -> next;
        if(p -> next != L) p -> next -> prior = p;
        free(q);
        return true;
      }
    }
  }
  return false;
}
