class HJT { public:
    int query(int lrt, int rrt, int fa, int faa, int k, int be, int en) {
        if (be >= en) return be;
        int mid = (be + en) >> 1;
        int delta = sum[ch[lrt][0]] + sum[ch[rrt][0]] - sum[ch[fa][0]] - sum[ch[faa][0]];
        if (delta >= k) return query(ch[lrt][0], ch[rrt][0], ch[fa][0], ch[faa][0], k, be, mid);
        else return query(ch[lrt][1], ch[rrt][1], ch[fa][1], ch[faa][1], k - delta, mid + 1, en);
    }
} tree;

struct Edge {
    int to, nex;
} e[MAXN << 1];
int head[MAXN], tol;
void addEdge(int u, int v) {
    e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
}
int val[MAXN], root[MAXN], new_val[MAXN];
int dep[MAXN], fa[MAXN][32], lg[MAXN];
void init(int _n) {
    for (int i = 1; i <= _n; i++) lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
}
void dfs(int u, int f) {
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    root[u] = tree.update(root[f], new_val[u], 1, 1, Discrete::blen);
    for (int i = 1; i <= lg[dep[u]]; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; ~i; i = e[i].nex) {
        int v = e[i].to;
        if (v == f) continue;
        dfs(v, u);
    }
}
int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) u = fa[u][lg[dep[u] - dep[v]] - 1];
    if (u == v) return u;
    for (int k = lg[dep[u]] - 1; k >= 0; k--) {
        if (fa[u][k] != fa[v][k]) u = fa[u][k], v = fa[v][k];
    }
    return fa[u][0];
}
int main() {
    int n, m; scanf("%d%d", &n, &m);
    init(n);
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);

    for (int i = 1; i <= n; i++) Discrete::insert(val[i]);
    Discrete::init();
    for (int i = 1; i <= n; i++) new_val[i] = Discrete::val2id(val[i]);
    for (int i = 2; i <= n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        addEdge(u, v), addEdge(v, u);
    }
    root[0] = 0;
    dfs(1, 0);
    while (m--) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        int lca = LCA(u, v);
        printf("%d\n", 
               Discrete::id2val(tree.query(root[u], root[v], root[lca], root[fa[lca][0]], k, 1, Discrete::blen)));
    }
}
