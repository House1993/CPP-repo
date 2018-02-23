//树的重心模版

//sz[i]为i节点按照dfs顺序的子树总结点数（包括i节点自己）
//dp[i]为i节点所连接的所有子树中节点个数最多的节点数

void dfs(int u,int fa)
{
	int i,v;
    sz[u]=1;//初始子节点个数为1（自己）
    for (i=head[u];~i;i=ed[i].next)
    {
        v=ed[i].v;
        if (v!=fa)
        {
            dfs(v,u);
            sz[u]+=sz[v];//加上子树的节点数
            dp[u]=max(sz[v],dp[u]);
        }
    }
    dp[u]=max(dp[u],n-sz[u]);//检查i的fa方向的子树的节点数
}
