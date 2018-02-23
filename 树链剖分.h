/*
树链剖分  1表示点剖  2表示边剖
操作为区间加值  如果要区间改值要用到线段树
查询为每个点（边）的值  如果要求区间最大（小）要用线段树
树链剖分主要是把树剖成线性结构进行处理  可以结合数组“头加尾减”、线段树、树状数组等
*/
#pragma comment(linker,"/STACk:10240000,10240000")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<vector>
#include<set>
#include<map>
#include<queue>
using namespace std;
typedef long long LL;
#define N 100010

inline bool scand(int &ret) {
	char c;
	int sgn;
	if (c = getchar(), c == EOF)
		return 0;
	while (c != '-' && (c < '0' || c > '9'))
		c = getchar();
	sgn = (c == '-') ? -1 : 1;
	ret = (c == '-') ? 0 : (c - '0');
	while (c = getchar(), c >= '0' && c <= '9')
		ret = ret * 10 + (c - '0');
	ret *= sgn;
	return 1;
}

int T, t, n, m;
int head[N], tot; //邻接表
int idx, pre[N], pree[N], size[N], dep[N], hson[N], top[N], tid[N], ftid[N];
//访问序号、树点父亲、树点父边、子树大小、树点深度、树点重儿子、树点链首、树点对应的链点、链点对应的树点
LL add1[N], add2[N], ans1[N], ans2[N];
//更新的数组和答案的数组
struct Edge {
	int id, v, next;
} ed[N * 2];

void init() { //对于变量较多的题一定要注意init
	tot = 0;
	memset(head, -1, sizeof(head));
	idx = 1;
	memset(hson, 0, sizeof(hson));
	memset(add1, 0, sizeof(add1));
	memset(add2, 0, sizeof(add2));
	memset(ans1, 0, sizeof(ans1));
	memset(ans2, 0, sizeof(ans2));
}

void add(int u, int v, int id) {
	ed[tot].id = id;
	ed[tot].v = v;
	ed[tot].next = head[u];
	head[u] = tot++;
}
//两个dfs进行剖分
inline void dfs1(int u, int fa, int edge) {
	dep[u] = dep[fa] + 1;
	pre[u] = fa;
	pree[u] = edge / 2 + 1;
	size[u] = 1;
	for (int i = head[u]; ~i; i = ed[i].next) {
		int v = ed[i].v;
		if (v != fa) {
			dfs1(v, u, i);
			size[u] += size[v];
			if (size[v] > size[hson[u]])
				hson[u] = v;
		}
	}
}

inline void dfs2(int u, int tp) {
	top[u] = tp;
	tid[u] = idx;
	ftid[idx] = u;
	idx++;
	if (hson[u])
		dfs2(hson[u], tp);
	for (int i = head[u]; ~i; i = ed[i].next) {
		int v = ed[i].v;
		if (v != hson[u] && v != pre[u])
			dfs2(v, v);
	}
}
//点剖的更新  这里使用头加尾减  可以很容易改成线段树
void update1(int u, int v, int w) {
	int fu = top[u], fv = top[v];
	while (fu != fv) {
		if (dep[fu] < dep[fv]) {
			swap(fu, fv);
			swap(u, v);
		}
		add1[tid[fu]] += w;
		add1[tid[u] + 1] -= w;
		u = pre[fu];
		fu = top[u];
	}
	if (dep[u] > dep[v])
		swap(u, v);
	add1[tid[u]] += w;
	add1[tid[v] + 1] -= w;
}
//边剖更新
void update2(int u, int v, int w) {
	int fu = top[u], fv = top[v];
	while (fu != fv) {
		if (dep[fu] < dep[fv]) {
			swap(fu, fv);
			swap(u, v);
		}
		add2[tid[fu]] += w;
		add2[tid[u] + 1] -= w;
		u = pre[fu];
		fu = top[u];
	}
	if (u == v)
		return;
	if (dep[u] > dep[v])
		swap(u, v);
	add2[tid[u] + 1] += w;
	add2[tid[v] + 1] -= w;
}

int main() {
	scand(T);
	for (t = 1; t <= T; t++) {
		init();
		scand(n);
		scand(m);
		for (int i = 1; i < n; i++) {
			int u, v;
			scand(u);
			scand(v);
			add(u, v, i);
			add(v, u, i);
		}
		dfs1(1, 0, -2);
		dfs2(1, 1);
		while (m--) {
			int u, v, w;
			char op[20];
			scanf("%s", op);
			scand(u);
			scand(v);
			scand(w);
			if (op[3] == '1')
				update1(u, v, w);
			else
				update2(u, v, w);
		}
		for (int i = 1; i <= n; i++) { //通过扫描add来维护ans
			add1[i] = add1[i - 1] + add1[i];
			add2[i] = add2[i - 1] + add2[i];
			ans1[ftid[i]] = add1[i];
			ans2[pree[ftid[i]]] = add2[i];
		}
		printf("Case #%d:\n", t);
		for (int i = 1; i <= n; i++) {
			printf("%I64d", ans1[i]);
			if (i != n)
				putchar(' ');
			else
				putchar('\n');
		}
		for (int i = 1; i < n; i++) {
			if (i != 1)
				putchar(' ');
			printf("%I64d", ans2[i]);
		}
		putchar('\n');
	}
	return 0;
}
