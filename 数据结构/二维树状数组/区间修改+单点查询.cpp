class BIT { public:
    ll val[MAXN][MAXN];
    int n, m;
    void init(int _n, int _m);
    inline int lowbit(int x);
    inline void add(int x, int y, ll v) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
                val[i][j] += v;
            }
        }
    }
    ll query(int x, int y) {
        ll ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i)) {
            for (int j = y; j >= 1; j -= lowbit(j)) {
                ans += val[i][j];
            }
        }
        return ans;
    }
    void change(int x1, int y1, int x2, int y2, ll v) { // x1 <= y1, x2 <= y2
        add(x1, y1, v);
        add(x2 + 1, y2 + 1, v);
        add(x2 + 1, y1, -v);
        add(x1, y2 + 1, -v);
    }
} tree;
