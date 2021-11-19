/*  5
    1 2 1
    1 3 2
    1 4 1
    2 5 3
    res = 13/25
    (1,1)，(2,2)，(2,3)，(2,5)，(3,2)，(3,3)，(3,4)，(3,5)，(4,3)，(4,4)，(5,2)，(5,3)，(5,5)*/
struct Edge {
    int to, nex, w;
} e[MAXN << 1];
int head[MAXN], tol;
void addEdge(int u, int v, int w) {
    e[tol].to = v, e[tol].w = w, e[tol].nex = head[u], head[u] = tol, tol++;
}
int son[MAXN], f[MAXN], vis[MAXN];
int t[5], dis[MAXN];
int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) head[i] = -1;
    tol = 0;
    for (int i = 2; i <= n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        w %= 3;
        addEdge(u, v, w), addEdge(v, u, w);
    }
    int root = 0, sum = n;
    f[0] = n;
    function<void(int, int)> get_root = [&](int u, int fa) {
        son[u] = 1, f[u] = 0;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            if (vis[v] || v == fa) continue;
            get_root(v, u);
            son[u] += son[v];
            f[u] = max(f[u], son[v]);
        }
        f[u] = max(f[u], sum - son[u]);
        if (f[u] < f[root]) root = u;
    };
    get_root(1, 0);
    function<void(int, int)> get_dis = [&](int u, int fa) {
        t[dis[u]]++;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w;
            if (v == fa || vis[v]) continue;
            dis[v] = (dis[u] + w) % 3;
            get_dis(v, u);
        }
    };
    auto cal = [&](int u, int x) {
        t[0] = t[1] = t[2] = 0;
        dis[u] = x;
        get_dis(u, 0);
        return t[1] * t[2] * 2 + t[0] * t[0];
    };
    int res = 0;
    function<void(int)> solve = [&](int u) {
        res += cal(u, 0);
        vis[u] = 1;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w;
            if (vis[v]) continue;
            res -= cal(v, w);
            root = 0, sum = son[v];
            get_root(v, 0);
            solve(root);
        }
    };
    solve(root);
    int gcdd = __gcd(res, n * n);
    printf("%d/%d", res / gcdd, n * n / gcdd);
}