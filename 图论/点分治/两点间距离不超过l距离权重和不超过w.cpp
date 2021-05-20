/*  4 4 6
    1 3
    1 4
    1 3
    res = 4
    6 2 17
    1 3
    2 5
    2 13
    1 6
    5 9
    res = 9     */
class BIT { public:
    int val[MAXN], n;
    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) val[i] = 0;
    }
    inline int lowbit(int x) { return x & (-x); }

    void add(int pos, int v) {
        for (int i = pos; i <= n; i += lowbit(i)) val[i] += v;
    }
    int query(int pos) {
        int ans = 0;
        for (int i = pos; i >= 1; i -= lowbit(i)) ans += val[i];
        return ans;
    }
} tree;
struct Edge {
    int to, nex;
    ll w;
} e[MAXN << 1];
int head[MAXN], tol;
void addEdge(int u, int v, ll w) {
    e[tol].to = v, e[tol].w = w, e[tol].nex = head[u], head[u] = tol, tol++;
}
int son[MAXN], f[MAXN], vis[MAXN];
int dis[MAXN];
ll wis[MAXN];

int main() {
    int n, l; ll w; scanf("%d%d%lld", &n, &l, &w);
    tol = 0;
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 2; i <= n; i++) {
        int v; ll w; scanf("%d%lld", &v, &w);
        addEdge(i, v, w), addEdge(v, i, w);
    }
    int root = 0, sum = n;
    f[0] = n;
    function<void(int, int)> get_root = [&](int u, int fa) {
        son[u] = 1, f[u] = 0;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            if (vis[v] || v == fa) continue;
            get_root(v, u);
            son[u] += son[v], f[u] = max(f[u], son[v]);
        }
        f[u] = max(f[u], sum - son[u]);
        if (f[u] < f[root]) root = u;
    };
    get_root(1, 0);

    vector<int> vec;
    function<void(int, int)> get_dis = [&](int u, int fa) {
        vec.pb(u);
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            ll w = e[i].w;
            if (v == fa || vis[v]) continue;
            dis[v] = dis[u] + 1, wis[v] = wis[u] + w;
            get_dis(v, u);
        }
    };
    auto cal = [&](int u, int x1, ll x2) {
        vec.clear();
        dis[u] = x1, wis[u] = x2, get_dis(u, 0);
        sort(vec.begin(), vec.end(), [&](int ta, int tb) {
            return wis[ta] < wis[tb];
        });
        tree.init(n+1);
        for (int i = 0; i < SZ(vec); i++) tree.add(dis[vec[i]] + 1, 1);
        ll ans = 0;
        int L = 0, R = SZ(vec) - 1;
        while (L < R) {
            if (wis[vec[L]] + wis[vec[R]] <= w) {
                tree.add(dis[vec[L]] + 1, -1);
                ans += tree.query(l - dis[vec[L]] + 1);
                L++;
            } else {
                tree.add(dis[vec[R]] + 1, -1);
                R--;
            }
        }
        tree.add(dis[vec[L]] + 1, -1);
        return ans;
    };

    ll res = 0;
    function<void(int)> solve = [&](int u) {
        res += cal(u, 0, 0);
        vis[u] = 1;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            ll w = e[i].w;
            if (vis[v]) continue;
            res -= cal(v, 1, w);
            root = 0, sum = son[v];
            get_root(v, 0);
            solve(root);
        }
    };
    solve(root);
    printf("%lld\n", res);
}