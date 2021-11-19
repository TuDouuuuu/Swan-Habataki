int dis[MAXN][MAXN];
void bfs(int s) {
    queue<int> q; dis[s][s] = 1; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            if (!dis[s][v]) {
                dis[s][v] = dis[s][u] + 1;
                q.push(v);
            }
        }
    }
}
ll res[MAXN][MAXN];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) head[i] = -1;
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v), addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) bfs(i);
    for (int x = 1; x <= n; x++) {
        for (int y = x; y <= n; y++) {
            int cnt = 0;
            for (int i = 1; i <= n; i++) {
                if (dis[x][i] + dis[y][i] - 1 == dis[x][y]) cnt++; // i int the path of x to y
            }
            ll ans = 1;
            if (cnt > dis[x][y]) ans = 0;
            for (int u = 1; u <= n; u++) {
                if (dis[x][u] + dis[y][u] - 1 != dis[x][y]) {
                    int fg = 0;
                    for (int i = head[u]; ~i; i = e[i].nex) {
                        int v = e[i].to;
                        if (dis[x][v] == dis[x][u] - 1 && dis[y][v] == dis[y][u] - 1) fg++;
                    }
                    ans = ans * fg % mod;
                    if (!ans) break;
                }
            }
            res[x][y] = res[y][x] = ans;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
}