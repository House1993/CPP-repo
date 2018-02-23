//trie树 + 无向图欧拉回路判断
//poj 2513 参考
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define M 500000

int tot,idx; //tot总结点数  idx映射（本题应用trie树目的是快速映射string到int）
int in[M+5],fa[M+5]; //度
struct node
{
	int next[26]; //trie树指针
	int end;
}nd[M*20+5];
char u[15],v[15];

int getf(int x)
{
	if(fa[x]!=x) fa[x]=getf(fa[x]);
	return fa[x];
}

int main()
{
	int i,len,x,y,now,to;
	tot=1;
	while(~scanf("%s%s",u,v))
	{
		len=strlen(u);
		x=1;
		for(i=0;i<len;i++)
		{
			y=u[i]-'a';
			if(nd[x].next[y]==0) nd[x].next[y]=++tot;
			x=nd[x].next[y];
			if(i==len-1)
			{
				if(nd[x].end==0) nd[x].end=++idx;
				now=nd[x].end;
			}
		}
		in[now]++;
		if(!fa[now]) fa[now]=now;
		//一个点
		len=strlen(v);
		x=1;
		for(i=0;i<len;i++)
		{
			y=v[i]-'a';
			if(nd[x].next[y]==0) nd[x].next[y]=++tot;
			x=nd[x].next[y];
			if(i==len-1)
			{
				if(nd[x].end==0) nd[x].end=++idx;
				to=nd[x].end;
			}
		}
		in[to]++;
		if(!fa[to]) fa[to]=to;
		//另一个点
		x=getf(now);
		y=getf(to);
		if(x!=y) fa[y]=x;
	}
	now=1;
	x=0;
	for(i=1;i<=idx;i++)
	{
		if(i==fa[i]) x++;
	}
	if(x>1) now=0; //判断图连通  用>1判断的原因是本题将一个点都没有定义为图连通
	if(now)
	{
		x=0;
		for(i=1;i<=idx;i++)
		{
			if(in[i]&1) x++;
		}
		if(x!=0&&x!=2) now=0; //连通图基础上存在欧拉回路条件 —— 有0或2个点的度为奇数
		//如果要打印欧拉回路  0个奇数度的点时路径可以从任一点开始  2个奇数度的点时必须路径从一个奇数度点开始到另一个结束
	}
	if(now) printf("Possible\n");
	else printf("Impossible\n");
	return 0;
}
