//树状数组套主席树
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 60010 //数组和哈希表大小
#define M 10010 //操作数
#define TS 2500010 //树的节点数
#define L(x) ch[x][0]
#define R(x) ch[x][1]
#define lowbit(x) (x&(-x))

int t,n,m,tot,cnt; //tot是节点数  cnt是hashtable大小
int ch[TS][2],size[TS],T[N],S[N]; //表示树的左右儿子  节点下面数组个数  原树的根  修改操作形成的树的根
int arr[N],hashtable[N]; //数组和哈希表
int op[M],opl[M],opr[M],opn[M],use[N]; //前四个是操作
//use数组类似指针  由于树状数组套主席树要在好多棵树上同时爬  所以用use指向节点
void make_hash()
{
    sort(hashtable+1,hashtable+cnt);
    cnt=unique(hashtable+1,hashtable+cnt)-hashtable;
}
//哈希表从1~cnt-1
int get_hash(int x)
{
    return lower_bound(hashtable+1,hashtable+cnt,x)-hashtable;
}
//根据区间左右端点建树  返回根
int build(int l,int r)
{
    int root=tot++;
    size[root]=0; //表示空树
    if(l!=r)
    {
        int mid=(l+r)>>1;
        L(root)=build(l,mid);
        R(root)=build(mid+1,r);
    }
    return root;
}
//插入操作  表示在old树的基础上 向pos位置插入 变化量为val大小的节点
int insert(int old,int pos,int val)
{
    int root=tot++,tmp=root,l=1,r=cnt-1; //新建节点 记录树根
    size[root]=size[old]+val;
    while(l<r) //非递归的插节点
    {
        int mid=(l+r)>>1;
        if(pos<=mid) //插入的节点位于左子树
        {
            R(root)=R(old); //新节点右子树不变
            old=L(old); //old指针往左走
            L(root)=tot++; //左子树新建节点
            root=L(root); //root同样往左走
            r=mid;
        }
        else
        {
            L(root)=L(old);
            old=R(old);
            R(root)=tot++;
            root=R(root);
            l=mid+1;
        }
        size[root]=size[old]+val;
    }
    return tmp;
}
//更新Stree 利用树状数组可以只更新logn棵树
void add(int id,int pos,int val) //更新主席树的pos位置
{
    for(;id<=n;id+=lowbit(id)) S[id]=insert(S[id],pos,val);
}
//use指针所指向的节点的左子树的size的和
int sum(int x)
{
    int res=0;
    for(;x;x-=lowbit(x)) res+=size[L(use[x])];
    return res;
}
//查询u到v区间第k值
int query(int u,int v,int k)
{
    int i,l=1,r=cnt-1,xl=T[u-1],xr=T[v]; //xl和xr指向原树
    for(i=u-1;i;i-=lowbit(i)) use[i]=S[i]; //用use指向修改树Stree
    for(i=v  ;i;i-=lowbit(i)) use[i]=S[i];
    while(l<r)
    {
        int mid=(l+r)>>1;
        int tmp=-sum(u-1)+sum(v)-size[L(xl)]+size[L(xr)]; //区间里有tmp个数位于左子树
        if(k<=tmp) //进入左子树
        {
            for(i=u-1;i;i-=lowbit(i)) use[i]=L(use[i]); //所有指针往左偏
            for(i=v  ;i;i-=lowbit(i)) use[i]=L(use[i]);
            xl=L(xl);
            xr=L(xr);
            r=mid;
        }
        else
        {
            k-=tmp;
            for(i=u-1;i;i-=lowbit(i)) use[i]=R(use[i]);
            for(i=v  ;i;i-=lowbit(i)) use[i]=R(use[i]);
            xl=R(xl);
            xr=R(xr);
            l=mid+1;
        }
    }
    return l;
}

int main()
{
    int i;
    char str[10];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        cnt=1;
        for(i=1;i<=n;i++)
        {
            scanf("%d",&arr[i]);
            hashtable[cnt++]=arr[i];
        }
        for(i=1;i<=m;i++)
        {
            scanf("%s",str);
            if(str[0]=='Q')
            {
                op[i]=1;
                scanf("%d%d%d",&opl[i],&opr[i],&opn[i]);
            }
            else
            {
                op[i]=2;
                scanf("%d%d",&opl[i],&opn[i]);
                hashtable[cnt++]=opn[i];
            }
        }
        make_hash();
        tot=1;
        T[0]=build(1,cnt-1);  //建空树
        for(i=1;i<=n;i++)
        {
            S[i]=T[0];
            T[i]=insert(T[i-1],get_hash(arr[i]),1); //在T[i-1]基础上建立T[i]
        }
        for(i=1;i<=m;i++)
        {
            if(op[i]==1) printf("%d\n",hashtable[query(opl[i],opr[i],opn[i])]);
			//query时要注意数组中只有一个数字这种情况  对于这种情况只需判断cnt大小然后输出hashtable[1]即可
            else
            {
                add(opl[i],get_hash(arr[opl[i]]),-1);
                add(opl[i],get_hash(opn[i]),1);
                arr[opl[i]]=opn[i];
            }
        }
    }
    return 0;
}
