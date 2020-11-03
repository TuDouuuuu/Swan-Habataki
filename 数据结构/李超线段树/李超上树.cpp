struct Edge {
    int to, nex, w;
} e[MAXN << 1];
int head[MAXN], tol;
void addEdge(int u, int v, int w) {
    e[tol].to = v, e[tol].w = w, e[tol].nex = head[u], head[u] = tol, tol++;
}

int son[MAXN], dfn[MAXN], _dfn[MAXN], dfn_cnt, fa[MAXN], dep[MAXN], siz[MAXN], top[MAXN];
ll dis[MAXN];
int LCA(int u, int v) {
    while (top[u] != top[v]) {
        dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
    }
    return dep[u] > dep[v] ? v : u;
}
void dfs1(int u, int f, int deep) {
    dep[u] = deep, fa[u] = f, siz[u] = 1;
    int maxson = -1;
    for (int i = head[u]; ~i; i = e[i].nex) {
        int v = e[i].to;
        if (v == f) continue;
        dis[v] = dis[u] + e[i].w;
        dfs1(v, u, deep + 1);
        siz[u] += siz[v];
        if (siz[v] > maxson) son[u] = v, maxson = siz[v];
    }
}
void dfs2(int u, int topf) {
    dfn[u] = ++dfn_cnt, _dfn[dfn_cnt] = u;
    top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (int i = head[u]; ~i; i = e[i].nex) {
        int v = e[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

class LC {  public:
    struct Line {
        int k; ll b;
    } p[MAXN];
    int cnt;

    void init() {
        cnt = 0;
        p[0].k = 0, p[0].b = inf;
    }

    void addLine(int k, ll b) {
        cnt++;
        p[cnt].k = k, p[cnt].b = b;
    }

    inline ll cal(int x, int id) {
        return (ll) p[id].k * dis[_dfn[x]] + p[id].b;
    }

    int s[MAXN<<2]; ll minn[MAXN<<2];

    inline void push_up(int rt) {
        minn[rt] = min(minn[rt], min(minn[rt << 1], minn[rt << 1 | 1]));
    }
    void build(int rt, int l, int r) {
        s[rt] = 0, minn[rt] = inf;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    }

    void update(int rt, int L, int R, int be, int en, int u) {
        int mid = (be + en) >> 1;
        if (L <= be && en <= R) {
            int v = s[rt];
            if (cal(be, u) <= cal(be, v) && cal(en, u) <= cal(en, v)) {
                s[rt] = u, minn[rt] = min(minn[rt], min(cal(be, u), cal(en, u)));
                return;
            }
            if (cal(be, u) >= cal(be, v) && cal(en, u) >= cal(en, v)) return;
            if (p[u].k < p[v].k) {
                if (cal(mid, u) <= cal(mid, v)) {
                    s[rt] = u;
                    update(rt << 1, L, R, be, mid, v);
                } else update(rt << 1 | 1, L, R, mid + 1, en, u);
            } else {
                if (cal(mid, u) <= cal(mid, v)) {
                    s[rt] = u;
                    update(rt << 1 | 1, L, R, mid + 1, en, v);
                } else update(rt << 1, L, R, be, mid, u);
            }
            minn[rt] = min(minn[rt], min(cal(be, u), cal(en, u)));
            push_up(rt);
            return;
        }
        if (L <= mid) update(rt << 1, L, R, be, mid, u);
        if (R > mid) update(rt << 1 | 1, L, R, mid + 1, en, u);
        push_up(rt);
    }

    ll query(int rt, int L, int R, int be, int en) {
        if (L <= be && en <= R) return minn[rt];
        int mid = (be + en) >> 1;
        ll ans = inf;
        if (p[s[rt]].b != inf) ans = min(cal(max(L, be), s[rt]), cal(min(R, en), s[rt]));
        if (L <= mid) ans = min(ans, query(rt << 1, L, R, be, mid));
        if (R > mid) ans = min(ans, query(rt << 1 | 1, L, R, mid + 1, en));
        return ans;
    }
} tree;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) head[i] = -1;  // init graph
    for (int i = 2; i <= n; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w), addEdge(v, u, w);
    }
    dfs1(1, 1, 1);  dfs2(1, 1);
    tree.init();
    tree.build(1, 1, n);
    
    while (m--) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int s, t, a, b; scanf("%d%d%d%d", &s, &t, &a, &b);
            int lca = LCA(s, t);
            auto update = [&](int u, int v, int a, int b) {
                while (top[u] != top[v]) {
                    tree.update(1, dfn[top[u]], dfn[u], 1, n, tree.cnt);
                    u = fa[top[u]];
                }
                tree.update(1, dfn[v], dfn[u], 1, n, tree.cnt);
            };
            tree.addLine(-a, dis[s] * a + b);
            update(s, lca, a, b);
            tree.addLine(a, (dis[s] - (dis[lca] << 1)) * a + b);
            update(t, lca, a, b);
        } else {
            int s, t; scanf("%d%d", &s, &t);
            auto query = [&](int u, int v) {
                ll ans = inf;
                while (top[u] != top[v]) {
                    if (dep[top[u]] < dep[top[v]]) swap(u, v);
                    ans = min(ans, tree.query(1, dfn[top[u]], dfn[u], 1, n));
                    u = fa[top[u]];
                }
                if (dep[u] > dep[v]) swap(u, v);
                ans = min(ans, tree.query(1, dfn[u], dfn[v], 1, n));
                return ans;
            };
            printf("%lld\n", query(s, t));
        }
    }
}