//LCA 倍增 在线
//在最小生成树中加一条边  再求最小生成树
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define M 100010
#define N 50010

int n,m,q,tot;
__int64 ans;
struct edgerank
{
    int u,v,w;
    bool operator<(const edgerank fa) const
    {
        return w<fa.w;
    }
}edr[M];
struct edge
{
    int v,w,next;
}ed[M];
int fa[N],head[N],dis[N],dp[N][20],lca[N][20];
//dis深度数组  lca[u][i]表示u的第2^i个祖先  dp[u][i]表示u到第2^i个祖先中的最大边权
void init()
{
    tot=0;
    ans=0;
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
        head[i]=-1;
        dis[i]=0;
    }
    memset(dp,0,sizeof(dp));
    memset(lca,0,sizeof(lca));
}

int getf(int x)
{
    if(x!=fa[x]) fa[x]=getf(fa[x]);
    return fa[x];
}

void add(int u,int v,int w)
{
    ed[tot].v=v; ed[tot].w=w; ed[tot].next=head[u]; head[u]=tot++;
}
//计算dis lca dp值
void dfs(int u,int from,int fromw)
{
    int i,v;
    dis[u]=dis[from]+1;
    lca[u][0]=from;
    dp[u][0]=fromw;
    for(i=1;i<20;i++)
    {
        lca[u][i]=lca[lca[u][i-1]][i-1];
        dp[u][i]=max(dp[u][i-1],dp[lca[u][i-1]][i-1]);
    }
    for(i=head[u];~i;i=ed[i].next)
    {
        v=ed[i].v;
        if(v!=from) dfs(v,u,ed[i].w);
    }
}
//找lca或者dp
int findmx(int u,int v)
{
    if(dis[v]>dis[u]) swap(u,v);
    int i,tmp=dis[u]-dis[v],res=0;
    for(i=19;tmp;i--)
    {
        if(tmp>=(1<<i))
        {
            tmp-=(1<<i);
            res=max(res,dp[u][i]);
            u=lca[u][i];
        }
    }
    if(u==v) return res;
    for(i=19;i>=0;i--)
    {
        if(lca[u][i]!=lca[v][i])
        {
            res=max(res,max(dp[u][i],dp[v][i]));
            u=lca[u][i];
            v=lca[v][i];
        }
    }
    return max(res,max(dp[u][0],dp[v][0]));
}

int main()
{
    int i,fu,fv,tmp;
    while(~scanf("%d%d",&n,&m))
    {
        init();
        for(i=1;i<=m;i++) scanf("%d%d%d",&edr[i].u,&edr[i].v,&edr[i].w);
        sort(edr+1,edr+m+1);
        for(i=1;i<=m;i++)
        {
            fu=getf(edr[i].u);
            fv=getf(edr[i].v);
            if(fu!=fv)
            {
                ans+=edr[i].w;
                fa[fv]=fu;
                add(edr[i].u,edr[i].v,edr[i].w);
                add(edr[i].v,edr[i].u,edr[i].w);
            }
        }
        dfs(1,0,0);
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d%d",&edr[0].u,&edr[0].v,&edr[0].w);
            tmp=findmx(edr[0].u,edr[0].v);
            if(tmp>edr[0].w) printf("%I64d\n",ans-tmp+edr[0].w);
            else printf("%I64d\n",ans);
        }
    }
    return 0;
}
