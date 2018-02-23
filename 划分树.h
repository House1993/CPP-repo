//划分树 —— 静态求解区间第k小值
//划分树一旦建树不能更新  因此经常与离线操作相结合
int tree[M][N],toleft[M][N],sum[M][N],sorted[N];
//tree[dep][i] 表示第dep层第i个节点  toleft[dep][i]表示第dep层1~i节点中有几个位于左子树
//sum[dep][i] 表示第dep层第1~i个节点中位于左子树的值的和
//ansnum 可以记录[l,r]区间小于其中第k值的数字的个数  anssum 可以记录它们的和

void build(int l,int r,int dep) //建树 模拟快排过程
{
	if(l==r) return ;
	int i,mid=(l+r)>>1;
	int y=sorted[mid],same=mid-l+1,lpos=l,rpos=mid+1;
	for(i=l;i<=r;i++) //same计算与sorted[mid]相同的数字有几个会被放在左子树（根节点也算左子树）
	{
		if(tree[dep][i]<y) same--;
	}
	for(i=l;i<=r;i++)
	{
		sum[dep][i]=sum[dep][i-1];
		if(tree[dep][i]<y)
		{
			tree[dep+1][lpos++]=tree[dep][i];
			sum[dep][i]+=tree[dep][i];
		}
		else if(tree[dep][i]==y&&same>0)
		{
			tree[dep+1][lpos++]=tree[dep][i];
			same--;
			sum[dep][i]+=tree[dep][i];
		}
		else tree[dep+1][rpos++]=tree[dep][i];
		toleft[dep][i]=toleft[dep][l-1]+lpos-l;
	}
	build(l,mid,dep+1);
	build(mid+1,r,dep+1);
}

int query(int L,int R,int l,int r,int dep,int k) //[L,R]为大区间 [l,r]为查询区间 查询[l,r]内第k小值
{
	if(l==r) return tree[dep][l];
	int mid=(L+R)>>1,amt=toleft[dep][r]-toleft[dep][l-1]; //amt表示[l,r]区间内分在左子树的节点个数
	if(amt>=k)
	{
		int fl=L+toleft[dep][l-1]-toleft[dep][L-1]; // L + [L,l-1]区间分在左子树的节点个数
		int fr=fl+amt-1;
		return query(L,mid,fl,fr,dep+1,k);
	}
	else
	{
		ansnum+=amt;
        anssum+=sum[dep][r]-sum[dep][l-1];
		int fr=r+toleft[dep][R]-toleft[dep][r]; // r + [r+1,R]区间分在左子树的节点个数
		int fl=fr-(r-l-amt);
		return query(mid+1,R,fl,fr,dep+1,k-amt);
	}
}

int findrank(int L,int R,int l,int r,int dep,int x) //查询[l,r]区间内数字x第几小
{
	if(l==r) return 1;
	int mid=(L+R)>>1,amt=toleft[dep][r]-toleft[dep][l-1];
	if(x<=sorted[mid]) //x在左子树
	{
		int fl=L+toleft[dep][l-1]-toleft[dep][L-1];
		int fr=fl+amt-1;
		return findrank(L,mid,fl,fr,dep+1,x);
	}
	else
	{
		int fr=r+toleft[dep][R]-toleft[dep][r];
		int fl=fr-(r-l-amt);
		return amt+findrank(mid+1,R,fl,fr,dep+1,x);
	}
}

int main()
{
	sort(sorted+1,sorted+1+n);
	build(1,n,0);
	query(1,n,u,v,0,k);
	findrank(1,n,u,v,0,x);
}
