const int MAXLOG = 22;
struct Edge {
    int to, nex;
} e[MAXM << 1];
int head[MAXN], tol;
void addEdge(int u, int v) {
    e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
}
namespace LCA {
    int dep[MAXN], fa[MAXN][MAXLOG], lg[MAXN];
    void init(int _n) { // n为点的个数，最坏情况为一条链
        for (int i = 1; i <= _n; i++) {
            lg[i] = lg[i-1] + (1 << lg[i-1] == i);
        }
    }
    void dfs(int u, int f) {
        fa[u][0] = f; dep[u] = dep[f] + 1;
        for (int i = 1; i <= lg[dep[u]]; i++) fa[u][i] = fa[fa[u][i-1]][i-1];
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
}