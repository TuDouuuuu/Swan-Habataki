const int MAXN = 1e5 + 5;
struct Edge {
    int to, nex;
} e[MAXN << 1];
int head[MAXN], tol;
void addEdge(int u, int v) {
    e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
}
int son[MAXN], siz[MAXN];
int col[MAXN], cnt[MAXN], res[MAXN];
int main() {
    int n; scanf("%d", &n);
    tol = 0;
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 2; i <= n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        addEdge(u, v), addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &col[i]);
    function<void(int, int)> dfs1 = [&](int u, int f) {
        siz[u] = 1;
        int maxson = -1;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            if (v == f) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > maxson) son[u] = v, maxson = siz[v];
        }
    };
    dfs1(1, 0);
    int ans = 0, son_son;
    function<void(int, int, int)> dfs3 = [&](int u, int f, int val) {
        cnt[col[u]] += val;
        if (val == 1 && cnt[col[u]] == 1) ans++;
        else if (val == -1 && cnt[col[u]] == 0) ans--;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            if (v == f || v == son_son) continue;
            dfs3(v, u, val);
        }
    };
    function<void(int, int, bool)> dfs2 = [&](int u, int f, bool kp) {
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            if (v == son[u] || v == f) continue;
            dfs2(v, u, 0);
        }
        if (son[u]) dfs2(son[u], u, 1), son_son = son[u];
        dfs3(u, f, 1), son_son = -1;
        res[u] = ans;
        if (!kp) dfs3(u, f, -1);
    };
    dfs2(1, 0, 0);
    int m; scanf("%d", &m);
    while (m--) {
        int x; scanf("%d", &x);
        printf("%d\n", res[x]);
    }
}