//动态维护一组森林，支持以下操作:
//link(a,b) : 如果a,b不在同一棵子树中，则通过在a,b之间连边的方式，连接这两棵子树
//cut(a,b)  : 如果a,b在同一棵子树中，且a!=b，则将a视为这棵子树的根以后，切断b与其父亲结点的连接
//ADD(a,b,w): 如果a,b在同一棵子树中，则将a,b之间路径上所有点的点权增加w
//query(a,b): 如果a,b在同一棵子树中，返回a,b之间路径上点权的最大值

#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
#define N  300010
#define L(x) (ch[x][0])
#define R(x) (ch[x][1])

struct Edge {
	int v, next;
} ed[N * 2];
int head[N], tot;
int ch[N][2], pre[N], key[N], add[N], rev[N], Max[N];
bool rt[N];

void Update_Add(int u, int d) {
	if (!u)
		return;
	key[u] += d;
	add[u] += d;
	Max[u] += d;
}

void Update_Rev(int u) {
	if (!u)
		return;
	swap(L(u), R(u));
	rev[u] ^= 1;
}

void down(int u) {
	if (add[u]) {
		Update_Add(L(u), add[u]);
		Update_Add(R(u), add[u]);
		add[u] = 0;
	}
	if (rev[u]) {
		Update_Rev(L(u));
		Update_Rev(R(u));
		rev[u] = 0;
	}
}

void up(int u) {
	Max[u] = max(max(Max[L(u)], Max[R(u)]), key[u]);
}

//Rotate P Splay 一般不变
void Rotate(int x) {
	int y = pre[x], kind = ch[y][1] == x;
	ch[y][kind] = ch[x][!kind];
	pre[ch[y][kind]] = y;
	pre[x] = pre[y];
	pre[y] = x;
	ch[x][!kind] = y;
	if (rt[y])
		rt[y] = false, rt[x] = true;
	else
		ch[pre[x]][ch[pre[x]][1] == y] = x;
	up(y);
}

//P函数先将splay根结点到u的路径上所有的结点的标记逐级下放
void P(int u) {
	if (!rt[u])
		P(pre[u]);
	down(u);
}

void Splay(int u) {
	P(u);
	while (!rt[u]) {
		int fa = pre[u], ffa = pre[fa];
		if (rt[fa])
			Rotate(u);
		else if ((R(ffa) == fa) == (R(fa) == u))
			Rotate(fa), Rotate(u);
		else
			Rotate(u), Rotate(u);
	}
	up(u);
}

//将root到u的路径变成实边
int Access(int u) {
	int v = 0;
	for (; u; u = pre[v = u]) {
		Splay(u);
		rt[R(u)] = true, rt[R(u) = v] = false;
		up(u);
	}
	return v;
}

//判断是否是同树(真实的树，非splay)
bool judge(int u, int v) {
	while (pre[u])
		u = pre[u];
	while (pre[v])
		v = pre[v];
	return u == v;
}

//使u成为它所在的树的根
void mroot(int u) {
	Access(u);
	Splay(u);
	Update_Rev(u);
}

//调用后u是原来u和v的lca,v和ch[u][1]分别存着lca的2个儿子(原来u和v所在的2颗子树)
void lca(int &u, int &v) {
	Access(v), v = 0;
	while (u) {
		Splay(u);
		if (!pre[u])
			return;
		rt[R(u)] = true;
		rt[R(u) = v] = false;
		up(u);
		u = pre[v = u];
	}
}

//连接两棵树  u接在v上
void link(int u, int v) {
	if (judge(u, v)) {
		puts("-1");
		return;
	}
	mroot(u);
	pre[u] = v;
}

//使u成为u所在树的根，并且v和它父亲的边断开
void cut(int u, int v) {
	if (u == v || !judge(u, v)) {
		puts("-1");
		return;
	}
	mroot(u);
	Splay(v);
	pre[L(v)] = pre[v];
	pre[v] = 0;
	rt[L(v)] = true;
	L(v) = 0;
	up(v);
}

//u-v路径+w
//其实路径操作先mroot(u)再access(v)就可以方便的将路径变成splay  不用lca
/*
void ADD(int u, int v, int w) {
    mroot(u);
    Access(v);
    Splay(v);
    Update_Add(v, w);
}
*/
void ADD(int u, int v, int w) {
	if (!judge(u, v)) {
		puts("-1");
		return;
	}
	lca(u, v);
	Update_Add(R(u), w);
	Update_Add(v, w);
	key[u] += w;
	up(u);
}

//u-v路径最大值 路径的询问同上不一定要lca
void query(int u, int v) {
	if (!judge(u, v)) {
		puts("-1");
		return;
	}
	lca(u, v);
	printf("%d\n", max(max(Max[v], Max[R(u)]), key[u]));
}

void addedge(int u, int v) {
	ed[tot].v = v;
	ed[tot].next = head[u];
	head[u] = tot++;
}

//利用dfs初始化pre数组  建立LCT
void dfs(int u) {
	for (int i = head[u]; ~i; i = ed[i].next) {
		int v = ed[i].v;
		if (pre[v] != 0)
			continue;
		pre[v] = u;
		dfs(v);
	}
}

int main() {
	int n, q, u, v;
	while (scanf("%d", &n) == 1) {
		tot = 0;
		memset(head, -1, sizeof(head));
		memset(pre, 0, sizeof(pre));
		memset(ch, 0, sizeof(ch));
		memset(rev, 0, sizeof(rev));
		memset(add, 0, sizeof(add));
		for (int i = 0; i <= n; i++)
			rt[i] = true;
		Max[0] = -2000000000;
		for (int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			addedge(u, v);
			addedge(v, u);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &key[i]);
			Max[i] = key[i];
		}
		scanf("%d", &q);
		pre[1] = -1;
		dfs(1);
		pre[1] = 0;
		int op;
		while (q--) {
			scanf("%d", &op);
			if (op == 1) {
				int x, y;
				scanf("%d%d", &x, &y);
				link(x, y);
			} else if (op == 2) {
				int x, y;
				scanf("%d%d", &x, &y);
				cut(x, y);
			} else if (op == 3) {
				int w, x, y;
				scanf("%d%d%d", &w, &x, &y);
				ADD(x, y, w);
			} else {
				int x, y;
				scanf("%d%d", &x, &y);
				query(x, y);
			}
		}
		printf("\n");
	}
	return 0;
}
