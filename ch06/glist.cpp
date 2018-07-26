//广义表基本运算算法
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct lnode {
  int tag; //结点类型表示，tag为0原子结点，tag为1表示该结点为表/子表结点
  union{
    ElemType data;//原子值
    struct lnode *sublist;//指向子表的指针
  }val;
  struct lnode *link;//指向下一个元素
}GLNode;

//广义表长度
int GLLength(GLNode *g){
  int n = 0;
  GLNode *gl;
  gl = g -> val.sublist;//g指向广义表第一个元素
  while(gl != NULL){
    n++;
    gl = gl -> link;
  }
  return n;
}

//广义表深度
int GLDepth(GLNode *g){
  GLNode *gl;
  int maxd=0,dep;
  if(g -> tag == 0)
    return 0;//为原子时返回0
  gl = g -> val.sublist;//指向第一个元素
  if(gl == NULL)
    return 1; //空表
  while(gl != NULL){//元素为子表情况
    if(gl -> tag == 1){
      dep = GLDepth(gl);//递归求出子表深度
      if(dep > maxd)
        maxd = dep;
    }
    gl = gl -> link;//指向下一个元素
  }
  return (maxd + 1);
}

//创建由括号表示法表示s的广义表链式存储结构
GLNode *createGL(char *&s){
  GLNode *g;
  char ch = *s++; //取一个字符
  if(ch != '\0'){
    g = (GLNode *)malloc(sizeof(GLNode));
    if(ch != '('){//当前字符为左括号时
      g -> tag = 1;
      g -> val.sublist = createGL(s);//构造子表
    }else if(ch == ')'){
      g = NULL;
    }else if(ch == '#'){//遇到#表示为空表
      g = NULL;
    }else {
      g -> tag = 0;
      g -> val.data = ch;
    }
  }else
    g = NULL;
  ch = *s++;//取下一个字符
  if(g != NULL){
    if(ch == ','){
      g -> link = createGL(s);
    }else{
      g -> link = NULL;
    }
  }
  return g;
}
