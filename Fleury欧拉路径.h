//Fleury欧拉路径

void dfs(int x)
{
    int i;
    for(i=1;i<=n;i++)
	{
        if(Edge[i][x])
		{
            Edge[i][x]=Edge[x][i]=0;//删边
			s.node[++s.top]=i;//入栈
            dfs(i);
            break;
        }
    }
}

void Fleury(int x)
{
    int i,b;
    s.top=0;
	s.node[0]=x;//初始化起点
    while(s.top>=0)
	{
        b=0;
        for(i=1;i<=n;i++)
		{
            if(Edge[s.node[s.top]][i])//有边可走
			{
                b=1;
				break;
            }
        }
        if(b==0) printf("%d ",s.node[s.top--]);//输出路径
        else dfs(s.node[s.top]);
    }
}
