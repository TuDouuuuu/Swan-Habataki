class SEG { public:
    struct node {
        int l, r;
        int len[2], pre[2], suf[2];
    } T[MAXN << 2];
    inline void push_up(int rt) {
        for (int i = 0; i < 2; i++) {
            T[rt].pre[i] = T[rt << 1].pre[i];
            T[rt].suf[i] = T[rt << 1 | 1].suf[i];
            T[rt].len[i] = max(T[rt << 1].len[i], T[rt << 1 | 1].len[i]);
            T[rt].len[i] = max(T[rt].len[i], T[rt << 1].suf[i] + T[rt << 1 | 1].pre[i]);
            if (T[rt << 1].pre[i] == T[rt << 1].r - T[rt << 1].l + 1) T[rt].pre[i] += T[rt << 1 | 1].pre[i];
            if (T[rt << 1 | 1].suf[i] == T[rt << 1 | 1].r - T[rt << 1 | 1].l + 1) T[rt].suf[i] += T[rt << 1].suf[i];
        }
    }
    inline void push_down(int rt) {
        for (int i = 0; i < 2; i++) {
            if (T[rt].len[i] == 0) {
                T[rt << 1].len[i] = T[rt << 1].pre[i] = T[rt << 1].suf[i] = 0;
                T[rt << 1 | 1].len[i] = T[rt << 1 | 1].pre[i] = T[rt << 1 | 1].suf[i] = 0;
            }
            if (T[rt].len[i] == T[rt].r - T[rt].l + 1) {
                T[rt << 1].len[i] = T[rt << 1].pre[i] = T[rt << 1].suf[i] = T[rt << 1].r - T[rt << 1].l + 1;
                T[rt << 1 | 1].len[i] = T[rt << 1 | 1].pre[i] = T[rt << 1 | 1].suf[i] =
                        T[rt << 1 | 1].r - T[rt << 1 | 1].l + 1;
            }
        }
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            for (int i = 0; i < 2; i++) {
                T[rt].len[i] = T[rt].pre[i] = T[rt].suf[i] = 1;
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void study(int rt, int L, int R) {
        if (L <= T[rt].l && T[rt].r <= R) {
            for (int i = 0; i < 2; i++) {
                T[rt].len[i] = T[rt].pre[i] = T[rt].suf[i] = T[rt].r - T[rt].l + 1;
            }
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) study(rt << 1, L, R);
        if (R > mid) study(rt << 1 | 1, L, R);
        push_up(rt);
    }
    void play(int rt, int L, int R, int op) {
        if (L <= T[rt].l && T[rt].r <= R) {
            T[rt].len[op] = T[rt].pre[op] = T[rt].suf[op] = 0;
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) play(rt << 1, L, R, op);
        if (R > mid) play(rt << 1 | 1, L, R, op);
        push_up(rt);
    }
    int query(int rt, int v, int op) {
        if (T[rt].l == T[rt].r) return T[rt].l;
        push_down(rt);
        int ans = -1;
        if (T[rt << 1].len[op] >= v)
            ans = query(rt << 1, v, op);
        if (ans == -1 && T[rt<<1].suf[op] + T[rt<<1|1].pre[op] >= v)
            ans = T[rt << 1].r - T[rt << 1].suf[op] + 1;
        if (ans == -1 && T[rt << 1 | 1].len[op] >= v)
            ans = query(rt << 1 | 1, v, op);
        return ans;
    }
} tree;

int main() {
    int T; scanf("%d", &T);
    int kass = 0;
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        tree.build(1, 1, n);
        while (m--) {
            char opt[10]; scanf("%s", opt);
            if (opt[0] == 'N') {
                int x; scanf("%d", &x);
                int ans = tree.query(1, x, 1);
                if (ans == -1) ans = tree.query(1, x, 0);
                if (ans == -1) printf("wait for me\n");
                else {
                    printf("%d,don't put my gezi\n", ans);
                    tree.play(1, ans, ans + x - 1, 0);
                    tree.play(1, ans, ans + x - 1, 1);
                }
            } else if (opt[0] == 'D') {
                int x; scanf("%d", &x);
                int ans = tree.query(1, x, 1);
                if (ans == -1) printf("fly with yourself\n");
                else {
                    printf("%d,let's fly\n", ans);
                    tree.play(1, ans, ans + x - 1, 1);
                }
            } else {
                int l, r; scanf("%d%d", &l, &r);
                tree.study(1, l, r);
                printf("I am the hope of chinese chengxuyuan!!\n");
            }
        }
    }
}
