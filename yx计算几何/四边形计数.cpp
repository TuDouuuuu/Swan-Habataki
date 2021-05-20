struct Point {
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    Point operator-(const Point &tb) const {
        return Point(x - tb.x, y - tb.y);
    }
    ll operator^(const Point &tb) const {
        return x * tb.y - y * tb.x;
    }
} p[MAXN];

struct node {
    Point p; int a, b;
    node() {}
    node(Point _p, int _a, int _b) : p(_p), a(_a), b(_b) {}
} nd[MAXN * MAXN];

int rk[MAXN], id[MAXN];
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld%lld", &p[i].x, &p[i].y);
        sort(p + 1, p + 1 + n, [&](const Point &ta, const Point &tb) {
            if (ta.x != tb.x) return ta.x < tb.x;
            else return ta.y < tb.y;
        });
        int nd_tot = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) nd[++nd_tot] = node(p[i] - p[j], i, j);
        }
        sort(nd + 1, nd + 1 + nd_tot, [&](const node &ta, const node &tb) {
            ll tmp = ta.p ^tb.p;
            return tmp < 0;
        });
        ll uconv = (ll) n * (n - 1) * (n - 2) * (n - 3) / 6;
        for (int i = 1; i <= n; i++) rk[i] = id[i] = i;
        for (int i = 1; i <= nd_tot; i++) {
            int a = nd[i].a, b = nd[i].b;
            if (rk[a] > rk[b]) swap(a, b);
            int na = rk[a] - 1, nb = n - rk[b];
            uconv -= (ll) na * (na - 1) / 2;
            uconv -= (ll) nb * (nb - 1) / 2;
            swap(rk[a], rk[b]);
            swap(id[rk[a]], id[rk[b]]);
        }
        ll conv = (ll) n * (n - 1) * (n - 2) * (n - 3) / 24 - uconv;
        printf("%lld\n", conv);
    }

}