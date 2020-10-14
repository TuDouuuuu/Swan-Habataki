struct Edge {
    int u, v;
} e[MAXM];

class LCT { public:
    int val[MAXN+MAXM], minn_id[MAXN+MAXM];
    int stk_top, stk[MAXN+MAXM];
    int fa[MAXN+MAXM], ch[MAXN+MAXM][2];
    bool rev[MAXN+MAXM];

    inline bool isroot(int x) {
        return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
    }
    inline void push_up(int x) {
        int l = ch[x][0], r = ch[x][1];
        minn_id[x] = x;
        if (val[minn_id[l]] < val[minn_id[x]]) minn_id[x] = minn_id[l];
        if (val[minn_id[r]] < val[minn_id[x]]) minn_id[x] = minn_id[r];
    }
    inline void split(int x, int y) {
        makeroot(x);
        access(y);
        splay(y);
    }

    int query(int x, int y) {
        split(x, y);
        return minn_id[y];
    }
} lct;

class HJT { public:
    int ch[MAXM * 70][2], sum[MAXM * 70];
    int tot;
    inline void push_up(int rt) {
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]];
    }
    int query(int lrt, int rrt, int L, int R, int be, int en) {
        if (L <= be && en <= R) return sum[rrt] - sum[lrt];
        int mid = (be + en) >> 1;
        int ans = 0;
        if (L <= mid) ans += query(ch[lrt][0], ch[rrt][0], L, R, be, mid);
        if (R > mid) ans += query(ch[lrt][1], ch[rrt][1], L, R, mid+1, en);
        return ans;
    }
} tree;

int del[MAXM], root[MAXM];
int main() {
    int n, m, q, type;
    scanf("%d%d%d%d", &n, &m, &q, &type);   // type标识在线参数

    lct.val[0] = inf;  // init
    for (int i = 1; i <= n; i++) lct.minn_id[i] = i, lct.val[i] = inf;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &e[i].u, &e[i].v);
    }

    // pre begin
    int tot = n;
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        if (u == v) {
            del[i] = i; continue;
        }
        if (lct.find(u) == lct.find(v)) {
            int tmp = lct.query(u, v), x = lct.val[tmp];
            del[i] = x;
            lct.cut(e[x].u, tmp), lct.cut(e[x].v, tmp);
        }
        tot++;
        lct.minn_id[tot] = tot, lct.val[tot] = i;
        lct.link(u, tot), lct.link(v, tot);
    }
    root[0] = 0;
    for (int i = 1; i <= m; i++) {
        del[i]++; // [0, m] -> [1, m+1]
        root[i] = tree.update(root[i - 1], del[i], 1, 1, m + 1);
    }
    // pre end
    int lastans = 0;
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        lastans = n - tree.query(root[l-1], root[r], 1, l, 1, m+1);
        printf("%d\n", lastans);
    }
}