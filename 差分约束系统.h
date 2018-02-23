// 差分约束系统

// 建图  加边
for(i=1;i<n;i++) // bellman-ford
{
	for(j=0;j<tot;j++)
	{
		u=ed[j].u;
		v=ed[j].v;
		c=ed[j].c;
		if(dis[v]>dis[u]+c)
		{
			dis[v]=dis[u]+c;
			vis[v]=1; // 这个点曾经被更新过  即约束条件作用到它身上
		}
	}
}

for(j=0;j<tot;j++)
{
	if(dis[ed[j].v]>dis[ed[j].u]+ed[j].c) // 存在负权环
	{
		printf("-1\n");
		return 0;
	}
}

if(vis[ans]) // dis[ans]就是解
else // vis[ans]==0 这个点没有被约束条件作用过
