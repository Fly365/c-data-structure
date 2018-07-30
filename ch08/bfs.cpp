//广度优先遍历
#include "graph.cpp"
#define MaxSize 100

//广度优先遍历使用队列基本运算算法
typedef int ElemType;
typedef struct {
  ElemType data[MaxSize];
  int front,rear;//队尾队首指针
}SqQueue;

void initQueue(SqQueue * &q){
  q = (SqQueue *)malloc(sizeof(SqQueue));
  q -> front = q -> rear = 0;
}

void destoryQueue(SqQueue *&q){
  free(q);
}

bool queueEmpty(SqQueue *q){
  return (q -> front == q -> rear);
}

bool enQueue(SqQueue * &q, ElemType e){
  if((q -> rear + 1) % MaxSize == q -> front)
    return false;
  q -> rear = (q -> rear + 1)%MaxSize;
  q -> data[q ->rear] = e;
  return true;
}

bool deQueue(SqQueue *&q, ElemType &e){
  if(q -> front == q -> rear)
    return false;
  q -> front = (q -> front + 1) % MaxSize;
  e = q -> data[q -> front];
  return true;
}

//广度优先遍历
void BFS(AdjGraph *G, int v){
  int w,i;
  ArcNode *p;
  SqQueue *qu;//定义环形队列指针
  initQueue(qu);
  int visited[MAXV];
  for(i = 0; i < G -> n; i++)
    visited[i] = 0;//访问标志数组初始化
  printf("%2d", v);//输出被访问顶点的编号
  visited[v] = 1;
  enQueue(qu,v);
  while(!queueEmpty(qu)){
    deQueue(qu,w);
    p = G -> adjlist[w].firstarc;//指向w的第一个邻接点
    while(p != NULL){
      if(visited[p -> adjvex] == 0){
        printf("%2d", p -> adjvex);
        visited[p -> adjvex] = 1;
        enQueue(qu, p -> adjvex);
      }
      p = p -> nextarc;
    }
  }
  printf("\n");
}

int main(){
  AdjGraph *G;
  int A[MAXV][MAXV]={{0,1,0,1,1},{1,0,1,1,0},
			{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0}};
	int n=5, e=8;
  createAdj(G,A,n,e);
  printf("图G的邻接表:\n");
  dispAdj(G);
  printf("广度优先遍历:");
  BFS(G,2);
  printf("\n");
  destoryAdj(G);
  return 1;  
}
