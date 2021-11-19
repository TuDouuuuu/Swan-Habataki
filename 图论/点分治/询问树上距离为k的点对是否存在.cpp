const int MAXN = 1e4 + 5;
const int MAXM = 105;
struct Edge {
    int to, w, nex;
} e[MAXN << 1];
int head[MAXN], tol;
void addEdge(int u, int v, int w) {
    e[tol].to = v, e[tol].w = w, e[tol].nex = head[u], head[u] = tol, tol++;
}
int son[MAXN], f[MAXN], vis[MAXN];
int dis[MAXN], top[MAXN];
int qs[MAXM], res[MAXM];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    tol = 0;
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 2; i <= n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w), addEdge(v, u, w);
    }
    for (int i = 1; i <= m; i++) scanf("%d", &qs[i]);

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
    function<void(int, int, int)> get_dis = [&](int u, int fa, int topf) {
        vec.pb(u), top[u] = topf;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w;
            if (vis[v] || v == fa) continue;
            dis[v] = dis[u] + w;
            get_dis(v, u, topf);
        }
    };
    auto cal = [&](int u) {
        vec.clear(), vec.pb(u);
        dis[u] = 0, top[u] = u;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w;
            if (vis[v]) continue;
            dis[v] = w;
            get_dis(v, u, v);
        }
        sort(vec.begin(), vec.end(), [&](int ta, int tb) {
            return dis[ta] < dis[tb];
        });
        for (int i = 1; i <= m; i++) {
            int L = 0, R = SZ(vec) - 1;
            if (res[i] || qs[i] == 0) {
                res[i] = 1;
            } else {
                while (L < R) {
                    if (dis[vec[L]] + dis[vec[R]] > qs[i]) R--;
                    else if (dis[vec[L]] + dis[vec[R]] < qs[i]) L++;
                    else if (top[vec[L]] == top[vec[R]]) {
                        if (dis[vec[R]] == dis[vec[R - 1]]) R--;
                        else L++;
                    } else {
                        res[i] = 1;
                        break;
                    }
                }
            }
        }
    };

    function<void(int)> solve = [&](int u) {
        vis[u] = 1;
        cal(u);
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w;
            if (vis[v]) continue;
            root = 0, sum = son[v];
            get_root(v, 0);
            solve(root);
        }
    };
    solve(root);
    for (int i = 1; i <= m; i++) {
        printf("%s\n", res[i] ? "AYE" : "NAY");
    }
}
