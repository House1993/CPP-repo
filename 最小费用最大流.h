#define N 110 //点数
#define M 2010 //边数
#define inf (1<<20)

int n, m, S, T, tot, flow, cost;
int head[N], pre[N], vis[N], dis[N];
struct edge {
	int u, v, w, c, next;
} ed[N * M];
queue<int> qu;

void init() {
	S = 0; //源点汇点
	T = n + 1;
	flow = 0;
	cost = 0;
	tot = 0;
	memset(head, -1, sizeof(head));
}

void add(int U, int V, int W, int C) {
	//+边
	ed[tot].u = U;
	ed[tot].v = V;
	ed[tot].w = W;
	ed[tot].c = C;
	ed[tot].next = head[U];
	head[U] = tot++;
	//-边
	ed[tot].u = V;
	ed[tot].v = U;
	ed[tot].w = 0;
	ed[tot].c = -C;
	ed[tot].next = head[V];
	head[V] = tot++;
}

int spfa() {
	int i, u, v;
	while (!qu.empty())
		qu.pop();
	for (i = 0; i <= T; i++) {
		vis[i] = 0;
		dis[i] = inf;
		pre[i] = -1;
	}
	qu.push(S);
	vis[S] = 1;
	dis[S] = 0;
	while (!qu.empty()) {
		u = qu.front();
		qu.pop();
		vis[u] = 0;
		for (i = head[u]; ~i; i = ed[i].next) {
			if (!ed[i].w)
				continue;
			v = ed[i].v;
			if (dis[v] > dis[u] + ed[i].c) {
				dis[v] = dis[u] + ed[i].c;
				pre[v] = i;
				if (!vis[v]) {
					vis[v] = 1;
					qu.push(v);
				}
			}
		}
	}
	return dis[T] != inf;
}

void mcmf() {
	int i, tmp;
	while (spfa()) {
		tmp = inf;
		for (i = pre[T]; ~i; i = pre[ed[i].u]) {
			if (tmp > ed[i].w)
				tmp = ed[i].w;
		}
		for (i = pre[T]; ~i; i = pre[ed[i].u]) {
			ed[i].w -= tmp;
			ed[i ^ 1].w += tmp;
			cost += tmp * ed[i].c; //这里注意相乘
		}
		flow += tmp;
	}
}