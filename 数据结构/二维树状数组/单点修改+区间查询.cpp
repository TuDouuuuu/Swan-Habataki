class BIT { public:
    ll val[MAXN][MAXN];
    int n, m;
    void init(int _n, int _m) {
        n = _n, m = _m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                val[i][j] = 0;
            }
        }
    }
    inline int lowbit(int x) { return x & (-x); }
    void add(int x, int y, ll v) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
                val[i][j] += v;
            }
        }
    }
    inline ll query(int x, int y) {
        ll ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i)) {
            for (int j = y; j >= 1; j -= lowbit(j)) {
                ans += val[i][j];
            }
        }
        return ans;
    }
    ll query(int x1, int y1, int x2, int y2) {  // x1 <= y1, x2 <= y2
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
} tree;