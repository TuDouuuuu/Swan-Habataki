class JLS { public:
    struct node {
        int l, r;
        int fi_max, se_max, max_cnt;    // 最大值，次大值，最大值个数
        ll sum;
    } T[MAXN << 2];
    int lazy[MAXN << 2];

    inline void push_up(int rt) {
        T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
        if (T[rt << 1].fi_max == T[rt << 1 | 1].fi_max) { // 左右儿子的最大值相同
            T[rt].fi_max = T[rt << 1].fi_max;
            T[rt].se_max = max(T[rt << 1].se_max, T[rt << 1 | 1].se_max);
            T[rt].max_cnt = T[rt << 1].max_cnt + T[rt << 1 | 1].max_cnt;
        } else if (T[rt << 1].fi_max > T[rt << 1 | 1].fi_max) {
            T[rt].fi_max = T[rt << 1].fi_max;
            T[rt].se_max = max(T[rt << 1].se_max, T[rt << 1 | 1].fi_max);
            T[rt].max_cnt = T[rt << 1].max_cnt;
        } else {
            T[rt].fi_max = T[rt << 1 | 1].fi_max;
            T[rt].se_max = max(T[rt << 1].fi_max, T[rt << 1 | 1].se_max);
            T[rt].max_cnt = T[rt << 1 | 1].max_cnt;
        }
    }

    inline void push_down(int rt) {
        if (lazy[rt] != -1) {
            if (T[rt << 1].fi_max > lazy[rt]) {   // left son
                T[rt << 1].sum += (1ll * lazy[rt] - T[rt << 1].fi_max) * T[rt << 1].max_cnt;
                T[rt << 1].fi_max = lazy[rt], lazy[rt << 1] = lazy[rt];
            }
            if (T[rt << 1 | 1].fi_max > lazy[rt]) { // right son
                T[rt << 1 | 1].sum += (1ll * lazy[rt] - T[rt << 1 | 1].fi_max) * T[rt << 1 | 1].max_cnt;
                T[rt << 1 | 1].fi_max = lazy[rt], lazy[rt << 1 | 1] = lazy[rt];
            }
            lazy[rt] = -1;
        }
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        lazy[rt] = -1;
        if (l == r) {
            T[rt].sum = T[rt].fi_max = a[l], T[rt].se_max = -1, T[rt].max_cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }

    void update_min(int rt, int L, int R, int val) {    // a[L],...,a[R] <- min(val, a[i])
        if (T[rt].fi_max <= val) return;
        if (L <= T[rt].l && T[rt].r <= R && T[rt].se_max < val) {
            if (T[rt].fi_max > val) {
                T[rt].sum += (1ll * val - T[rt].fi_max) * T[rt].max_cnt;
                T[rt].fi_max = val, lazy[rt] = val;
            }
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update_min(rt << 1, L, R, val);
        if (R > mid) update_min(rt << 1 | 1, L, R, val);
        push_up(rt);
    }

    int query_max(int rt, int L, int R) {   // find max value
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].fi_max;
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = -1;
        if (L <= mid) ans = max(ans, query_max(rt << 1, L, R));
        if (R > mid) ans = max(ans, query_max(rt << 1 | 1, L, R));
        return ans;
    }

    ll query_sum(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].sum;
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        ll ans = 0;
        if (L <= mid) ans += query_sum(rt << 1, L, R);
        if (R > mid) ans += query_sum(rt << 1 | 1, L, R);
        return ans;
    }
} tree;