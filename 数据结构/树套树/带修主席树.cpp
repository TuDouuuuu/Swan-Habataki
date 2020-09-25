/*
  input       output
  5 3
  3 2 1 4 7
  Q 1 4 3     3
  C 2 6
  Q 2 5 3     6
*/
class BIT { public:
    // HJT begin
    int ch[MAXN * 400][2], sum[MAXN * 400], tot = 0;
    inline void push_up(int rt) {
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]];
    }
    int update(int rt, int pos, int val, int be, int en) {
        int nrt = ++tot;
        ch[nrt][0] = ch[nrt][1] = sum[nrt] = 0;
        if (be == en) {
            sum[nrt] = sum[rt] + val;
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
    inline int Kth(int be, int en, int k) {
        if (be >= en) return be;
        int mid = (be + en) >> 1, delta = 0;

        for (int i = 1; i <= n1; i++) delta -= sum[ch[t1[i]][0]];
        for (int i = 1; i <= n2; i++) delta += sum[ch[t2[i]][0]];
        if (delta >= k) {
            for (int i = 1; i <= n1; i++) t1[i] = ch[t1[i]][0];
            for (int i = 1; i <= n2; i++) t2[i] = ch[t2[i]][0];
            return Kth(be, mid, k);
        } else {
            for (int i = 1; i <= n1; i++) t1[i] = ch[t1[i]][1];
            for (int i = 1; i <= n2; i++) t2[i] = ch[t2[i]][1];
            return Kth(mid + 1, en, k - delta);
        }
    }
    int query(int l, int r, int k) {
        n1 = n2 = 0;
        for (int i = l - 1; i >= 1; i -= lowbit(i)) t1[++n1] = root[i];
        for (int i = r; i >= 1; i -= lowbit(i)) t2[++n2] = root[i];
        return Kth(1, c_len, k);
    }
} tree;
int ai[MAXN];
int opt[MAXN], l[MAXN], r[MAXN], k[MAXN], x[MAXN], y[MAXN];
int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> ai[i];
    for (int i = 1; i <= n; i++) Discrete::insert(ai[i]);
    for (int i = 1; i <= m; i++) {
        char op; cin >> op;
        if (op == 'Q') {
            opt[i] = 1; cin >> l[i] >> r[i] >> k[i];
        } else {
            opt[i] = 2; cin >> x[i] >> y[i];
            Discrete::insert(y[i]);
        }
    }
    Discrete::init();
    for (int i = 1; i <= n; i++) ai[i] = Discrete::val2id(ai[i]);
    for (int i = 1; i <= m; i++) {
        if (opt[i] == 2) y[i] = Discrete::val2id(y[i]);
    }
    tree.init(n, Discrete::blen);

    for (int i = 1; i <= n; i++) tree.insert(i, ai[i], 1);
    for (int i = 1; i <= m; i++) {
        if (opt[i] == 1) {  // 表示查询下标在区间[l,r]中的第k小的数
            cout << Discrete::id2val(tree.query(l[i], r[i], k[i])) << '\n';
        } else {  // 表示将a[x]改为y
            tree.insert(x[i], ai[x[i]], -1);
            ai[x[i]] = y[i];
            tree.insert(x[i], ai[x[i]], 1);
        }
    }
}
