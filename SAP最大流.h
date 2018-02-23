//SAP最大流算法

const int MAXN=20010;//点数的最大值
const int MAXM=880010;//边数的最大值
const int INF=0x3f3f3f3f;

struct Node
{
    int from,to,next;
    int cap;
}edge[MAXM];
int tol;
int head[MAXN];
int dep[MAXN];//层数
int gap[MAXN];//gap[x]=y : 属于x层的点有y个

int n;//n是总的点的个数，包括源点和汇点

void init()
{
    tol=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int w)
{
    edge[tol].from=u;
    edge[tol].to=v;
    edge[tol].cap=w;
    edge[tol].next=head[u];
    head[u]=tol++;
	//+边
    edge[tol].from=v;
    edge[tol].to=u;
    edge[tol].cap=0;
    edge[tol].next=head[v];
    head[v]=tol++;
	//-边
}
void BFS(int start,int end)//目的求出每个点属于的层数和每层的点数
{
    memset(dep,-1,sizeof(dep));
    memset(gap,0,sizeof(gap));
    gap[0]=1;
    int que[MAXN];
    int front,rear;
    front=rear=0;
    dep[end]=0;
    que[rear++]=end;
    while(front!=rear)
    {
        int u=que[front++];
        if(front==MAXN)front=0;//滚动队列  用stl更方便
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].to;
            if(dep[v]!=-1)continue;
            que[rear++]=v;
            if(rear==MAXN)rear=0;
            dep[v]=dep[u]+1;
            ++gap[dep[v]];
        }
    }
}
int SAP(int start,int end)
{
    int res=0;
    BFS(start,end);
    int cur[MAXN];//优化边遍历 cur[i] ~ head[i] 的边已经没有更新流的可能了
    int S[MAXN];
    int top=0;
    memcpy(cur,head,sizeof(head));
    int u=start;
    int i;
    while(dep[start]<n)//层数必须比总共点数小
    {
        if(u==end)//增广路到达终点  加ans  更新边
        {
            int temp=INF;
            int inser;
            for(i=0;i<top;i++)
               if(temp>edge[S[i]].cap)
               {
                   temp=edge[S[i]].cap;
                   inser=i;
               }
            for(i=0;i<top;i++)
            {
                edge[S[i]].cap-=temp;
                edge[S[i]^1].cap+=temp;
            }
            res+=temp;
            top=inser;//这边将被删除 意味着这条边前的边仍有流量可以继续流
            u=edge[S[top]].from;
        }
        if(u!=end&&gap[dep[u]-1]==0)//出现断层，无增广路
          break;
        for(i=cur[u];i!=-1;i=edge[i].next)
           if(edge[i].cap!=0&&dep[u]==dep[edge[i].to]+1)
             break;
        if(i!=-1)//找到增广路
        {
            cur[u]=i;
            S[top++]=i;
            u=edge[i].to;
        }
        else
        {
            int min=n;
            for(i=head[u];i!=-1;i=edge[i].next)
            {
                if(edge[i].cap==0)continue;
                if(min>dep[edge[i].to])//退回到离终点最近的点
                {
                    min=dep[edge[i].to];
                    cur[u]=i;
                }
            }
            --gap[dep[u]];
            dep[u]=min+1;//由于边被删掉而断开的点要根据bfs原则更新所在层数
            ++gap[dep[u]];
            if(u!=start)u=edge[S[--top]].from;
        }
    }
    return res;
}