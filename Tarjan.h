//无向图求桥
//有自环时不加自环的边
//边双连通缩点方法：去掉桥，遍历图，每一块缩成一个点

void solve()
{
	int i;
	memset(dfn,-1,sizeof(dfn));
	idx=0;
	for(i=1;i<=n;i++)
	{
		if(dfn[i]==-1) tarjan(i);//图可能本身不连通
	}
}

void tarjan(int u)
{
    int i,v,num=0;
    dfn[u]=low[u]=++idx;
    for(i=head[u];~i;i=ed[i].next)
    {
        v=ed[i].v;
        if(ed[i].flag) continue;
		ed[i].flag=ed[i^1].flag=1;
        if(dfn[v]==-1)
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
            {
                //i为桥
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
}

//无向图求割点
//一个顶点u是割点，当且仅当满足 (1) 或 (2) 
//(1) u为树根，且u有多于一个子树。
//(2) u不为树根，且满足存在(u,v)为树枝边(或称父子边，即u为v在搜索树中的父亲)，使得DFS(u)<=Low(v)
//点双连通缩点方法：
//求割点时候用栈记录遍历的边，每次找到一个割点时让一些边出栈，出栈的边所关联的点缩成一个点，此时割点和其他点会缩在一起

void tarjan(int u,int fa)//u为所在点，fa为父亲点  刚开始调用函数时要用tarjan(i,i)
{
	int i,j,v,son=0;
	dfn[u]=low[u]=++idx;
	for(i=head[u];~i;i=ed[i].next)
	{
		v=ed[i].v;
		if(ed[i].flag||dfn[v]>=dfn[u]) continue;
		ed[i].flag=ed[i^1].flag=1;
		st[++top]=i;//缩点时用以存边的栈
		if(dfn[v]==-1)
		{
			son++;
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<=low[v])
            {
				if(u!=fa) //u为割点
                n++; //建立新点
                do //缩点
                {
                    j=st[top--];
                    if(Tmp[ed[j].v]!=n) //Tmp[x]=y 表示原图中点x属于新图中双连通分量y
                    {
                        E[m++]=make_pair(n,ed[j].v); //暂时存储新图的边  tarjan结束后建边时要变成双向
                        Tmp[ed[j].v]=n;
                    }
                    if(Tmp[ed[j^1].v]!=n)
                    {
                        E[m++]=make_pair(n,ed[j^1].v);
                        Tmp[ed[j^1].v]=n;
                    }
                    belong[j>>1]=n; //belong[i]=y 表示第i条双向边属于双连通分量y
                }while(j!=i);
            }
		}
		else low[u]=min(low[u],dfn[v]);
	}
	if(u==fa&&son>1) //u为割点
}

//有向图强连通分量

void solve()
{
    int i;
    top=cnt=idx=0;
    memset(dfn,-1,sizeof(dfn));
	memset(instack,0,sizeof(instack));
	memset(belong,0,sizeof(belong));
    for(i=1;i<=n;i++)
        if(dfn[i]==-1) tarjan(i);
}

void tarjan(int u)
{
    int i,v;
    dfn[u]=low[u]=++idx;
    instack[u]=1;
    st[++top]=u;
    for(i=head[u];~i;i=ed[i].next)
    {
        v=ed[i].v;
        if(dfn[v]==-1)
        {
            tarjan(v);
			low[u]=min(low[u],low[v]);
        }
        else if(instack[v]&&dfn[v]<low[u]) low[u]=dfn[v];
    }
    if(dfn[u]==low[u])
    {
        cnt++;
        do
        {
            v=st[top--];
            instack[v]=0;
            belong[v]=cnt;
        }while(u!=v);
    }
}

//离线LCA

int getf(int x)
{
	if(x!=fa[x]) fa[x]=getf(fa[x]);
	return fa[x];
}

void tarjan(int u)
{
	int i,v;
	fa[u]=u;
	for(i=head[u];~i;i=ed[i].next)
	{
		v=ed[i].v;
		if(!color[v])
		{
			tarjan(v);
			fa[v]=u;
		}
	}
	color[u]=1;
	for(i=1;i<=m;i++)
	{
		if(u==ask[i].from&&color[ask[i].to]) ask[i].ans=getf(ask[i].to);
		if(u==ask[i].to&&color[ask[i].from]) ask[i].ans=getf(ask[i].from);
	}
}