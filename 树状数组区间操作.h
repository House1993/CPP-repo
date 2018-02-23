/*
总结树状数组：
1、单点更新  区间求和（单点求值）
最简单最基础的操作  数组中存的东西就是要求和的数字
2、区间更新  单点求值
维护差分序列  例如要求a[i]  数组中存的东西应该是d[i] （d[i] = a[i] - a[i-1]）
那么 a[i] = d[1] + d[2] + d[3] + … + d[i]
如果要区间[l,r]每个元素都+v  那么只需让d[l] + v  再让d[r+1] - v
3、区间更新  区间求和
求 a[1] + a[2] + a[3] + … + a[x]  沿用d[i]思想
sum = sigma(a[i]) = sigma( sigma(d[i]) ) = sigma( d[i]*(x-i+1) ) = sigma( d[i]*(x+1) ) - sigma( d[i]*i )
因此需要维护d（即d[i]）和di（即d[i]*i）两个树状数组
求值时  ans(l,r) = sum(d,r)*(r+1) - sum(d,l-1)*l - ( sum(di,r) - sum(di,l-1) )
更新[l,r]时分开维护d树状数组和di树状数组
add(d,l,v); add(d,r+1,-v);  因为 d[l] = a[l](新的) - a[l-1] = a[l](原来的) + v - a[l-1] = d[l](原来的) + v 同理r+1处 - v
add(di,l,v*l); add(di,r+1,-v*(r+1)); 在d[i]的变化基础上乘i  一样是l处加  r+1处减
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define M 100010

__int64 a[M],d[M],di[M];
int n,m;

int lowbit(int x)
{
    return x&(-x);
}

void add(__int64 a[],int x,__int64 v)
{
    while(x<=n)
    {
        a[x]+=v;
        x+=lowbit(x);
    }
}

__int64 sum(__int64 a[],int x)
{
    __int64 res=0;
    while(x)
    {
        res+=a[x];
        x-=lowbit(x);
    }
    return res;
}

int main()
{
    int f,t;
    char op[5];
    __int64 val;
    scanf("%d%d",&n,&m);
    for(f=1;f<=n;f++)
    {
        scanf("%I64d",&a[f]);
        a[f]+=a[f-1];
    }
    while(m--)
    {
        scanf("%s",op);
        if(op[0]=='Q')
        {
            scanf("%d%d",&f,&t);
            printf("%I64d\n",a[t]-a[f-1]+sum(d,t)*(t+1)-sum(d,f-1)*f-sum(di,t)+sum(di,f-1));
        }
        else if(op[0]=='C')
        {
            scanf("%d%d%I64d",&f,&t,&val);
            add(d,f,val);
            add(d,t+1,-val);
            add(di,f,val*f);
            add(di,t+1,val*(-t-1));
        }
    }
	return 0;
}
