class HJT { public:
    int ch[MAXN * 70][2], sum[MAXN * 70];
    int tot = 0;
    inline void push_up(int rt) {
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]];
    }
    int change(int rt, int pos, int val, int be, int en) {
        int nrt = ++tot;
        ch[nrt][0] = ch[nrt][1] = sum[nrt] = 0;
        if (be == en) {
            sum[nrt] = sum[rt] + val;
            return nrt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) {
            ch[nrt][0] = change(ch[rt][0], pos, val, be, mid);
            ch[nrt][1] = ch[rt][1];
        } else {
            ch[nrt][0] = ch[rt][0];
            ch[nrt][1] = change(ch[rt][1], pos, val, mid+1, en);
        }
        push_up(nrt);
        return nrt;
    }
    int query(int lrt, int rrt, int k, int be, int en) {
        if (be >= en) return be;
        int delta = sum[ch[rrt][0]] - sum[ch[lrt][0]];
        int mid = (be + en) >> 1;
        int ans = -1;
        if (delta > k) ans = query(ch[lrt][0], ch[rrt][0], k, be, mid);
        delta = sum[ch[rrt][1]] - sum[ch[lrt][1]];
        if (ans == -1 && delta > k) ans = query(ch[lrt][1], ch[rrt][1], k, mid + 1, en);
        return ans;
    }
} tree;
int ai[MAXN], root[MAXN];
int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &ai[i]);
    root[0] = 0;
    for (int i = 1; i <= n; i++) {
        root[i] = tree.change(root[i - 1], ai[i], 1, 1, n);
    }
    while (q--) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        int K = (r - l + 1) / k;
        int res = tree.query(root[l-1], root[r], K, 1, n);
        printf("%d\n", res);
    }
}