class DS {  public:
    // HJT begin
    int ch[MAXN * 150][2], tot = 0;
    ll sum[MAXN * 150];

    inline void push_up(int rt) {
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]];
    }

    int update(int rt, int pos, int val, int be, int en) {
        int nrt = rt;
        if (!rt) {
            nrt = ++tot;
            ch[nrt][0] = ch[nrt][1] = sum[nrt] = 0;
        }
        if (be == en) {
            sum[nrt] += (ll) be * val;
            return nrt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) {
            ch[nrt][0] = update(ch[rt][0], pos, val, be, mid);
            ch[nrt][1] = ch[rt][1];
        } else {
            ch[nrt][0] = ch[rt][0];
            ch[nrt][1] = update(ch[rt][1], pos, val, mid + 1, en);
        }
        push_up(nrt);
        return nrt;
    }

    // HJT end
    int n, c_len, root[MAXN];

    void init(int _n, int _c_len) {
        c_len = _c_len, n = _n;
        for (int i = 1; i <= c_len; i++) root[i] = i;
        tot = c_len;
    }

    inline int lowbit(int x) { return x & (-x); }
    void insert(int pos, int pos_val, int val) {
        for (int i = pos; i <= n; i += lowbit(i)) root[i] = update(root[i], pos_val, val, 1, c_len);
    }
    int t1[MAXN], t2[MAXN], n1, n2;
    inline ll SUM(int R, int be, int en) {
        if (be == en) {
            ll ans = 0;
            for (int i = 1; i <= n1; i++) ans -= sum[t1[i]];
            for (int i = 1; i <= n2; i++) ans += sum[t2[i]];
            return ans;
        }
        int mid = (be + en) >> 1;
        ll ans = 0;
        if (mid >= R) {
            for (int i = 1; i <= n1; i++) t1[i] = ch[t1[i]][0];
            for (int i = 1; i <= n2; i++) t2[i] = ch[t2[i]][0];
            return SUM(R, be, mid);
        } else {
            for (int i = 1; i <= n1; i++) ans -= sum[ch[t1[i]][0]];
            for (int i = 1; i <= n2; i++) ans += sum[ch[t2[i]][0]];
            for (int i = 1; i <= n1; i++) t1[i] = ch[t1[i]][1];
            for (int i = 1; i <= n2; i++) t2[i] = ch[t2[i]][1];
            return ans + SUM(R, mid + 1, en);
        }
    }
    ll query(int l, int r, int x) {
        n1 = n2 = 0;
        for (int i = l - 1; i >= 1; i -= lowbit(i)) t1[++n1] = root[i];
        for (int i = r; i >= 1; i -= lowbit(i)) t2[++n2] = root[i];
        return SUM(x, 1, c_len);
    }
} tree;

int a[MAXN];
int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    tree.init(n, 2e5);
    for (int i = 1; i <= n; i++) tree.insert(i, a[i], 1);
    while (q--) {
        int opt; scanf("%d", &opt);
        if (opt == 1) {
            int x, y; scanf("%d%d", &x, &y);
            tree.insert(x, a[x], -1);
            a[x] = y;
            tree.insert(x, a[x], 1);
        } else {
            int L, R; scanf("%d%d", &L, &R);
            ll now = 1, sum = 0;
            while (1) {
                int t = min(now, (ll) 2e5);
                ll tmp = tree.query(L, R, t);
                if (tmp == sum) {
                    printf("%lld\n", now);
                    break;
                } else {
                    sum = tmp, now = sum + 1;
                }
            }
        }
    }
}