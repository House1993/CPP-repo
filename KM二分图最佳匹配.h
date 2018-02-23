//HDU 2255 
#include <cstdio>
#include <cstring>
#include <algorithm>
#define oo 99999999
#define M 310
using namespace std;

int n,ans;
int link[M],visx[M],visy[M],val[M][M],slack[M],x[M],y[M];
//匹配记录、x访问、y访问、出价矩阵、松弛记录、x标号、y标号 

int dfs(int now)
{
	int i,tmp;
	visx[now]=1;
	for(i=1;i<=n;i++)
	{
		if(visy[i]) continue;
		tmp=x[now]+y[i]-val[now][i];
		if(tmp==0)
		{
			visy[i]=1;
			if(link[i]==-1||dfs(link[i]))
			{
				link[i]=now;
				return 1;
			}
		}
		else if(slack[i]>tmp) slack[i]=tmp;
	}
	return 0;
}

void KM()
{
	int i,j,tmp;
	memset(link,-1,sizeof(link));
	memset(y,0,sizeof(y));
	for(i=1;i<=n;i++)
	{
		x[i]=-oo;
		for(j=1;j<=n;j++)
		{
			if(x[i]<val[i][j]) x[i]=val[i][j];
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++) slack[j]=oo;
		for(;;)
		{
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(dfs(i)) break;
			tmp=oo;
			for(j=1;j<=n;j++)
			{
				if(!visy[j]&&tmp>slack[j]) tmp=slack[j];
			}
			for(j=1;j<=n;j++)
			{
				if(visx[j]) x[j]-=tmp;
			}
			for(j=1;j<=n;j++)
			{
				if(visy[j]) y[j]+=tmp;
				else slack[j]-=tmp;
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		if(link[i]!=-1) ans+=val[link[i]][i];
	}
}

int main()
{
	int i,j;
	while(scanf("%d",&n)!=EOF)
	{
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++) scanf("%d",&val[i][j]);
		}
		ans=0;
		KM();
		printf("%d\n",ans);
	}
	return 0;
}
