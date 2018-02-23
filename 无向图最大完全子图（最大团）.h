#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1005

int T,n,m,best;
int num[N],vis[N],g[N][N];

bool dfs(int *adj,int total,int cnt)
{
    int i,j,k;
    int t[N];
    if(!total)
    {
        if(best<cnt)
        {
            best=cnt;
            return true;
        }
        return false;
    }
    for(i=0;i<total;i++)
    {
        if(cnt+(total-i)<=best) return false;
        if(cnt+num[adj[i]]<=best) return false;
        for(k=0,j=i+1;j<total;j++)
            if(g[adj[i]][adj[j]])
                t[k++]=adj[j];
        if(dfs(t,k,cnt+1)) return true;
    }
    return false;
}

void maxClique()
{
    int i,j,k;
    if(n<=1)
    {
        best=n;
        return ;
    }
    int adj[N];
    best=0;
    for(i=n;i>=1;i--)
    {
        for(k=0,j=i+1;j<=n;j++)
        {
            if(g[i][j]) adj[k++]=j;
        }
        dfs(adj,k,1);
        num[i]=best;
    }
}

void dfs(int u,int fa)
{
    for(int i=1;i<=n;i++)
    {
        if(!vis[i]&&g[u][i])
        {
            vis[i]=1;
            g[fa][i]=1;
            dfs(i,fa);
        }
    }
}

void tran()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) vis[j]=0;
        vis[i]=1;
        dfs(i,i);
    }
}

int main()
{
    int i,j;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)
        {
            num[i]=0;
            for(j=1;j<=n;j++) g[i][j]=0;
        }
        while(m--)
        {
            scanf("%d%d",&i,&j);
            g[i][j]=1;
        }
        tran();
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                if(g[i][j]) g[j][i]=1;
            }
        }
        maxClique();
        printf("%d\n",best);
    }
    return 0;
}
