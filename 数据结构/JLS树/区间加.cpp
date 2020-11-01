class JLS { public:
    struct node {
        int l, r;
        int fi_max, se_max, fi_min, se_min;
        int cnt_max, cnt_min;
        ll sum;
    } T[MAXN << 2];
    ll add[MAXN << 2];
#define lson rt<<1
#define rson rt<<1|1
    inline void push_up(int rt) {
        T[rt].sum = T[lson].sum + T[rson].sum;
        // max
        if (T[lson].fi_max == T[rson].fi_max) {
            T[rt].fi_max = T[lson].fi_max;
            T[rt].se_max = max(T[lson].se_max, T[rson].se_max);
            T[rt].cnt_max = T[lson].cnt_max + T[rson].cnt_max;
        } else if (T[lson].fi_max > T[rson].fi_max) {
            T[rt].fi_max = T[lson].fi_max;
            T[rt].se_max = max(T[lson].se_max, T[rson].fi_max);
            T[rt].cnt_max = T[lson].cnt_max;
        } else {
            T[rt].fi_max = T[rson].fi_max;
            T[rt].se_max = max(T[lson].fi_max, T[rson].se_max);
            T[rt].cnt_max = T[rson].cnt_max;
        }
        // min
        if (T[lson].fi_min == T[rson].fi_min) {
            T[rt].fi_min = T[lson].fi_min;
            T[rt].se_min = min(T[lson].se_min, T[rson].se_min);
            T[rt].cnt_min = T[lson].cnt_min + T[rson].cnt_min;
        } else if (T[lson].fi_min < T[rson].fi_min) {
            T[rt].fi_min = T[lson].fi_min;
            T[rt].se_min = min(T[lson].se_min, T[rson].fi_min);
            T[rt].cnt_min = T[lson].cnt_min;
        } else {
            T[rt].fi_min = T[rson].fi_min;
            T[rt].se_min = min(T[lson].fi_min, T[rson].se_min);
            T[rt].cnt_min = T[rson].cnt_min;
        }
    }

    inline void push_add(int rt, int tg) {
        T[rt].sum += (ll) (T[rt].r - T[rt].l + 1) * tg;
        T[rt].fi_max += tg, T[rt].fi_min += tg;
        if (T[rt].se_max != -inf) T[rt].se_max += tg;
        if (T[rt].se_min != inf) T[rt].se_min += tg;
        add[rt] += tg;
    }

    inline void push_min(int rt, int tg) {
        T[rt].sum = T[rt].sum - (ll) (T[rt].fi_max - tg) * T[rt].cnt_max;
        if (T[rt].fi_max == T[rt].fi_min) T[rt].fi_max = T[rt].fi_min = tg;
        else if (T[rt].fi_max == T[rt].se_min) T[rt].fi_max = T[rt].se_min = tg;
        else T[rt].fi_max = tg;
    }

    inline void push_max(int rt, int tg) {
        T[rt].sum = T[rt].sum + (ll) (tg - T[rt].fi_min) * T[rt].cnt_min;
        if (T[rt].fi_min == T[rt].fi_max) T[rt].fi_min = T[rt].fi_max = tg;
        else if (T[rt].fi_min == T[rt].se_max) T[rt].fi_min = T[rt].se_max = tg;
        else T[rt].fi_min = tg;
    }

    inline void push_down(int rt) {
        if (add[rt]) {
            push_add(lson, add[rt]), push_add(rson, add[rt]);
            add[rt] = 0;
        }
        if (T[rt].fi_max < T[lson].fi_max) push_min(lson, T[rt].fi_max);
        if (T[rt].fi_max < T[rson].fi_max) push_min(rson, T[rt].fi_max);
        if (T[rt].fi_min > T[lson].fi_min) push_max(lson, T[rt].fi_min);
        if (T[rt].fi_min > T[rson].fi_min) push_max(rson, T[rt].fi_min);
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        add[rt] = 0;
        if (l == r) {
            T[rt].sum = T[rt].fi_max = T[rt].fi_min = a[l];
            T[rt].se_max = -inf, T[rt].se_min = inf;
            T[rt].cnt_min = T[rt].cnt_max = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(lson, l, mid), build(rson, mid + 1, r);
        push_up(rt);
    }

    void update_add(int rt, int L, int R, int v) {  // add v to [L, R]
        if (L <= T[rt].l && T[rt].r <= R) {
            push_add(rt, v);
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update_add(lson, L, R, v);
        if (R > mid) update_add(rson, L, R, v);
        push_up(rt);
    }

    void update_min(int rt, int L, int R, int v) {  // a[L],...,a[R] <- min(val, a[i])
        if (v >= T[rt].fi_max) return;
        if (L <= T[rt].l && T[rt].r <= R && T[rt].se_max < v) {
            push_min(rt, v);
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update_min(lson, L, R, v);
        if (R > mid) update_min(rson, L, R, v);
        push_up(rt);
    }

    void update_max(int rt, int L, int R, int v) {  // a[L],...,a[R] <- max(val, a[i])
        if (v <= T[rt].fi_min) return;
        if (L <= T[rt].l && T[rt].r <= R && T[rt].se_min > v) {
            push_max(rt, v);
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update_max(lson, L, R, v);
        if (R > mid) update_max(rson, L, R, v);
        push_up(rt);
    }

    ll query_sum(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].sum;
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        ll ans = 0;
        if (L <= mid) ans += query_sum(lson, L, R);
        if (R > mid) ans += query_sum(rson, L, R);
        return ans;
    }

    int query_max(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].fi_max;
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = -inf;
        if (L <= mid) ans = max(ans, query_max(lson, L, R));
        if (R > mid) ans = max(ans, query_max(rson, L, R));
        return ans;
    }

    int query_min(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].fi_min;
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = inf;
        if (L <= mid) ans = min(ans, query_min(lson, L, R));
        if (R > mid) ans = min(ans, query_min(rson, L, R));
        return ans;
    }
} tree;
