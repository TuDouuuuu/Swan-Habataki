/*
  input       output
  6 
  1 8 5 10 8  
  1 6 7 2 6   
  0 2         2
  0 11        0
  1 4 7 6 7 
  0 5         3
*/
class LC {  public:
    struct LINE {
        double k, b;
    } p[MAXN];
    int sum[MAXN << 2];
    int cnt = 0;
    void init() { cnt = 0; }
    void add_seg(int x0, int y0, int x1, int y1) {
        cnt++;
        if (x0 == x1) p[cnt].k = 0, p[cnt].b = max(y0, y1);
        else p[cnt].k = 1.0 * (y1 - y0) / (x1 - x0), p[cnt].b = y0 - p[cnt].k * x0;
    }
    void update(int rt, int L, int R, int be, int en, int u) {
        int mid = (be + en) >> 1;
        if (L <= be && en <= R) {
            int v = sum[rt];
            double ansu = p[u].b + p[u].k * mid, ansv = p[v].b + p[v].k * mid;
            if (be == en) {
                if (ansu > ansv) sum[rt] = u;
                return;
            }
            if (p[v].k < p[u].k) {
                if (ansu > ansv) {
                    sum[rt] = u;
                    update(rt << 1, L, R, be, mid, v);
                } else update(rt << 1 | 1, L, R, mid + 1, en, u);
            } else if (p[v].k > p[u].k) {
                if (ansu > ansv) {
                    sum[rt] = u;
                    update(rt << 1 | 1, L, R, mid + 1, en, v);
                } else update(rt << 1, L, R, be, mid, u);
            } else {
                if (p[u].b > p[v].b) sum[rt] = u;
            }
            return;
        }
        if (L <= mid) update(rt << 1, L, R, be, mid, u);
        if (R > mid) update(rt << 1 | 1, L, R, mid + 1, en, u);
    }
    typedef pair<double, int> pdi;
    pdi pmax(pdi x, pdi y) {
        if (x.first < y.first) return y;
        else if (x.first > y.first) return x;
        else return x.second < y.second ? x : y;
    }
    pdi query(int rt, int d, int be, int en) {
        if (be == en) {
            int v = sum[rt];
            double ans = (p[v].b + p[v].k * d);
            return {ans, sum[rt]};
        }
        int mid = (be + en) >> 1;
        int v = sum[rt];
        double res = (p[v].b + p[v].k * d);
        pdi ans = {res, sum[rt]};
        if (d <= mid) return pmax(ans, query(rt << 1, d, be, mid));
        else return pmax(ans, query(rt << 1 | 1, d, mid + 1, en));
    }
} tree;
int main() {
    int n; scanf("%d", &n);
    while (n--) {
        int opt; scanf("%d", &opt);
        if (opt == 1) {
            int x0, y0, x1, y1; scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            if (x0 > x1) swap(x0, x1), swap(y0, y1);  // notice x0, x1
            tree.add_seg(x0, y0, x1, y1);
            tree.update(1, x0, x1, 1, MOD1, tree.cnt);
        } else {
            int x; scanf("%d", &x);
            printf("%d\n", tree.query(1, x, 1, MOD1).second);
        }
    }
}

