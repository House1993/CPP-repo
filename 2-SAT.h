//可行性判定  只适用于对称图
bool can(int m)
{
    int i,j;
    init(); //各种清0
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==j) continue;
			//冲突建边  注意这里别特判什么直接return false之类的  就建边让2-sat跑
			//建边方法  i-j冲突  则建边 i->j^1  j->i^1  i必选则建边  i^1->i
            if(abs(f[i]-f[j])<m)
            {
                add(i,j^1); //边是对称的
                add(j,i^1);
            }
        }
    }
    for(i=0;i<n;i++) //根据图的对称性 强连通缩点
    {
        if(dfn[i]==-1) tarjan(i);
    }
    for(i=0;i<n;i+=2) //如果i和i^1在同一个强连通分量里一定是false
    {
        if(belong[i]==belong[i^1]) return false;
    }
    return true;
}

//判定为可行后  寻找一组可行解
void solve()
{
    int i,u,v,s=tot,l,r;
    for(i=1;i<=cnt;i++) head[i]=-1; //边清0
    tot=0;
    for(i=0;i<s;i++)
    {
        u=belong[ed[i].u];
        v=belong[ed[i].v];
        if(u!=v)
        {
            add(v,u); //重新建边  这里要建反向边（补图）
            in[u]++; //计算入度
        }
    }
	//opt记录 i点所在强连通分量 对应 i^1点所在强连通分量
    for(i=0;i<n;i++) opt[belong[i]]=belong[i^1];
    l=r=0; //bfs寻找拓扑逆序
    for(i=1;i<=cnt;i++)
    {
        if(!in[i]) qu[r++]=i;
    }
    while(l<r)
    {
        u=qu[l++];
        if(!col[u]) //col为1表示取  为2表示不取  为0表示未确定
        {
            col[u]=1;
            col[opt[u]]=2;
        }
        for(i=head[u];~i;i=ed[i].next)
        {
            v=ed[i].v;
            in[v]--;
            if(!in[v]) qu[r++]=v;
        }
    }
}