/*  [input]         [output]
    2
    4 2             2
    3 -2  4 -2
    5 4             -1
    -1 -1 -1 -1 6
*/
class SEG { public:
    struct node {
        int l, r, maxx;
    } T[MAXN << 2];

    inline void push_up(int rt) {
        T[rt].maxx = max(T[rt << 1].maxx, T[rt << 1 | 1].maxx);
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            T[rt].maxx = -inf;
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void update(int rt, int pos, int v) {
        if (T[rt].l == T[rt].r) {
            T[rt].maxx = v;
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) update(rt << 1, pos, v);
        else update(rt << 1 | 1, pos, v);
        push_up(rt);
    }
    int query(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].maxx;
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = -inf;
        if (L <= mid) ans = max(ans, query(rt << 1, L, R));
        if (R > mid) ans = max(ans, query(rt << 1 | 1, L, R));
        return ans;
    }
} tree;
int n, k;
int a[MAXN];
ll sum[MAXN];
bool check(ll mid) {
    tree.build(1, 1, Discrete::blen);
    int pos = val2id(0);
    tree.update(1, pos, 0);
    for (int i = 1; i <= n; i++) {
        pos = val2id(sum[i] - mid);
        int tmp = tree.query(1, pos, Discrete::blen);
        tree.update(1, val2id(sum[i]), tmp + 1);
    }
    if (tree.T[1].maxx >= k) return 1;
    else return 0;
}
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        Discrete::btol = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        Discrete::insert(0);
        Discrete::insert(-llinf), Discrete::insert(llinf);      // 防止出锅
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i], Discrete::insert(sum[i]);
        Discrete::init();

        ll L = -llinf, R = llinf;   // 二分范围注意！不然会在超大数据挂掉……
        while (L < R) {
            ll mid = (L + R) >> 1;
            if (check(mid)) R = mid;
            else L = mid+1;
        }
        printf("%lld\n", L);
    }
}