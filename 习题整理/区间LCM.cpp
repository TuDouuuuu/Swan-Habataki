class HJT { public:
    int ch[MAXN * 400][2], val[MAXN * 400]; int tot;
    HJT() {
        tot = 0; val[0] = 1;
    }
    inline void push_up(int rt) {
        val[rt] = (ll) val[ch[rt][0]] * val[ch[rt][1]] % mod;
    }
    int update(int rt, int pos, int v, int be, int en) {
        int nrt = ++tot;
        ch[nrt][0] = ch[nrt][1] = val[nrt] = 0;
        if (be == en) {
            val[nrt] = (ll) val[rt] * v % mod;
            return nrt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) {
            ch[nrt][0] = update(ch[rt][0], pos, v, be, mid);
            ch[nrt][1] = ch[rt][1];
        } else {
            ch[nrt][0] = ch[rt][0];
            ch[nrt][1] = update(ch[rt][1], pos, v, mid + 1, en);
        }
        push_up(nrt);
        return nrt;
    }
    int query(int rt, int L, int R, int be, int en) {
        if (L <= be && en <= R) return val[rt];
        int ans = 1, mid = (be + en) >> 1;
        if (L <= mid) ans = (ll) ans * query(ch[rt][0], L, R, be, mid) % mod;
        if (R > mid) ans = (ll) ans * query(ch[rt][1], L, R, mid + 1, en) % mod;
        return ans;
    }
} tree;
int a[MAXN], root[MAXN]; int pre[MAXM], pm[MAXM];
int main() {
    for (int i = 2; i < MAXM; i++) {
        if (!pm[i]) {
            for (int j = 1; j < MAXM; j++) {
                if ((ll) i * j >= (ll) MAXM) break;
                pm[i * j] = i;
            }
        }
    }
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        int x = a[i];
        root[i] = root[i - 1];
        vector<pii > vec;
        while (pm[x]) {
            int now = pm[x], cnt = 0, k = 1;
            int inv_now = inv(now);
            while (x % now == 0) {
                x /= now, cnt++, k *= now;
                if (pre[k]) vec.pb(mp(pre[k], inv_now));
                pre[k] = i;
            }
            pre[k] = i;
            if (k != 1) root[i] = tree.update(root[i], i, k, 1, n);// printf("i = %d k = %d\n", i, k);
        }

        if (x) {
            if (pre[x]) vec.pb(mp(pre[x], inv(x)));
            pre[x] = i;
            if (x != 1) root[i] = tree.update(root[i], i, x, 1, n);//, printf("i = %d x = %d\n", i, x);
        }
        int ans = 1;
        for (int j = 0; j < SZ(vec); j++) {
            if (j == 0 || vec[j - 1].fi != vec[j].fi) ans = 1;
            ans = (ll) ans * vec[j].se % mod;
            if (j == SZ(vec) - 1 || vec[j].fi != vec[j + 1].fi)
                if (ans != 1)
                    root[i] = tree.update(root[i], vec[j].fi, ans, 1, n);
        }
    }
    int lastans = 0;
    int q; scanf("%d", &q);
    while (q--) {
        int l, r, x, y; scanf("%d%d", &x, &y);
        l = (x + lastans) % n + 1, r = (y + lastans) % n + 1;
        if (l > r) swap(l, r);
        lastans = tree.query(root[r], l, r, 1, n);
        printf("%d\n", lastans);
    }
}