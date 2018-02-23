#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
#define N 30010
#define inf ((1U<<31)-1)
#define L(x) (ch[x][0])
#define R(x) (ch[x][1])
//priority表示优先级  数字越小优先级越高
int ch[N][2],val[N],priority[N],num[N],size[N];
int tot,root;
//新建节点
int newnode(int &u,int w)
{
    u=++tot;
    L(u)=R(u)=0;
    priority[u]=rand(); //这里可以模一个数  不知道是否有必要
    num[u]=size[u]=1;
    val[u]=w;
    return u;
}
//up操作
inline void up(int u)
{
    size[u]=size[L(u)]+size[R(u)]+num[u];
}
//旋转操作 kind=1 则将u的左儿子旋上去  kind=0 则将u的右儿子旋上去
void rotate(int &u,int kind)
{
    int y=ch[u][kind^1];
    ch[u][kind^1]=ch[y][kind];
    ch[y][kind]=u;
    up(u);
    up(y);
    u=y;
}
//插入一个数w
int insert(int &u,int w)
{
    if(!u) return newnode(u,w);
    int res,kind;
    if(w==val[u])
    {
        num[u]++;
        res=u;
    }
    else
    {
        kind=(w>val[u]);
        res=insert(ch[u][kind],w);
        if(priority[ch[u][kind]]<priority[u]) rotate(u,kind^1);
    }
    up(u);
    return res;
}
//查找第k小的数是几
int select(int u,int k)
{
    if(size[L(u)]>=k) return select(L(u),k);
    if(size[L(u)]+num[u]>=k) return val[u];
    return select(R(u),k-size[L(u)]-num[u]);
}
//删除一个w数字
void remove(int &u,int w)
{
    if(val[u]==w)
    {
        if(num[u]>1) num[u]--;
        else if(!L(u)&&!R(u))
        {
            u=0;
            return ;
        }
        else
        {
            int kind=(priority[L(u)]<priority[R(u)]);
            rotate(u,kind);
            remove(u,w);
        }
    }
    else remove(ch[u][w>val[u]],w);
    up(u);
}

void init()
{
    R(0)=L(0)=size[0]=num[0]=val[0]=0;
    priority[0]=inf;
    tot=root=0;
    newnode(root,inf); //初始化一个优先级无限低的节点
}

int n,m;
int a[N],b[N];

int main()
{
    int i,j;
    while(~scanf("%d%d",&n,&m))
    {
        srand(n*5-m+19930909); //自己搞随机种子
        init();
        for(i=1;i<=n;i++) scanf("%d",&a[i]);
        for(j=1;j<=m;j++) scanf("%d",&b[j]);
        for(j=1,i=1;j<=m;j++)
        {
            while(i<=b[j])
            {
                insert(root,a[i]);
                i++;
            }
            printf("%d\n",select(root,j));
        }
    }
    return 0;
}
