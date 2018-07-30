//图的存储结构及其基本运算算法
#include <stdio.h>
#include <malloc.h>
#define INF  32767 // 定义∞
#define MAXV 100 //最大顶大个数
typedef char InfoType;

//邻接矩阵类型
typedef struct {
  int no;//顶点编号
  InfoType info;//顶点其他信息
} VertexType; //顶点类型
typedef struct {
  int edges[MAXV][MAXV];//邻接矩阵数组
  int n,e;//顶点数，边数
  VertexType vexs[MAXV];//存放顶点信息,顶点信息存放
} MatGraph;//完整图邻接矩阵类型

//邻接表类型
typedef struct ANode {
  int adjvex;//边的邻接点编号
  struct ANode *nextarc;//指向下一条边的指针
  int weight;//边的相关信息，权值
} ArcNode;//边的结点类型
typedef struct Vnode {
  InfoType info;//顶点其他信息
  int count;//顶点入度，仅仅用于拓扑排序
  ArcNode *firstarc;//指向第一条边
} VNode; //邻接表头结点类型
typedef struct {
  VNode adjlist[MAXV];//邻接表头结点数组
  int n,e;//图中顶点数n和边数e
} AdjGraph;

//------------图基本运算------------
//邻接矩阵 创建
void createMat(MatGraph &g, int A[MAXV][MAXV], int n, int e){
  int i,j;
  g.n = n,g.e = e;
  for(i = 0; i < g.n; i++){
    for(j = 0; j < g.n; j++){
      g.edges[i][j] = A[i][j];
    }
  }
}

//邻接矩阵 输出
void dispMat(MatGraph g){
  int i,j;
  for(i = 0; i < g.n; i++){
    for(j = 0; j < g.n; j++){
      if(g.edges[i][j] != INF){
        printf("%4d",g.edges[i][j]);
      }else{
        printf("%4s","∞");
      }
    }
    printf("\n");
  }
}

//邻接表创建
void createAdj(AdjGraph *&G,int A[MAXV][MAXV],int n,int e){
  int i,j;
  ArcNode *p;
  G = (AdjGraph *)malloc(sizeof(AdjGraph));
  for(i = 0; i < n; i++){
    G -> adjlist[i].firstarc = NULL;//邻接表中所有头结点的指针域设置初值
  }
  for(i = 0; i < n; i++){
    for(j = n-1; j >= 0; j--){
      if(A[i][j] != 0 && A[i][j] != INF){//存在一条边
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p -> adjvex = j;
        p -> weight = A[i][j];
        p -> nextarc = G -> adjlist[i].firstarc;//头插法加入结点p
        G -> adjlist[i].firstarc = p;
      }
    }
  }
  G -> n = n;
  G -> e = n;
}

//输出邻接表
void dispAdj(AdjGraph *G){
  int i;
  ArcNode *p;
  for(i = 0; i < G->n; i++){
    p = G -> adjlist[i].firstarc;//获取单链表的首结点
    printf("%3d: ",i);
    while(p != NULL){
      printf("%3d[%d]->", p-> adjvex, p -> weight);
      p = p -> nextarc;
    }
    printf("^\n");
  }
}

//销毁邻接表
void destoryAdj(AdjGraph *&G){
  int i;
  ArcNode *pre, *p;
  for(i = 0; i < G-> n; i++){
    pre = G -> adjlist[i].firstarc;//获取链表的首结点
    if(pre != NULL){
      p = pre -> nextarc;
      while(p != NULL){
        free(pre);
        pre = p;
        p = p -> nextarc;
      }
      free(pre);
    }
  }
  free(G);
}
