void floyd()
{
    int k,i,j;
    for(k=1;k<=n;k++)
    {
        for(i=1;i<=n;i++) //无向图最小权环
        {
            if(i==k||maz[i][k]==oo) continue;
            for(j=1;j<=n;j++)
            {
                if(j==k||j==i||maz[k][j]==oo||dis[i][j]==oo) continue;
                ans=min(ans,dis[i][j]+maz[i][k]+maz[k][j]);
            }
        }
        for(i=1;i<=n;i++)
        {
            if(i==k||dis[i][k]==oo) continue;
            for(j=1;j<=n;j++)
            {
                if(j==k||j==i||dis[k][j]==oo) continue;
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
}