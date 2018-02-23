//朱刘算法——有向图最小生成树（最小树形图）

//要求去掉自环建图
int ZL(int root, int V, int E)//根、点数、边数
{
    int ret = 0;
    for(;;)
    {
        //1.找最小入边
        for(int i = 0; i < V; i++) in[i] = INF;
        for(int i = 0; i < E; i++)
        {
            int u = edge[i].u;
            int v = edge[i].v;
            if(edge[i].w < in[v] && u != v) {pre[v] = u; in[v] = edge[i].w;}
        }
        for(int i = 0; i < V; i++)
        {
            if(i == root) continue;
            if(in[i] == INF) return -1;//除了根以外有点没有入边,则根无法到达它
        }
        //2.找环
        int cnt = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0;
        for(int i = 0; i < V; i++) //标记每个环
        {
            ret += in[i];
            int v = i;
            while(vis[v] != i && id[v] == -1 && v != root)  //每个点寻找其前序点，要么最终寻找至根部，要么找到一个环
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1)//缩点
            {
                for(int u = pre[v]; u != v; u = pre[u]) id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if(cnt == 0) break; //无环
        for(int i = 0; i < V; i++)
            if(id[i] == -1) id[i] = cnt++;
        //3.建立新图
        for(int i = 0; i < E; i++)
        {
            int u = edge[i].u;
            int v = edge[i].v;
            edge[i].u = id[u];
            edge[i].v = id[v];
            if(id[u] != id[v]) edge[i].w -= in[v];
        }
        V = cnt;
        root = id[root];
    }
    return ret;
}

