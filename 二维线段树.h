#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define inf 2147483647
#define N 805
#define L(x) (x<<1)
#define R(x) ((x<<1)|1)
#define Mid(x,y) ((x+y)>>1)

struct nodey
{
    int l,r,minval,maxval;
};
struct nodex
{
    int l,r;
    nodey y[N*4];
}x[N*4];
int n,q,lx,ly,ll;

void inity(int l,int r,int i,int j)
{
    x[j].y[i].l=l; x[j].y[i].r=r; x[j].y[i].minval=inf; x[j].y[i].maxval=-inf;
    if(l==r) return ;
    inity(l,Mid(l,r),L(i),j);
    inity(Mid(l,r)+1,r,R(i),j);
}

void initx(int l,int r,int i)
{
    x[i].l=l; x[i].r=r;
    inity(1,n,1,i);
    if(l==r) return ;
    initx(l,Mid(l,r),L(i));
    initx(Mid(l,r)+1,r,R(i));
}

int maxans,minans;
void queryy(int l,int r,int i,int j)
{
    if(x[j].y[i].l==l&&x[j].y[i].r==r)
    {
        maxans=max(maxans,x[j].y[i].maxval);
        minans=min(minans,x[j].y[i].minval);
        return ;
    }
    int mid=Mid(x[j].y[i].l,x[j].y[i].r);
    if(r<=mid) queryy(l,r,L(i),j);
    else if(l>mid) queryy(l,r,R(i),j);
    else
    {
        queryy(l,mid,L(i),j);
        queryy(mid+1,r,R(i),j);
    }
}

void queryx(int l,int r,int i)
{
    if(x[i].l==l&&x[i].r==r)
    {
        queryy(max(1,ly-ll/2),min(n,ly+ll/2),1,i);
        return ;
    }
    int mid=Mid(x[i].l,x[i].r);
    if(r<=mid) queryx(l,r,L(i));
    else if(l>mid) queryx(l,r,R(i));
    else
    {
        queryx(l,mid,L(i));
        queryx(mid+1,r,R(i));
    }
}

void updatey(int l,int i,int j,int key)
{
    if(x[j].y[i].l==x[j].y[i].r)
    {
        if(x[j].l==x[j].r)
        {
            x[j].y[i].minval=key;
            x[j].y[i].maxval=key;
        }
        else
        {
            x[j].y[i].minval=min(x[L(j)].y[i].minval,x[R(j)].y[i].minval);
            x[j].y[i].maxval=max(x[L(j)].y[i].maxval,x[R(j)].y[i].maxval);
        }
        return ;
    }
    int mid=Mid(x[j].y[i].l,x[j].y[i].r);
    if(l<=mid) updatey(l,L(i),j,key);
    else updatey(l,R(i),j,key);
    x[j].y[i].minval=min(x[j].y[L(i)].minval,x[j].y[R(i)].minval);
    x[j].y[i].maxval=max(x[j].y[L(i)].maxval,x[j].y[R(i)].maxval);
}

void updatex(int l,int i,int key)
{
    if(x[i].l==x[i].r)
    {
        updatey(ly,1,i,key);
        return ;
    }
    int mid=Mid(x[i].l,x[i].r);
    if(l<=mid) updatex(l,L(i),key);
    else updatex(l,R(i),key);
    updatey(ly,1,i,key);
}

int main()
{
    int t,i,j,k,tmp;
    scanf("%d",&t);
    for(k=1;k<=t;k++)
    {
        scanf("%d",&n);
        initx(1,n,1);
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                scanf("%d",&tmp);
                ly=j;
                updatex(i,1,tmp);
            }
        }
        scanf("%d",&q);
        printf("Case #%d:\n",k);
        while(q--)
        {
            scanf("%d%d%d",&lx,&ly,&ll);
            minans=inf; maxans=-inf;
            queryx(max(1,lx-ll/2),min(n,lx+ll/2),1);
            tmp=Mid(maxans,minans);
            printf("%d\n",tmp);
            updatex(lx,1,tmp);
        }
    }
    return 0;
}