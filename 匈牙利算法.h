//二分图最大匹配  匈牙利算法
//最大匹配数 = 最小点覆盖
//顶点数 - 最大匹配数 = 最小路径覆盖 = 最大独立集

bool dfs(int u)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(!vis[i]&&maz[u][i])
		{
			vis[i]=1;
			if(!match[i]||dfs(match[i]))
			{
				match[i]=u;
				return true;
			}
		}
	}
	return false;
}

int bimatch()
{
	int i,sol=0;
	memset(match,0,sizeof(match));
	for(i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(dfs(i)) sol++;
	}
	return sol;
}
