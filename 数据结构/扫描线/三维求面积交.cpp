namespace Discrete_y {
    int b[MAXN << 1], blen, btol;
    void insert(int x) { b[btol++] = x; }
    void init() {
        sort(b, b + btol);
        blen = unique(b, b + btol) - b;
    }
    int val2id(int x) { return lower_bound(b, b + blen, x) - b + 1; }
    int id2val(int x) { return b[x - 1]; }
}
using Discrete_y::id2val;
using Discrete_y::val2id;

namespace Discrete_z {
    int b[MAXN << 1], blen, btol;
    void insert(int x) { b[btol++] = x; }
    void init() {
        sort(b, b + btol);
        blen = unique(b, b + btol) - b;
    }
    int id2val(int x) { return b[x - 1]; }
}
class SEG { public:
    struct node {
        int l, r, val;
        int len[3];
    } T[MAXN << 3]; // 两倍的点*4

    inline void push_up(int rt) {   // 重点！
        if (T[rt].val >= 1) {
            T[rt].len[0] = id2val(T[rt].r + 1) - id2val(T[rt].l);
        } else if (T[rt].l != T[rt].r) {
            T[rt].len[0] = T[rt << 1].len[0] + T[rt << 1 | 1].len[0];
        } else T[rt].len[0] = 0;

        if (T[rt].val >= 2) {
            T[rt].len[1] = id2val(T[rt].r + 1) - id2val(T[rt].l);
        } else if (T[rt].l != T[rt].r) {
            if (T[rt].val == 1) {
                T[rt].len[1] = T[rt << 1].len[0] + T[rt << 1 | 1].len[0];
            } else {
                T[rt].len[1] = T[rt << 1].len[1] + T[rt << 1 | 1].len[1];
            }
        } else T[rt].len[1] = 0;

        if (T[rt].val >= 3) {
            T[rt].len[2] = id2val(T[rt].r + 1) - id2val(T[rt].l);
        } else if (T[rt].l != T[rt].r) {
            if (T[rt].val == 2) {
                T[rt].len[2] = T[rt << 1].len[0] + T[rt << 1 | 1].len[0];
            } else if (T[rt].val == 1) {
                T[rt].len[2] = T[rt << 1].len[1] + T[rt << 1 | 1].len[1];
            } else {
                T[rt].len[2] = T[rt << 1].len[2] + T[rt << 1 | 1].len[2];
            }
        } else T[rt].len[2] = 0;
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        T[rt].val = 0;
        if (l == r) {
            for (int i = 0; i < 3; i++) {
                T[rt].len[i] = 0;
            }
            push_up(rt);
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void update(int rt, int L, int R, int c) {
        if (L <= T[rt].l && T[rt].r <= R) {
            T[rt].val += c;
            push_up(rt);
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update(rt << 1, L, R, c);
        if (R > mid) update(rt << 1 | 1, L, R, c);
        push_up(rt);
    }
} tree;
struct Line {
    int x, y1, y2, z1, z2;
    int mark;
    Line(int _x = 0, int _y1 = 0, int _y2 = 0, int _z1 = 0, int _z2 = 0, int _mark = 0) {
        x = _x, y1 = _y1, y2 = _y2, z1 = _z1, z2 = _z2, mark = _mark;
    }
    bool operator<(const Line &tb) {
        return x < tb.x;
    }
} line[MAXN << 1];

int main() {
    int T;  scanf("%d", &T);
    while (T--) {
        int n;  scanf("%d", &n);
        Discrete_y::btol = 0;
        Discrete_z::btol = 0;
        for (int i = 1; i <= n; i++) {
            int x1, y1, z1, x2, y2, z2;
            scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
            Discrete_y::insert(y1), Discrete_y::insert(y2);
            Discrete_z::insert(z1), Discrete_z::insert(z2);
            line[2 * i - 1] = Line(x1, y1, y2, z1, z2, 1);
            line[2 * i] = Line(x2, y1, y2, z1, z2, -1);
        }
        Discrete_y::init();
        Discrete_z::init();
        n <<= 1;
        sort(line + 1, line + 1 + n);
        ll res = 0;
        for (int zz = 1; zz < Discrete_z::blen; zz++) {
            int z = Discrete_z::id2val(zz);
            tree.build(1, 1, Discrete_y::blen - 1);
            int lastx = 0;  // 注意一定要用lastx, 否则可能导致下一个z不在统计范围内
            ll ans = 0;
            for (int i = 1; i <= n; i++) {
                if (line[i].z1 <= z && z < line[i].z2) {
                    ans += (ll) tree.T[1].len[2] * (line[i].x - lastx), lastx = line[i].x;
                    tree.update(1, val2id(line[i].y1), val2id(line[i].y2)-1, line[i].mark);
                }
            }
            res += ans * (ll)(Discrete_z::id2val(zz + 1) - Discrete_z::id2val(zz));
        }
        printf("Case %d: %lld\n", kass++, res);
    }
}
