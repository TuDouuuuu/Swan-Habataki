struct Query {
    int opt, x, y;
} q[MAXN];
ull rnd[MAXN<<2], pre_rnd[MAXN<<2]; // 空间注意！
int a[MAXN];

class SEG { public:
    struct node {
        int l, r, minn;
        ull sum;
    } T[MAXN << 2];

    inline void push_up(int rt) {
        T[rt].minn = min(T[rt << 1].minn, T[rt << 1 | 1].minn);
        T[rt].sum = T[rt << 1].sum ^ T[rt << 1 | 1].sum;
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            T[rt].minn = a[l];
            T[rt].sum = rnd[T[rt].minn];
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }

    void update(int rt, int pos, int val) {
        if (T[rt].l == T[rt].r) {
            T[rt].minn = val;
            T[rt].sum = rnd[T[rt].minn];
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) update(rt << 1, pos, val);
        else update(rt << 1 | 1, pos, val);
        push_up(rt);
    }

    ull query_sum(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].sum;
        int mid = (T[rt].l + T[rt].r) >> 1;
        ull ans = 0;
        if (L <= mid) ans ^= query_sum(rt << 1, L, R);
        if (R > mid) ans ^= query_sum(rt << 1 | 1, L, R);
        return ans;
    }

    int query_min(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) return T[rt].minn;
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = inf;
        if (L <= mid) ans = min(ans, query_min(rt << 1, L, R));
        if (R > mid) ans = min(ans, query_min(rt << 1 | 1, L, R));
        return ans;
    }
} tree;

int main() {
    srand(19260817);
    int n, m;   scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        Discrete::insert(a[i]), Discrete::insert(a[i] + 1);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &q[i].opt, &q[i].x, &q[i].y);
        if (q[i].opt == 1) Discrete::insert(q[i].y), Discrete::insert(q[i].y + 1);
    }

    Discrete::init();
    for (int i = 1; i <= n; i++) {
        a[i] = val2id(a[i]);
    }

    pre_rnd[0] = 0;
    for (int i = 1; i < (MAXN<<2); i++) rnd[i] = Newrnd(), pre_rnd[i] = pre_rnd[i - 1] ^ rnd[i];

    tree.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        if (q[i].opt == 1) {
            tree.update(1, q[i].x, val2id(q[i].y));
        } else {
            int l = tree.query_min(1, q[i].x, q[i].y);
            int r = l + (q[i].y - q[i].x);
            ull tmp1 = pre_rnd[r] ^ pre_rnd[l-1];
            ull tmp2 = tree.query_sum(1, q[i].x, q[i].y);
            if (tmp1 == tmp2) printf("damushen\n"); // 能够重排为值域上连续的一段
            else printf("yuanxing\n");  // 不能够重排为值域上连续的一段
        }
    }
}