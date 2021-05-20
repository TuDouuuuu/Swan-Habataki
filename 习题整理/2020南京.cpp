int a[MAXN];
class JLS { public:
    struct node {
        int l, r; int fi_min, se_min;
        int cnt_min; int sum, bit[31];
    } T[MAXN << 2];
    int lazy[MAXN << 2];
#define lson rt<<1
#define rson rt<<1|1
    inline void push_up(int rt) {
        T[rt].sum = T[lson].sum ^ T[rson].sum;
        for (int i = 0; i < 31; i++) T[rt].bit[i] = T[lson].bit[i] + T[rson].bit[i];
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
    inline void push_tag(int rt, int tg) {
        if (T[rt].fi_min >= tg) return;
        T[rt].sum ^= (T[rt].cnt_min & 1) * (T[rt].fi_min ^ tg);
        for (int i = 0; i < 31; i++) {
            if (T[rt].fi_min >> i & 1)T[rt].bit[i] -= T[rt].cnt_min;
            if (tg >> i & 1) T[rt].bit[i] += T[rt].cnt_min;
        }
        T[rt].fi_min = lazy[rt] = tg;
    }
    inline void push_down(int rt) {
        if (lazy[rt] != -1) {
            push_tag(lson, lazy[rt]), push_tag(rson, lazy[rt]);
            lazy[rt] = -1;
        }
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r; lazy[rt] = -1;
        if (l == r) {
            T[rt].sum = T[rt].fi_min = a[l];
            T[rt].se_min = inf; T[rt].cnt_min = 1;
            for (int i = 0; i < 31; i++) {
                T[rt].bit[i] = (a[l] >> i) & 1;
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(lson, l, mid), build(rson, mid + 1, r);
        push_up(rt);
    }

    void update(int rt, int L, int R, int v) {
        if (v <= T[rt].fi_min) return;
        if (L <= T[rt].l && T[rt].r <= R && T[rt].se_min > v) {
            push_tag(rt, v);
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update(lson, L, R, v);
        if (R > mid) update(rson, L, R, v);
        push_up(rt);
    }

    int query_sum(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].sum;
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = 0;
        if (L <= mid) ans ^= query_sum(lson, L, R);
        if (R > mid) ans ^= query_sum(rson, L, R);
        return ans;
    }

    int query_bit(int rt, int L, int R, int pos) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].bit[pos];
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = 0;
        if (L <= mid) ans += query_bit(lson, L, R, pos);
        if (R > mid) ans += query_bit(rson, L, R, pos);
        return ans;
    }
} tree;

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    tree.build(1, 1, n);
    while (q--) {
        int opt, l, r, x; scanf("%d%d%d%d", &opt, &l, &r, &x);
        if (opt == 1) {
            tree.update(1, l, r, x);
        } else {
            int res = tree.query_sum(1, l, r); res ^= x;
            if (res == 0) {
                printf("0\n");
            } else {
                int ans = 0, k = 0;
                for (int i = 30; i >= 0; i--) {
                    if ((res >> i) & 1) {
                        k = i; break;
                    }
                }
                ans = tree.query_bit(1, l, r, k) + ((x >> k) & 1);
                printf("%d\n", ans);
            }
        }
    }
}