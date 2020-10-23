/*
    input   output
    3 4     3
    3 4
    1 3 1
    2 1 0
    2 2 0
    3 3 1
*/
struct Query {
    int x, y;
    Query() {}
    Query(int _x, int _y) { x = _x, y = _y; }
};
int fa[MAXN];
int find(int x) {
    if (x == fa[x]) return x;
    else return fa[x] = find(fa[x]);
}
vector<Query> q;
int LH[MAXN], RH[MAXN], L[MAXN], R[MAXN];
int root[MAXN], siz[MAXN], edge[MAXN];

void join(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    fa[fy] = fx;
    if (fx < fy) RH[fx] = RH[fy], L[R[fx]] = fx, R[fx] = R[fy];
    else LH[fx] = LH[fy], R[L[fx]] = fx, L[fx] = L[fy];
    root[fx] = tree.merge(root[fx], root[fy]);
    edge[fx] += edge[fy];
    siz[fx] += siz[fy];
}

int main() {
    int T;  scanf("%d", &T);
    while (T--) {
        int n, m;   scanf("%d%d", &n, &m);
        LH[1] = RH[n] = inf;
        L[n] = n-1;
        for (int i = 1; i < n; i++) {
            scanf("%d", &RH[i]);
            LH[i + 1] = RH[i];
            L[i] = i - 1, R[i] = i + 1;
        }
        tree.init(); q.clear();
        for (int i = 1; i <= n; i++) root[i] = 0;   // init LT's root
        int res = 0;
        for (int i = 1; i <= m; i++) {
            int x, y, z;    scanf("%d%d%d", &x, &y, &z);
            if (z == 1) {
                q.pb(Query(x, y + 1));
            } else {
                if (root[x]) {
                    root[x] = tree.insert(root[x], y);
                } else root[x] = tree.Newnode(y);
                res++;
            }
        }
        sort(q.begin(), q.end(), [&](const Query &ta, const Query &tb) {
            if (ta.y != tb.y) return ta.y < tb.y;
            else return ta.x < tb.x;
        });
        for (int i = 1; i <= n; i++) fa[i] = i;
        for (int i = 1; i <= n; i++) siz[i] = edge[i] = 0;
        for (auto &e : q) {
            int x = find(e.x), y = e.y;
            // 向左溢出
            while (y > LH[x]) join(x, L[x]), x = find(x);
            // 向右溢出
            while (y > RH[x]) join(x, R[x]), x = find(x);
            // 删除水位以下的X
            while (!tree.isempty(root[x]) && tree.top(root[x]) < y) {
                root[x] = tree.pop(root[x]);
                siz[x]++;
            }
            // update result
            if (++edge[x] >= siz[x]) {
                res += (edge[x] - siz[x]);
                siz[x] = edge[x] = 0;
            }
        }
        printf("Case #%d: %d\n", kass++, res);
    }
}
