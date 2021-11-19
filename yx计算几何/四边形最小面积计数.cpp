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
    ll area = LLONG_MAX; // llinf?  dog never use!
    ll cnt_uconv = 0, cnt_conv = 0;
    for (int i = 1; i <= n; i++) rk[i] = id[i] = i;
    for (int i = 1; i <= nd_tot; i++) {
        Point cen = nd[i].p;
        int a = nd[i].a, b = nd[i].b;
        if (rk[a] > rk[b]) swap(a, b);
        int na = rk[a] - 1, nb = n - rk[b];
        uconv -= (ll) na * (na - 1) / 2;
        uconv -= (ll) nb * (nb - 1) / 2;
        if (1 <= rk[a] - 1 && rk[b] + 1 <= n) {
            ll left = abs(cen ^ (p[a] - p[id[rk[a] - 1]])), right = abs(cen ^ (p[b] - p[id[rk[b] + 1]]));
            ll cur_area = left + right;
            if (cur_area < area) area = cur_area, cnt_uconv = cnt_conv = 0;
            if (cur_area == area) {
                vi l, r;
                l.pb(id[rk[a] - 1]), r.pb(id[rk[b] + 1]);
                for (int j = rk[a] - 2; j >= 1; j--) {
                    if (abs(cen ^ (p[id[j]] - p[a])) == left) l.pb(id[j]);
                }
                for (int j = rk[b] + 2; j <= n; j++) {
                    if (abs(cen ^ (p[id[j]] - p[b])) == right) r.pb(id[j]);
                }
                for (auto &ea:l) {
                    for (auto &eb: r) {
                        vector<Point> tmp{p[ea], p[a], p[eb], p[b]};
                        int s = signbit((tmp[1] - tmp[0]) ^ (tmp[2] - tmp[0]));
                        bool f = 0;
                        for (int j = 1; j < 4; j++) {
                            if (s != signbit((tmp[(j + 1) % 4] - tmp[j]) ^ (tmp[(j + 2) % 4] - tmp[j]))) {
                                f = 1; break;
                            }
                        }
                        if (f) cnt_uconv++;
                        else cnt_conv++;
                    }
                }
            }
        }
        swap(rk[a], rk[b]); swap(id[rk[a]], id[rk[b]]);
    }
    ll conv = (ll) n * (n - 1) * (n - 2) * (n - 3) / 24 - uconv;
    cnt_conv /= 2;
    ll res = 4ll * cnt_conv + 3ll * cnt_uconv + 2ll * (conv - cnt_conv) + 1ll * (uconv * 3 - cnt_uconv);
    printf("%lld\n", res);
}