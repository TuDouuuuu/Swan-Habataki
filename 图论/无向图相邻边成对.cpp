vector<pii > res;
int vis[MAXN];
int dfs(int u) {
    vis[u] = 1;
    int cur = -1;
    for (int i = head[u]; ~i; i = e[i].nex) {
        int v = e[i].to, id = e[i].id;
        if (vis[v] == 1) continue;
        int tx1 = id;
        if (!vis[v]) {
            int tx2 = dfs(v);
            if (tx2 != -1) {
                res.pb(mp(tx1, tx2));
                tx1 = -1;
            }
        }
        if (tx1 != -1) {
            if (cur != -1) {
                res.pb(mp(tx1, cur));
                cur = -1;
            } else cur = tx1;
        }
    }
    vis[u] = 2;
    return cur;
}

int main() {
    int n; scanf("%d", &n);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        ll a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        ll gcdd1 = __gcd(c * b, d * (a + b)), gcdd2 = __gcd(b * (c + d), d * a);
        pll ks1 = mp(c * b / gcdd1, d * (a + b) / gcdd1);
        pll ks2 = mp(b * (c + d) / gcdd2, d * a / gcdd2);

        if (ma.find(ks1) == ma.end()) {
            ma[ks1] = ++cnt, head[cnt] = -1;
        }
        if (ma.find(ks2) == ma.end()) {
            ma[ks2] = ++cnt, head[cnt] = -1;
        }
        addEdge(ma[ks1], ma[ks2], i), addEdge(ma[ks2], ma[ks1], i);
    }
    for (int i = 1; i <= cnt; i++) {
        if (!vis[i]) dfs(i);
    }
    printf("%d\n", SZ(res));
    for (auto e: res) { printf("%d %d\n", e.first, e.second); }

}
