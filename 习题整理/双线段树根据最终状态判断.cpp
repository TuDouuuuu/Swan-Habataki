/*  [input]     [output]
    1           3
    10 7
    3 11 0
    3 11 2
    5 12 1
    8 13 2
    7 11 2
    10 12 1
    9 12 0
*/
class SEG { public:
    struct node {
        int l, r, val;
    } T[MAXN << 2];
    int lazy[MAXN << 2];
    inline void push_down(int rt) {
        if (lazy[rt]) {
            lazy[rt << 1] = lazy[rt], lazy[rt << 1 | 1] = lazy[rt];
            T[rt << 1].val = lazy[rt], T[rt << 1 | 1].val = lazy[rt];
            lazy[rt] = 0;
        }
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r, T[rt].val = 0;
        lazy[rt] = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
    }
    void update(int L, int R, int v, int rt) {
        if (L <= T[rt].l && R >= T[rt].r) {
            T[rt].val = v;
            lazy[rt] = v;
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        push_down(rt);
        if (L <= mid) update(L, R, v, rt << 1);
        if (R > mid) update(L, R, v, rt << 1 | 1);
    }
    int query(int rt, int pos, int l, int r) {
        if (l == r) return T[rt].val;
        int mid = (l + r) >> 1;
        push_down(rt);
        if (pos <= mid) return query(rt << 1, pos, l, mid);
        else return query(rt << 1 | 1, pos, mid + 1, r);
    }
} tree;
class SEG2 { public:
    struct node {
        int l, r, val;
    } T[MAXN << 2];
    int lazy[MAXN << 2];
    inline void push_down(int rt) {
        if (lazy[rt]) {
            lazy[rt << 1] += lazy[rt], lazy[rt << 1 | 1] += lazy[rt];
            T[rt << 1].val += lazy[rt], T[rt << 1 | 1].val += lazy[rt];
            lazy[rt] = 0;
        }
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r, T[rt].val = 0;
        lazy[rt] = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
    }
    void update(int L, int R, int v, int rt) {
        if (L <= T[rt].l && R >= T[rt].r) {
            T[rt].val += v;
            lazy[rt] += v;
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        push_down(rt);
        if (L <= mid) update(L, R, v, rt << 1);
        if (R > mid) update(L, R, v, rt << 1 | 1);
    }
    int query(int rt, int pos, int l, int r) {
        if (l == r) return T[rt].val;
        int mid = (l + r) >> 1;
        push_down(rt);
        if (pos <= mid) return query(rt << 1, pos, l, mid);
        else return query(rt << 1 | 1, pos, mid + 1, r);
    }
} tree2;
typedef pair<int, int> pii;
vector<pii> col[MAXN];
vector<int> vec[MAXN];
int main() {
    int T;mscanf("%d", &T);
    while (T--) {
        int n, q;mscanf("%d%d", &n, &q);
        for (int i = 1; i < MAXN; i++) col[i].clear(), vec[i].clear();
        tree.build(1, 1, n);
        int maxL = -1;
        while (q--) {
            int x, l, k;
            scanf("%d%d%d", &x, &l, &k);
            int L = x - k, R = x + k;
            tree.update(L, R, l, 1);
            maxL = max(maxL, l);
            col[l].push_back(make_pair(x - k, x + k));
        }
        int res = 0;
        for (int i = 1; i <= n; i++) {
            int color = tree.query(1, i, 1, n);
            if (color == 0) res++;
            else vec[color].push_back(i);
        }
        tree2.build(1, 1,n);
        for (int i = 1; i <= maxL; i++) {
            if (SZ(vec[i])) {
                for (auto e: col[i]) {
                    int L = e.first, R = e.second;
                    tree2.update(L, R, 1, 1);
                }
                for (auto e: vec[i]) {
                    if (tree2.query(1, e, 1, n) > 1) res++;
                }
                for (auto e: col[i]) {
                    int L = e.first, R = e.second;
                    tree2.update(L, R, -1, 1);
                }
            }
        }
        printf("%d\n", res);
    }
}