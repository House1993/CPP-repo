#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
#define keytree ch[ch[root][1]][0]
#define L(x) ch[x][0]
#define R(x) ch[x][1]
#define N 100010

int n,m,tot,root;
int a[N],ch[N][2],pre[N],size[N];
LL val[N],add[N],sum[N];
//新节点申请  如果题中有删除操作则加入栈存放删除节点标号  每次申请先从栈里拿  防止MLE
void newnode(int &u,int fa,int w) 
{
	u=++tot;
	L(u)=R(u)=0;
	pre[u]=fa;
	size[u]=1;
	val[u]=w;
	add[u]=0;
}
//单个节点更新
void updatenode(int u,LL w)
{
	if(!u) return ; //由于up的时候不管有没有子节点都updatenode了  所以此处要判断这里是不是个节点
	val[u]+=w;
	add[u]+=w;
	sum[u]+=w*size[u];
}
//up和down的操作和线段树相似  随题而变  比较灵活
void up(int u)
{
	size[u]=size[L(u)]+size[R(u)]+1;
	sum[u]=sum[L(u)]+sum[R(u)]+val[u];
}

void down(int u)
{
	if(add[u])
	{
		updatenode(L(u),add[u]);
		updatenode(R(u),add[u]);
		add[u]=0;
	}
}
//rotate和splay基本不变
void rotate(int u,int kind) //旋转操作  kind=0左旋  kind=1右旋
{
	int fa=pre[u];
	down(fa); //注意两个down
	down(u);
	ch[fa][!kind]=ch[u][kind];
	pre[ch[u][kind]]=fa;
	if(pre[fa]) ch[pre[fa]][ch[pre[fa]][1]==fa]=u;
	pre[u]=pre[fa];
	ch[u][kind]=fa;
	pre[fa]=u;
	up(fa); //转完了要up
}

void splay(int u,int goal) //将u移动到goal下面
{
	int fa,kind;
	down(u); //注意down  循环时候不用down和up  这两个操作在rotate里面有
	while(pre[u]!=goal)
	{
		//如果有rev操作  下面的if里都要先down pre再down u  else里要先down prefa再down fa再down u
		if(pre[pre[u]]==goal) rotate(u,L(pre[u])==u);
		else
		{
			fa=pre[u];
			kind=L(pre[fa])==fa;
			if(ch[fa][kind]==u)
			{
				rotate(u,!kind);
				rotate(u,kind);
			}
			else
			{
				rotate(fa,kind);
				rotate(u,kind);
			}
		}
	}
	up(u); //注意up
	if(goal==0) root=u; //将节点转到根  则根就变了
}

int getkth(int u,int k) //找第k个元素（与元素大小无关）
{
	down(u); //注意down
	int s=size[L(u)]+1;
	if(s==k) return u;
	if(s>k) return getkth(L(u),k);
	else return getkth(R(u),k-s);
}

void build(int &u,int l,int r,int fa) //建树过程
{
	if(l>r) return ;
	int mid=(l+r)>>1;
	newnode(u,fa,a[mid]);
	build(L(u),l,mid-1,u);
	build(R(u),mid+1,r,u);
	up(u); //注意up
}

void init() //初始化清零操作并建树
{
	root=tot=0;
	L(root)=R(root)=pre[root]=size[root]=val[root]=add[root]=sum[root]=0;
	newnode(root,0,-1); //在头和尾建立哨兵节点  注意如果求max和min的时候要特判这两个点
	newnode(R(root),root,-1);
	build(keytree,1,n,R(root));
	up(R(root)); //建完节点要up
	up(root);
}
//区间[l,r]更新w  由于加入哨兵节点  [l,r]对应[l+1,r+1]节点  这时将l转到根r+2转到R(root)  则所求区间在keytree
void update(int l,int r,int w)
{
	splay(getkth(root,l),0);
	splay(getkth(root,r+2),root);
	updatenode(keytree,w);
	up(R(root));
	up(root);
}
//区间[l,r]查询  同理update
LL query(int l,int r)
{
	splay(getkth(root,l),0);
	splay(getkth(root,r+2),root);
	return sum[keytree];
}
//找前驱  要先把u转成根  只有根的前驱是一定能在子树里找到的
int getpre(int u)
{
    down(u);
    u=L(u);
    down(u);
    while(R(u))
    {
        u=R(u);
        down(u);
    }
    return u;
}
//删除根
void remove()
{
    if(L(root))
    {
        int i=getpre(root);
        splay(i,root);
        R(i)=R(root);
        pre[R(root)]=i;
        root=L(root);
        pre[root]=0;
        up(root);
    }
    else
    {
        root=R(root);
        pre[root]=0;
    }
}
//插入节点
void insert(int u)
{
    keytree=u;
    pre[u]=R(root);
    L(u)=R(u)=0;
    up(u);
    up(pre[u]);
    up(root);
}

int main()
{
	int u,v,x;
	char op[3];
	while(~scanf("%d%d",&n,&m))
	{
		for(u=1;u<=n;u++) scanf("%d",&a[u]);
		init();
		while(m--)
		{
			scanf("%s",op);
			if(op[0]=='Q')
			{
				scanf("%d%d",&u,&v);
				printf("%lld\n",query(u,v));
			}
			else
			{
				scanf("%d%d%d",&u,&v,&x);
				update(u,v,x);
			}
		}
	}
	return 0;
}
