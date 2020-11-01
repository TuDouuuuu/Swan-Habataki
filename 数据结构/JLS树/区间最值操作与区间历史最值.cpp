class JLS { public:
    struct node1 {  // 实时信息
        int l, r;   // 左端点，右端点
        int fi_max, se_max, cnt_max; // 当前区间最大值，区间次大值，区间最大值个数
        int fi_add, se_add; // 区间最大值lazy标记，区间次大值lazy标记
        ll sum;    // 当前区间和
    } now[MAXN << 2];
    struct node2 {  // 历史信息
        int fi_max; // 历史区间最大值
        int fi_add, se_add; // 历史区间最大值lazy标记，区间次大值lazy标记
    } old[MAXN << 2];
#define lson rt<<1
#define rson rt<<1|1
    inline void push_up(int rt) {
        now[rt].sum = now[lson].sum + now[rson].sum;
        old[rt].fi_max = max(old[lson].fi_max, old[rson].fi_max);
        // max
        if (now[lson].fi_max == now[rson].fi_max) {
            now[rt].fi_max = now[lson].fi_max;
            now[rt].se_max = max(now[lson].se_max, now[rson].se_max);
            now[rt].cnt_max = now[lson].cnt_max + now[rson].cnt_max;
        } else if (now[lson].fi_max > now[rson].fi_max) {
            now[rt].fi_max = now[lson].fi_max;
            now[rt].se_max = max(now[lson].se_max, now[rson].fi_max);
            now[rt].cnt_max = now[lson].cnt_max;
        } else {
            now[rt].fi_max = now[rson].fi_max;
            now[rt].se_max = max(now[lson].fi_max, now[rson].se_max);
            now[rt].cnt_max = now[rson].cnt_max;
        }
    }

    // v1, v3 change now; v2, v4 change old;
    inline void push_node(int rt, int v1, int v2, int v3, int v4) {
        old[rt].fi_max = max(old[rt].fi_max, now[rt].fi_max + v2);
        old[rt].fi_add = max(old[rt].fi_add, now[rt].fi_add + v2);
        old[rt].se_add = max(old[rt].se_add, now[rt].se_add + v4);

        now[rt].sum += 1ll * v1 * now[rt].cnt_max +
                       1ll * v3 * (now[rt].r - now[rt].l + 1 - now[rt].cnt_max);
        now[rt].fi_max += v1;
        if (now[rt].se_max != inf) now[rt].se_max += v3;
        now[rt].fi_add += v1, now[rt].se_add += v3;
    }

    inline void push_down(int rt) {
        int tmp = max(now[lson].fi_max, now[rson].fi_max);

        if (now[lson].fi_max == tmp) push_node(lson, now[rt].fi_add, old[rt].fi_add, now[rt].se_add, old[rt].se_add);
        else push_node(lson, now[rt].se_add, old[rt].se_add, now[rt].se_add, old[rt].se_add);

        if (now[rson].fi_max == tmp) push_node(rson, now[rt].fi_add, old[rt].fi_add, now[rt].se_add, old[rt].se_add);
        else push_node(rson, now[rt].se_add, old[rt].se_add, now[rt].se_add, old[rt].se_add);

        now[rt].fi_add = now[rt].se_add = old[rt].fi_add = old[rt].se_add = 0;
    }

    void build(int rt, int l, int r) {
        now[rt].l = l, now[rt].r = r;
        now[rt].fi_add = now[rt].se_add = 0;
        old[rt].fi_add = old[rt].se_add = 0;
        if (l == r) {
            now[rt].sum = now[rt].fi_max = a[l];
            now[rt].cnt_max = 1;
            now[rt].se_max = -inf;

            old[rt].fi_max = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lson, l, mid), build(rson, mid + 1, r);
        push_up(rt);
    }

    void update_add(int rt, int L, int R, int v) {  // op1
        if (L <= now[rt].l && now[rt].r <= R) {
            push_node(rt, v, v, v, v);
            return;
        }
        push_down(rt);
        int mid = (now[rt].l + now[rt].r) >> 1;
        if (L <= mid) update_add(lson, L, R, v);
        if (R > mid) update_add(rson, L, R, v);
        push_up(rt);
    }

    void update_min(int rt, int L, int R, int v) {  // op2
        if (v >= now[rt].fi_max) return;
        if (L <= now[rt].l && now[rt].r <= R && now[rt].se_max < v) {
            push_node(rt, v - now[rt].fi_max, v - now[rt].fi_max, 0, 0);
            return;
        }
        push_down(rt);
        int mid = (now[rt].l + now[rt].r) >> 1;
        if (L <= mid) update_min(lson, L, R, v);
        if (R > mid) update_min(rson, L, R, v);
        push_up(rt);
    }

    ll query_sum(int rt, int L, int R) {    // op3
        if (L <= now[rt].l && now[rt].r <= R) return now[rt].sum;
        push_down(rt);
        int mid = (now[rt].l + now[rt].r) >> 1;
        ll ans = 0;
        if (L <= mid) ans += query_sum(lson, L, R);
        if (R > mid) ans += query_sum(rson, L, R);
        return ans;
    }

    int query_max1(int rt, int L, int R) {  // op4
        if (L <= now[rt].l && now[rt].r <= R) return now[rt].fi_max;
        push_down(rt);
        int mid = (now[rt].l + now[rt].r) >> 1;
        int ans = -inf;
        if (L <= mid) ans = max(ans, query_max1(lson, L, R));
        if (R > mid) ans = max(ans, query_max1(rson, L, R));
        return ans;
    }

    int query_max2(int rt, int L, int R) {  // op5
        if (L <= now[rt].l && now[rt].r <= R) return old[rt].fi_max;
        push_down(rt);
        int mid = (now[rt].l + now[rt].r) >> 1;
        int ans = -inf;
        if (L <= mid) ans = max(ans, query_max2(lson, L, R));
        if (R > mid) ans = max(ans, query_max2(rson, L, R));
        return ans;
    }
#undef lson
#undef rson
} tree;