struct Line {
    ll x, y1, y2;
    int mark;
    Line() {}
    Line(ll _x, ll _y1, ll _y2, int _mark) {
        x = _x, y1 = _y1, y2 = _y2, mark = _mark;
    }
    bool operator<(const Line &tb) { return x < tb.x;}
} line[MAXN << 1];

class Seg_Tree { public:
    struct node {
        int l, r, val;
        ll len;
    } T[MAXN << 2];
    inline void push_up(int rt) {
        int l = T[rt].l, r = T[rt].r;
        if (T[rt].val) T[rt].len = b[r + 1] - b[l];
        else T[rt].len = T[rt << 1].len + T[rt << 1 | 1].len;
    }

    void build(int l, int r, int rt) {
        T[rt].l = l, T[rt].r = r;
        T[rt].val = 0;
        T[rt].len = 0;
        if (l == r) {
            T[rt<<1].val = T[rt<<1|1].val = T[rt<<1].len = T[rt<<1|1].len = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
    }
    void update(ll L, ll R, int c, int rt) {
        int l = T[rt].l, r = T[rt].r;
        if (b[r + 1] <= L || R <= b[l]) return;
        if (L <= b[l] && b[r + 1] <= R) {
            T[rt].val += c;
            push_up(rt);
            return;
        }
        update(L, R, c, rt << 1); update(L, R, c, rt << 1 | 1);
        push_up(rt);
    }
} tree;

int main() {
    int n; int kase = 0;
    while (~scanf("%d", &n) && n) {
        init();
        for (int i = 1; i <= n; i++) {
            ll x1, y1, x2, y2; scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            push(y1); push(y2);
            line[2 * i - 1] = Line(x1, y1, y2, 1);
            line[2 * i] = Line(x2, y1, y2, -1);
        }
        n <<= 1;
        sort(line + 1, line + 1 + n);
        build();
        tree.build(1, blen - 1, 1);
        ll res = 0;
        for (int i = 1; i < n; i++) {
            tree.update(line[i].y1, line[i].y2, line[i].mark, 1);
            res += tree.T[1].len * (line[i + 1].x - line[i].x);
        }
        printf("Test case #%d\n", ++kase);
        printf("Total explored area: %.2f\n", res);
        printf("\n");
    }
}
