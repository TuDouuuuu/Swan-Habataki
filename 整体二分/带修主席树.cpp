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
    int query(int l, int r) { return query(r) - query(l - 1); }
} tree;
struct Query {
    int l, r, k, val, id, type;
} q[MAXN << 1], q1[MAXN << 1], q2[MAXN << 1];
int a[MAXN], res[MAXN], type[MAXN];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int qcnt = 0;
    for (int i = 1; i <= n; i++) {
        q[++qcnt] = {0, 0, 0, a[i], i, 1};
    }
    for (int i = 1; i <= m; i++) {
        char opt[3];
        scanf("%s", opt);
        if (opt[0] == 'Q') {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            q[++qcnt] = {l, r, k, 0, i, 2};
            type[i] = 1;
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            q[++qcnt] = {0, 0, 0, a[x], x, 3};
            q[++qcnt] = {0, 0, 0, y, x, 1};
            a[x] = y;
        }
    }

    tree.init(n);
    function<void(int, int, int, int)> solve = [&](int l, int r, int ql, int qr) {
        if (ql > qr) return;
        if (l == r) {
            for (int i = ql; i <= qr; i++) {
                if (q[i].type == 2) res[q[i].id] = l;
            }
            return;
        }
        int mid = (l + r) >> 1;
        int cnt1 = 0, cnt2 = 0;
        for (int i = ql; i <= qr; i++) {
            if (q[i].type == 1) {
                if (q[i].val <= mid) {
                    tree.add(q[i].id, 1);
                    q1[++cnt1] = q[i];
                } else {
                    q2[++cnt2] = q[i];
                }
            } else if (q[i].type == 3) {
                if (q[i].val <= mid) {
                    tree.add(q[i].id, -1);
                    q1[++cnt1] = q[i];
                } else {
                    q2[++cnt2] = q[i];
                }
            } else {
                int d = tree.query(q[i].l, q[i].r);
                if (q[i].k <= d) {
                    q1[++cnt1] = q[i];
                } else {
                    q[i].k -= d;
                    q2[++cnt2] = q[i];
                }
            }
        }
        for (int i = 1; i <= cnt1; i++) {
            if (q1[i].type == 1) tree.add(q1[i].id, -1);
            else if (q1[i].type == 3) tree.add(q1[i].id, 1);
        }
        for (int i = 1; i <= cnt1; i++) q[ql + i - 1] = q1[i];
        for (int i = 1; i <= cnt2; i++) q[ql + cnt1 + i - 1] = q2[i];
        solve(l, mid, ql, ql + cnt1 - 1);
        solve(mid + 1, r, ql + cnt1, qr);
    };
    solve(0, 1e9, 1, qcnt);
    for (int i = 1; i <= m; i++) {
        if (type[i]) printf("%d\n", res[i]);
    }
}