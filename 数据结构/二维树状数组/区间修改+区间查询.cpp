class BIT { public:
    ll val[MAXN][MAXN][4];
    int n, m;
    void init(int _n, int _m) {
        n = _n, m = _m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < 4; k++) {
                    val[i][j][k] = 0;
                }
            }
        }
    }
    inline int lowbit(int x) { return x & (-x); }
    inline void add(int x, int y, ll v) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
                val[i][j][0] += v, val[i][j][1] += v * x, val[i][j][2] += v * y, val[i][j][3] += v * x * y;
            }
        }
    }
    void change(int x1, int y1, int x2, int y2, ll v) { // x1 <= y1, x2 <= y2
        add(x1, y1, v);
        add(x2 + 1, y2 + 1, v);
        add(x2 + 1, y1, -v);
        add(x1, y2 + 1, -v);
    }
    inline ll query(int x, int y) {
        ll ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i)) {
            for (int j = y; j >= 1; j -= lowbit(j)) {
                ans += (ll) (x + 1) * (y + 1) * val[i][j][0] - (ll) (y + 1) * val[i][j][1] -
                       (ll) (x + 1) * val[i][j][2] + val[i][j][3];
            }
        }
        return ans;
    }
    ll sum(int x1, int y1, int x2, int y2) {  // x1 <= y1, x2 <= y2
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
} tree;