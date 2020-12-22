/*  [input]     [output]
    2 8
    0 0 1
    1 1 2
    3 1 2       2
    1 1 1 1
    3 1 2       0
    1 1 1 1
    2 1 2
    3 1 2       0
    2 1 1
    3 1 2       2
*/
pil a1[MAXN], a2[MAXN];
struct node {
    int l, r;
    pil fi_max, se_max;
    pil fi_min, se_min;
    node() {
        l = 0, r = 0;
        fi_max = se_max = mp(0, -llinf);
        fi_min = se_min = mp(0, llinf);
    }
};
class JLS { public:
    node T[MAXN << 2];
    inline node merge(const node &L, const node &R) {
        node ans;
        ans.l = L.l, ans.r = R.r;
        // max
        if (L.fi_max.second > R.fi_max.second) ans.fi_max = L.fi_max;
        else ans.fi_max = R.fi_max;

        if (L.fi_max.first != R.fi_max.first) {
            if (L.fi_max.second <= R.fi_max.second) ans.se_max = L.fi_max;
            else ans.se_max = R.fi_max;
        }
        if (L.se_max.second > ans.se_max.second && L.se_max.first != ans.fi_max.first) {
            ans.se_max = L.se_max;
        }
        if (R.se_max.second > ans.se_max.second && R.se_max.first != ans.fi_max.first) {
            ans.se_max = R.se_max;
        }
        
        // min
        if (L.fi_min.second < R.fi_min.second) ans.fi_min = L.fi_min;
        else ans.fi_min = R.fi_min;

        if (L.fi_min.first != R.fi_min.first) {
            if (L.fi_min.second >= R.fi_min.second) ans.se_min = L.fi_min;
            else ans.se_min = R.fi_min;
        }
        if (L.se_min.second < ans.se_min.second && L.se_min.first != ans.fi_min.first) {
            ans.se_min = L.se_min;
        }
        if (R.se_min.second < ans.se_min.second && R.se_min.first != ans.fi_min.first) {
            ans.se_min = R.se_min;
        }

        return ans;
    }

    void update1(int rt, int pos) {
        if (T[rt].l == T[rt].r) {
            T[rt].fi_max = a1[T[rt].l], T[rt].se_max = mp(0, -llinf);
            T[rt].fi_min = a1[T[rt].l], T[rt].se_min = mp(0, llinf);
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) update1(rt << 1, pos);
        else update1(rt << 1 | 1, pos);
        T[rt] = merge(T[rt << 1], T[rt << 1 | 1]);
    }

    void update2(int rt, int pos) {
        if (T[rt].l == T[rt].r) {
            T[rt].fi_max = a2[T[rt].l], T[rt].se_max = mp(0, -llinf);
            T[rt].fi_min = a2[T[rt].l], T[rt].se_min = mp(0, llinf);
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) update2(rt << 1, pos);
        else update2(rt << 1 | 1, pos);
        T[rt] = merge(T[rt << 1], T[rt << 1 | 1]);
    }

    void build1(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            T[rt].fi_max = a1[l], T[rt].se_max = mp(0, -llinf);
            T[rt].fi_min = a1[l], T[rt].se_min = mp(0, llinf);
            return;
        }
        int mid = (l + r) >> 1;
        build1(rt << 1, l, mid), build1(rt << 1 | 1, mid + 1, r);
        T[rt] = merge(T[rt << 1], T[rt << 1 | 1]);
    }

    void build2(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            T[rt].fi_max = a2[l], T[rt].se_max = mp(0, -llinf);
            T[rt].fi_min = a2[l], T[rt].se_min = mp(0, llinf);
            return;
        }
        int mid = (l + r) >> 1;
        build2(rt << 1, l, mid), build2(rt << 1 | 1, mid + 1, r);
        T[rt] = merge(T[rt << 1], T[rt << 1 | 1]);
    }

    node query(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt];
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (R <= mid) return query(rt << 1, L, R);
        else if (L > mid) return query(rt << 1 | 1, L, R);
        else {
            node ansl = query(rt << 1, L, R), ansr = query(rt << 1 | 1, L, R);
            return merge(ansl, ansr);
        }
    }
} tree1, tree2;

int main() {
    int T; scanf("%d", &T); int kass = 1;
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            ll x, y; int c; scanf("%lld%lld%d", &x, &y, &c);
            a1[i].first = c, a1[i].second = x + y;
            a2[i].first = c, a2[i].second = x - y;
        }
        tree1.build1(1, 1, n), tree2.build2(1, 1, n);
        printf("Case #%d:\n", kass++);
        while (m--) {
            int opt;
            scanf("%d", &opt);
            if (opt == 1) {
                int k; ll x, y; scanf("%d%lld%lld", &k, &x, &y);
                a1[k].second += x + y, a2[k].second += x - y;
                tree1.update1(1, k), tree2.update2(1, k);
            } else if (opt == 2) {
                int k, c; scanf("%d%d", &k, &c);
                a1[k].first = c, a2[k].first = c;
                tree1.update1(1, k), tree2.update2(1, k);
            } else {
                int l, r; scanf("%d%d", &l, &r);
                if (l == r) {
                    printf("0\n");
                } else {
                    ll res = -1;
                    node ans1 = tree1.query(1, l, r);
                    if (ans1.fi_max.first != ans1.fi_min.first)
                        res = max(res, ans1.fi_max.second - ans1.fi_min.second);
                    if (ans1.fi_max.first != ans1.se_min.first)
                        res = max(res, ans1.fi_max.second - ans1.se_min.second);
                    if (ans1.se_max.first != ans1.fi_min.first)
                        res = max(res, ans1.se_max.second - ans1.fi_min.second);

                    node ans2 = tree2.query(1, l, r);
                    if (ans2.fi_max.first != ans2.fi_min.first)
                        res = max(res, ans2.fi_max.second - ans2.fi_min.second);
                    if (ans2.fi_max.first != ans2.se_min.first)
                        res = max(res, ans2.fi_max.second - ans2.se_min.second);
                    if (ans2.se_max.first != ans2.fi_min.first)
                        res = max(res, ans2.se_max.second - ans2.fi_min.second);

                    if (res == -1) printf("0\n");
                    else printf("%lld\n", res);
                }
            }
        }
    }
}