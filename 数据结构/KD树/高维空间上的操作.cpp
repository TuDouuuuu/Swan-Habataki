/*
    intput      output
    4
    1 2 3 3
    2 1 1 3 3   3
    1 1 1 1
    2 1 1 0 7   5
    3
*/
const int MAXN = 2e5 + 5;   // 操作次数
class KD {
public:
    struct node {
        int x, y, v;
    } T[MAXN];
    int ch[MAXN][2], L[MAXN], R[MAXN], D[MAXN], U[MAXN];
    int siz[MAXN], sum[MAXN], g[MAXN], d[MAXN];

    inline void push_up(int rt) {
        siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + 1;
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]] + T[rt].v;
        L[rt] = R[rt] = T[rt].x;
        U[rt] = D[rt] = T[rt].y;
        if (ch[rt][0]) {
            L[rt] = min(L[rt], L[ch[rt][0]]), R[rt] = max(R[rt], R[ch[rt][0]]),
            D[rt] = min(D[rt], D[ch[rt][0]]), U[rt] = max(U[rt], U[ch[rt][0]]);
        }
        if (ch[rt][1]) {
            L[rt] = min(L[rt], L[ch[rt][1]]), R[rt] = max(R[rt], R[ch[rt][1]]),
            D[rt] = min(D[rt], D[ch[rt][1]]), U[rt] = max(U[rt], U[ch[rt][1]]);
        }
    }

    int build(int l, int r) {
        if (l > r) return 0;
        int mid = (l + r) >> 1;
        double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
        for (int i = l; i <= r; i++) av1 += T[g[i]].x, av2 += T[g[i]].y;
        av1 /= (r - l + 1);
        av2 /= (r - l + 1);
        for (int i = l; i <= r; i++) {
            va1 += (av1 - T[g[i]].x) * (av1 - T[g[i]].x),
                    va2 += (av2 - T[g[i]].y) * (av2 - T[g[i]].y);
        }
        if (va1 > va2)
            nth_element(g + l, g + mid, g + r + 1, [&](int ta, int tb) { return T[ta].x < T[tb].x; }), d[g[mid]] = 1;
        else nth_element(g + l, g + mid, g + r + 1, [&](int ta, int tb) { return T[ta].y < T[tb].y; }), d[g[mid]] = 2;
        ch[g[mid]][0] = build(l, mid - 1);
        ch[g[mid]][1] = build(mid + 1, r);
        push_up(g[mid]);
        return g[mid];
    }

    const double bad_para = 0.725;
    int tot;
    bool bad(int rt) {
        return bad_para * siz[rt] <= (double) max(siz[ch[rt][0]], siz[ch[rt][1]]);
    }
    void dfs(int rt) {
        if (!rt) return;
        dfs(ch[rt][0]);
        g[++tot] = rt;
        dfs(ch[rt][1]);
    }
    void rebuild(int &rt) {
        tot = 0;
        dfs(rt);
        rt = build(1, tot);
    }
    void insert(int &rt, int v) {
        if (!rt) {
            rt = v;
            push_up(rt);
            return;
        }
        if (d[rt] == 1) {
            if (T[v].x <= T[rt].x) insert(ch[rt][0], v);
            else insert(ch[rt][1], v);
        } else {
            if (T[v].y <= T[rt].y) insert(ch[rt][0], v);
            else insert(ch[rt][1], v);
        }
        push_up(rt);
        if (bad(rt)) rebuild(rt);
    }
    int query(int rt, int xl, int xr, int yl, int yr) {
        if (!rt ||  xr < L[rt] || xl > R[rt] || yr < D[rt] || yl > U[rt]) return 0;
        if (xl <= L[rt] && R[rt] <= xr &&  yl <= D[rt] && U[rt] <= yr) return sum[rt];
        int ans = 0;
        if (xl <= T[rt].x && T[rt].x <= xr && yl <= T[rt].y && T[rt].y <= yr) ans += T[rt].v;
        return query(ch[rt][0], xl, xr, yl, yr) + query(ch[rt][1], xl, xr, yl, yr) + ans;
    }

} tree;

int main() {
    int N, opt;
    scanf("%d", &N);
    int tot = 0, lastans = 0, root = 0;
    while (~scanf("%d", &opt)) {
        if (opt == 1) {
            tot++;
            scanf("%d%d%d", &tree.T[tot].x, &tree.T[tot].y, &tree.T[tot].v);
            tree.T[tot].x ^= lastans, tree.T[tot].y ^= lastans, tree.T[tot].v ^= lastans;
            tree.insert(root, tot);
        } else if (opt == 2) {
            int xl, yl, xr, yr;
            scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
            xl ^= lastans, yl ^= lastans, xr ^= lastans, yr ^= lastans;
            lastans = tree.query(root, xl, xr, yl, yr);
            printf("%d\n", lastans);
        } else break;
    }
}