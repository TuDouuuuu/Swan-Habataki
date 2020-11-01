using namespace Discrete; // 矩形并面积中的namespace Discrete
struct LINE {
    int x, y1, y2, l;
    LINE() {}
    LINE(int _x, int _y1, int _y2, int _l) {
        x = _x, y1 = _y1, y2 = _y2, l = _l;
    }
} line[MAXN << 1];
class SEG { public:
    struct node {
        int l, r, maxx;
    } T[MAXN << 3]; // 8倍注意!
    int lazy[MAXN << 3];

    inline void push_up(int rt) {
        T[rt].maxx = max(T[rt << 1].maxx, T[rt << 1 | 1].maxx);
    }
    inline void push_down(int rt) {
        if (lazy[rt]) {
            T[rt << 1].maxx += lazy[rt], lazy[rt << 1] += lazy[rt];
            T[rt << 1 | 1].maxx += lazy[rt], lazy[rt << 1 | 1] += lazy[rt];
            lazy[rt] = 0;
        }
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        lazy[rt] = 0;
        if (l == r) {
            T[rt].maxx = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }

    void update(int rt, int L, int R, int v) {
        if (L <= T[rt].l && T[rt].r <= R) {
            T[rt].maxx += v;
            lazy[rt] += v;
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update(rt << 1, L, R, v);
        if (R > mid) update(rt << 1 | 1, L, R, v);
        push_up(rt);
    }
} tree;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, w, h; scanf("%d%d%d", &n, &w, &h);
        init();
        for (int i = 1; i <= n; i++) {
            int x, y, l; scanf("%d%d%d", &x, &y, &l);
            line[i] = LINE(x, y, y + h - 1, l);
            line[i+n] = LINE(x + w - 1, y, y + h - 1, -l);
            push(y + h - 1);
            push(y);
        }
        n <<= 1;
        build();
        sort(line + 1, line + 1 + n, [&](const LINE &ta, const LINE &tb) {
            if (ta.x != tb.x) return ta.x < tb.x;
            return ta.l > tb.l;
        });
        tree.build(1, 1, blen);
        int res = 0;
        for (int i = 1; i <= n; i++) {
            int l = lower_bound(b+1, b+1+blen, line[i].y1) - b;
            int r = lower_bound(b+1, b+1+blen, line[i].y2) - b;
            tree.update(1, l, r, line[i].l);
            res = max(res, tree.T[1].maxx);
        }
        printf("%d\n", res);
    }
}