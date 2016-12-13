#include <stdio.h>
#include <stdlib.h>
#define MAX 30
#define N 30
#define M 10
int visited[MAX]={0};

typedef struct ebox
{
    int ivex,jvex; //该边依附两个顶点的位置
    struct ebox *ilink,*jlink;//分别指向依附这两个顶点的下一条边
}ebox,*pebox;
typedef struct vexbox
{
    char *data;
    pebox firstedge;//指向第一条依附该顶点的边
}vexbox,*pvexbox;
typedef struct amlgraph//邻接多重表
{
    vexbox adjmulist[MAX];
}amlgraph,*pamlgraph;
typedef struct QNode//链式队列
{
    int data;
    struct QNode*next;
}QNode,*QueuePtr;
typedef struct
{
    QueuePtr front;//队头指针
    QueuePtr rear;//队尾指针
}LinkQueue;
LinkQueue InitQueue()//构造一个空队列Q
{
    LinkQueue Q;
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
    Q.front->next=NULL;
    return Q;
}
int DeQueue(LinkQueue*Q)//队列不为空时，删除队头元素
{
    QueuePtr p;
    int e;
    p=Q->front->next;
    e=p->data;
    Q->front->next=p->next;
    if(Q->rear==p)
    Q->rear=Q->front;
    free(p);
    return e;
}
void EnQueue(LinkQueue*Q,int e)//插入e为新的队尾元素
{
    QueuePtr p;
    p=(QueuePtr)malloc(sizeof(QNode));
    p->data=e;
    p->next=NULL;
    Q->rear->next=p;
    Q->rear=p;
}
int QueueEmpty(LinkQueue Q)//判定队列是否为空
{
    if(Q.front==Q.rear)
    return     1;
    else return 0;
}

void initgraph(pamlgraph G,int n)//？
{
    int i=1;
    for(;i<=n;i++)
        G->adjmulist[i].firstedge=NULL;
}
void SCANF(char name[N][M],int n,pamlgraph G)
{
    int i;
    printf("请输入结点名称：\n");
    for(i=1;i<=n;i++)
    {
        scanf("%s",name[i]);
        G->adjmulist[i].data=name[i];
    }
}
void CreateGraph(int n,pamlgraph G)//构造邻接多重表
{
    pebox p1,p2;
    int i,j,k,m;
    int mark;
    initgraph(G,n);
    printf("请输入边的数量:");
    scanf("%d",&m);
    for(k = 0; k < m; k++)
    {
        printf("请输入第%d条边的两个顶点:",k+1);
        scanf("%d%d",&i,&j);
        p1=(pebox)malloc(sizeof(ebox));
        p1->ivex=i;
        p1->jvex=j;
        p1->ilink=NULL;
        p1->jlink=NULL;
        p2=G->adjmulist[i].firstedge;
        if(p2==NULL)
            G->adjmulist[i].firstedge=p1;
        else
        {
            mark=0;
            while(!mark)
            {
                if(p2->ivex==i && p2->ilink==NULL) mark=1;
                else if(p2->jvex==i && p2->jlink==NULL) mark=2;
                else if(p2->ivex==i) p2=p2->ilink;
                else p2=p2->jlink;
            }
            if(mark==1) p2->ilink=p1;
            else p2->jlink=p1;
        }
        p2=G->adjmulist[j].firstedge;
        if(p2==NULL)
            G->adjmulist[j].firstedge=p1;
        else
        {
            mark=0;
            while(mark==0)
            {
                if(p2->ivex==j && p2->ilink==NULL) mark=1;
                else if(p2->jvex==j && p2->jlink==NULL) mark=2;
                else if(p2->ivex==j) p2=p2->ilink;
                else p2=p2->jlink;
            }
            if(mark==1) p2->ilink=p1;
            else p2->jlink=p1;
        }
    }
}
void visit(pamlgraph G,int v)
{
    printf("\n%s",G->adjmulist[v].data);
    visited[v]=1;
}
void DFS(pamlgraph G,int v)
{
    pebox p;
    int mark;
    if(visited[v]==0) visit(G,v);
    else return;
    p=G->adjmulist[v].firstedge;
    if(p==NULL)
        return;
    else
    {
        mark=0;
        while(mark==0)
        {
            if(p->ivex==v)
            {
                if(visited[p->jvex]==0)
                {
                    printf("\t\t\t<%d,%d>",p->ivex,p->jvex);
                    DFS(G,p->jvex);
                }
                if(p->ilink==NULL) mark=1;
                else p=p->ilink;
            }
            else
            {
                if(visited[p->ivex]==0)
                {
                    printf("\t\t\t<%d,%d>",p->jvex,p->ivex);
                    DFS(G,p->ivex);
                }
                if(p->jlink==NULL) mark=1;
                else p=p->jlink;
            }
        }
    }
}
void BFS(pamlgraph G,int v)
{
    LinkQueue Q;
    pebox p;
    int e;
    int mark;
    Q=InitQueue();
    if(visited[v]==0) visit(G,v);
    else return;
    EnQueue(&Q,v);
    while(QueueEmpty(Q)!=1)
    {
        e=DeQueue(&Q);
        p=G->adjmulist[e].firstedge;
        if(p==NULL) return;
        mark=0;
        while(mark==0)
        {
            if(p->ivex==e)
            {
                if(visited[p->jvex]==0)
                {
                    EnQueue(&Q,p->jvex);
                    printf("\t\t\t<%d,%d>",p->ivex,p->jvex);
                    visit(G,p->jvex);
                }
                if(p->ilink==NULL) mark=1;
                else p=p->ilink;
            }
            else
            {
                if(visited[p->ivex]==0)
                {
                    EnQueue(&Q,p->ivex);
                    printf("\t\t\t<%d,%d>",p->jvex,p->ivex);
                    visit(G,p->ivex);
                }
                if(p->jlink==NULL) mark=1;
                else p=p->jlink;
            }
        }
    }
}
void clear(int v[MAX])
{
    int i;
    for(i=0;i<MAX;i++)
    v[i]=0;
}
int main()
{
    int n,v,i;
    char name[N][M];
    amlgraph G;
    printf("请输入结点的数量:");
    scanf("%d",&n);
    SCANF(name,n,&G);
    CreateGraph(n,&G);
    printf("请输入从哪一个结点开始访问:");
    scanf("%d",&v);
    printf("该图的深度优先遍历和所经过的边为:");
    for(i=0;i<n;i++)
    {
        if(i==0) DFS(&G,v);
        else DFS(&G,i);
    }
    clear(visited);
    printf("\n该图的广度优先遍历和所经过的边为:");
    for(i=0;i<n;i++)
    {
        if(i==0) BFS(&G,v);
        else BFS(&G,i);
    }
    printf("\n两种遍历结束!\n");
    return 0;
}
