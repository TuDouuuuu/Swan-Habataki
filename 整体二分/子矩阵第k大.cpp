/*  [input]         [output]
    2 2
    2 1
    3 4
    1 2 1 2 1       1
    1 1 2 2 3       3           */
class BIT { public:
    int val[MAXN][MAXN]; int n, m;
    void init(int _n, int _m) {
        n = _n, m = _m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                val[i][j] = 0;
    }
    inline int lowbit(int x) { return x & (-x); }
    void add(int x, int y, int v) {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
                val[i][j] += v;
    }
    inline int query(int x, int y) {
        int ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i))
            for (int j = y; j >= 1; j -= lowbit(j))
                ans += val[i][j];
        return ans;
    }
    int query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
} bit;

struct Query {
    int x1, y1, x2, y2, k, val, id, type;
} q[MAXM], q1[MAXM], q2[MAXM];
int res[MAXM];
int a[MAXN][MAXN];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    }
    int qcnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            q[++qcnt] = {i, j, i, j, 0, a[i][j], 0, 1};
        }
    }
    for (int i = 1; i <= m; i++) {
        int x1, y1, x2, y2, k;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
        q[++qcnt] = {x1, y1, x2, y2, k, 0, i, 2};
    }
    bit.init(n, n);
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
                    bit.add(q[i].x1, q[i].y1, 1);
                    q1[++cnt1] = q[i];
                } else q2[++cnt2] = q[i];
            } else {
                int d = bit.query(q[i].x1, q[i].y1, q[i].x2, q[i].y2);
                if (q[i].k <= d) q1[++cnt1] = q[i];
                else {
                    q[i].k -= d;
                    q2[++cnt2] = q[i];
                }
            }
        }
        for (int i = 1; i <= cnt1; i++) {
            if (q1[i].type == 1)
                bit.add(q1[i].x1, q1[i].y1, -1);
        }
        for (int i = 1; i <= cnt1; i++) q[ql + i - 1] = q1[i];
        for (int i = 1; i <= cnt2; i++) q[ql + cnt1 + i - 1] = q2[i];
        solve(l, mid, ql, ql + cnt1 - 1);
        solve(mid + 1, r, ql + cnt1, qr);

    };
    solve(0, 1e9, 1, qcnt);
    for (int i = 1; i <= m; i++) printf("%d\n", res[i]);
}