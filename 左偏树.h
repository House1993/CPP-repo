//左偏树 -- 可合并的堆
// hdu 1512
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100010

int n,m,tot;
int fa[N];
struct node
{
    int v,l,r,dis;
}nd[N];

int getf(int x)
{
    if(x!=fa[x]) fa[x]=getf(fa[x]);
    return fa[x];
}

int newnode(int x) //新建节点  注意0节点不用 返回节点id
{
    nd[tot].v=x;
    nd[tot].l=0;
    nd[tot].r=0;
    nd[tot].dis=0;
    tot++;
    return tot-1;
}

int merge(int x,int y) //左偏树递归合并 返回新根
{
    if(!x) return y;
    if(!y) return x;
    if(nd[x].v<nd[y].v) swap(x,y);
    nd[x].r=merge(nd[x].r,y);
    if(nd[nd[x].l].dis<nd[nd[x].r].dis) swap(nd[x].l,nd[x].r);
    nd[x].dis=nd[nd[x].r].dis+1;
    return x;
}

int pop(int x) //pop左偏树的根 返回新根
{
    int tmp=merge(nd[x].l,nd[x].r);
    nd[x].dis=nd[x].l=nd[x].r=0;
    return tmp;
}

int main()
{
    int i,j,fi,fj,x;
    while(~scanf("%d",&n))
    {
        tot=1; //从1开始
        for(i=1;i<=n;i++)
        {
            scanf("%d",&j);
            fa[i]=newnode(j);
        }
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d%d",&i,&j);
            fi=getf(i);
            fj=getf(j);
            if(fi==fj) puts("-1");
            else
            {
                i=pop(fi);
                nd[fi].v/=2;
                j=pop(fj);
                nd[fj].v/=2;
                i=merge(i,j);
                i=merge(i,fi);
                i=merge(i,fj);
                fa[i]=fa[fi]=fa[fj]=i; //这里注意  由于i的fa是fi  所以要改变三个fa  使他们指向新的左偏树的根
                printf("%d\n",nd[i].v);
            }
        }
    }
    return 0;
}
