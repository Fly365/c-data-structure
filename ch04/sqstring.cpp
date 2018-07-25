//顺序串基本运算算法
#include <stdio.h>
#define MaxSize 100

typedef struct {
  char data[MaxSize];
  int length;
} SqString;

//字符串常量赋给串 s
void strAssign(SqString &s, char csstr[]){
  int i;
  for(i = 0; csstr[i] != '\0'; i++){
    s.data[i] = csstr[i];
  }
  s.length = i;
}

void destoryStr(SqString &s){

}

void strCopy(SqString &s, SqString t){
  int i;
  for(i=0;i < t.length;i++)
    s.data[i] = t.data[i];
  s.length = t.length;
}

bool strEqual(SqString s, SqString t){
  bool same = true;
  int i;
  if(s.length != t.length){
    same = false;
  }else{
    for(i = 0; i < s.length;i++){
      if(s.data[i] != t.data[i]){
        same=false;
        break;
      }
    }
  }
  return same;
}

int strLength(SqString s){
  return s.length;
}

SqString concat(SqString s, SqString t){
  SqString str;
  int i;
  str.length = s.length + t.length;
  for(i = 0; i < s.length; i++){
    str.data[i] = s.data[i];
  }
  for(i=0; i< t.length; i++){
    str.data[s.length+i] = t.data[i];
  }
  return str;
}

SqString subStr(SqString s, int i, int j){
  SqString str;
  int k;
  str.length=0;
  if(i <= 0 || i > s.length || j < 0 || i+j-1 > s.length){
    return str;//参数不正确，返回空串
  }
  for(k = i-1; k< i+j-1; k++){
    str.data[k-i+1] = s.data[k];
  }
  str.length=j;
  return str;
}
