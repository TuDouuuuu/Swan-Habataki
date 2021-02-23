/*  [input]     [output]
    1           
    6 3
    2 1 4 2 1 3
    P           4
    U 1 2
    P           6
*/
ll a[MAXN];
class SEG { public:
    struct node {
        int l, r;
        ll maxx, sum, lx, rx;
    } T[MAXN << 2];
    inline void push_up(int rt) {
        T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
        T[rt].maxx = max(T[rt << 1].maxx, T[rt << 1 | 1].maxx);
    }
    inline void push_down(int rt) {
        T[rt << 1].lx = max(T[rt].lx, T[rt << 1].lx);
        T[rt << 1 | 1].lx = max(T[rt].lx, T[rt << 1 | 1].lx);
        T[rt << 1].rx = max(T[rt].rx, T[rt << 1].rx);
        T[rt << 1 | 1].rx = max(T[rt].rx, T[rt << 1 | 1].rx);
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        T[rt].lx = T[rt].rx = 0;
        if (l == r) {
            T[rt].maxx = T[rt].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void change(int rt, int pos, ll v) {
        if (T[rt].l == T[rt].r) {
            T[rt].maxx += v;
            T[rt].sum += v;
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) change(rt << 1, pos, v);
        else change(rt << 1 | 1, pos, v);
        push_up(rt);
    }
    void change1(int rt, int L, int R, ll v) {
        if (L <= T[rt].l && T[rt].r <= R) {
            T[rt].lx = max(T[rt].lx, v);
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) change1(rt << 1, L, R, v);
        if (R > mid) change1(rt << 1 | 1, L, R, v);
    }
    void change2(int rt, int L, int R, ll v) {
        if (L <= T[rt].l && T[rt].r <= R) {
            T[rt].rx = max(T[rt].rx, v);
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) change2(rt << 1, L, R, v);
        if (R > mid) change2(rt << 1 | 1, L, R, v);
    }
    ll query(int rt) {
        if (T[rt].maxx <= min(T[rt].lx, T[rt].rx)) {
            return min(T[rt].lx, T[rt].rx) * (T[rt].r - T[rt].l + 1) - T[rt].sum;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        return query(rt << 1) + query(rt << 1 | 1);
    }
} tree;

int main() {
    int T; FI(T);
    while (T--) {
        int n, q; FI(n), FI(q);
        for (int i = 1; i <= n; i++) FI(a[i]);
        tree.build(1, 1, n);
        for (int i = 1; i <= n; i++) {
            tree.change1(1, i, n, a[i]);
            tree.change2(1, 1, i, a[i]);
        }
        while (q--) {
            char opt[2]; FI(opt);
            if (opt[0] == 'P') {
                FO(tree.query(1)); FO('\n');
            } else {
                int pos; ll v; FI(pos), FI(v); // add v in pos
                tree.change(1, pos, v);
                a[pos] += v;
                tree.change1(1, pos, n, a[pos]);
                tree.change2(1, 1, pos, a[pos]);
            }
        }
    }
    Flush;
}