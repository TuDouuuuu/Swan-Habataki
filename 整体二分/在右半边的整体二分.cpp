class BIT_LL { public:
    __int128 val[MAXN], n;
    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++) val[i] = 0;
    }
    inline int lowbit(int x) { return x & (-x); }
    void add(int pos, __int128 v) {
        for (int i = pos; i <= n; i += lowbit(i)) val[i] += v;
    }
    __int128 query(int pos) {
        __int128 ans = 0;
        for (int i = pos; i >= 1; i -= lowbit(i)) ans += val[i];
        return ans;
    }
    __int128 query(int L, int R) {
        return query(R) - query(L - 1);
    }
} bit1, bit2;
struct Query {
    int d, p, l;
    ll g, L;
    int id;
} q[MAXN << 1], q1[MAXN << 1], q2[MAXN << 1];
int res[MAXN], type[MAXN];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    bit1.init(1e5), bit2.init(1e5);
    int qcnt = 0;
    for (int i = 1; i <= n; i++) {
        int d, p, l;
        scanf("%d%d%d", &d, &p, &l);
        q[++qcnt] = {d, p, l, 0, 0, 0};
        bit1.add(q[i].p, (ll) l);
        bit2.add(q[i].p, (ll) l * p);
    }
    for (int i = 1; i <= m; i++) {
        ll g, L;
        scanf("%lld%lld", &g, &L);
        ll tmp = bit1.query(1e5);
        if (L > tmp) {
            type[i] = 0;
        } else {
            int posL = 1, posR = 1e5;
            while (posL < posR) {
                int mid = (posL + posR) >> 1;
                if (bit1.query(mid) < L) posL = mid + 1;
                else posR = mid;
            }
            int pos = posL;

            ll momo = bit2.query(pos - 1) +
                      (L - bit1.query(pos - 1)) * (bit2.query(pos, pos) / bit1.query(pos, pos));
            if (momo > g) type[i] = 0;
            else type[i] = 1, q[++qcnt] = {0, 0, 0, g, L, i};
        }
    }
    bit1.init(1e5), bit2.init(1e5);
    function<void(int, int, int, int)> solve = [&](int l, int r, int ql, int qr) {
        if (ql > qr) return;
        if (l == r) {
            for (int i = ql; i <= qr; i++) {
                if (q[i].id && type[q[i].id]) {
                    res[q[i].id] = l;
                }
            }
            return;
        }
        int mid = (l + r + 1) >> 1;
        int cnt1 = 0, cnt2 = 0;
        for (int i = ql; i <= qr; i++) {
            if (q[i].id == 0) {
                if (q[i].d >= mid) {
                    bit1.add(q[i].p, (ll) q[i].l);
                    bit2.add(q[i].p, (ll) q[i].l * q[i].p);
                    q2[++cnt2] = q[i];
                } else q1[++cnt1] = q[i];
            } else {
                ll tmp = bit1.query(1e5);
                if (q[i].L > tmp) {
                    q1[++cnt1] = q[i];
                } else {
                    int posL = 1, posR = 1e5;
                    while (posL < posR) {
                        int mid = (posL + posR) >> 1;
                        if (bit1.query(mid) < q[i].L) posL = mid + 1;
                        else posR = mid;
                    }
                    int pos = posL;
                    __int128 momo = (__int128) bit2.query(pos - 1) +
                                    ((__int128) q[i].L - (__int128) bit1.query(pos - 1)) *
                                    (__int128) ((__int128) bit2.query(pos, pos) / (__int128) bit1.query(pos, pos));
                    if (momo > q[i].g) q1[++cnt1] = q[i];
                    else q2[++cnt2] = q[i];
                }
            }
        }
        for (int i = 1; i <= cnt1; i++) q[ql + i - 1] = q1[i];
        for (int i = 1; i <= cnt2; i++) q[ql + cnt1 + i - 1] = q2[i];
        solve(l, mid - 1, ql, ql + cnt1 - 1);
        for (int i = 1; i <= cnt2; i++) {
            if (q[ql + cnt1 + i - 1].id == 0) {
                bit1.add(q[ql + cnt1 + i - 1].p, 0ll - (ll) q[ql + cnt1 + i - 1].l);
                bit2.add(q[ql + cnt1 + i - 1].p, 0ll - (ll) q[ql + cnt1 + i - 1].l * q[ql + cnt1 + i - 1].p);
            }
        }
        solve(mid, r, ql + cnt1, qr);
    };
    solve(1, 1e5, 1, qcnt);
    for (int i = 1; i <= m; i++)
        if (type[i]) printf("%d\n", res[i]);
        else printf("-1\n");
}