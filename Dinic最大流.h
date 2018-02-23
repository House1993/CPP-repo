//Dinic算法模版
bool bfs()
{
    int l,r,u,v,i;
    for(i=1;i<=n;i++) dis[i]=-1;
    dis[S]=0;
    qu[0]=S; l=0; r=1;
    while(l<r)
    {
        u=qu[l++];
        for(i=head[u];~i;i=ed[i].next)
        {
            v=ed[i].v;
            if(dis[v]<0&&ed[i].w>0) //未来过的点满足有容量条件
            {
                dis[v]=dis[u]+1;
                if(v==T) return true; //一个有趣的剪枝
                qu[r++]=v;
            }
        }
    }
    return false;
}

int dfs(int u,int nowflow) //多路增广dfs
{
    if(u==T) return nowflow; //到达汇点
    int i,v,tmp,res=0;
    for(i=head[u];~i;i=ed[i].next)
    {
        v=ed[i].v;
        if(dis[v]==dis[u]+1&&ed[i].w>0) //满足分层条件和有容量条件
        {
            tmp=dfs(v,min(nowflow,ed[i].w));
            nowflow-=tmp;
            ed[i].w-=tmp;
            ed[i^1].w+=tmp;
            res+=tmp;
            if(!nowflow) break; //小剪枝
        }
    }
    if(!nowflow) dis[u]=-1; //关键
    return res;
}

int main()
{
	while(bfs()) ans+=dfs(S,oo);
}