const int MAXN = 2e5 + 5;   // 点的个数
class KD {
public:
    struct node {
        double x, y;
    } T[MAXN];
    int ch[MAXN][2];
    double L[MAXN], R[MAXN], D[MAXN], U[MAXN];
    inline void push_up(int rt) {
        L[rt] = R[rt] = T[rt].x;
        D[rt] = U[rt] = T[rt].y;
        if (ch[rt][0]) {
            L[rt] = min(L[rt], L[ch[rt][0]]), R[rt] = max(R[rt], R[ch[rt][0]]),
            D[rt] = min(D[rt], D[ch[rt][0]]), U[rt] = max(U[rt], U[ch[rt][0]]);
        }
        if (ch[rt][1]) {
            L[rt] = min(L[rt], L[ch[rt][1]]), R[rt] = max(R[rt], R[ch[rt][1]]),
            D[rt] = min(D[rt], D[ch[rt][1]]), U[rt] = max(U[rt], U[ch[rt][1]]);
        }
    }

    int d[MAXN];
    int build(int l, int r) {
        if (l > r) return 0;
        int mid = (l + r) >> 1;
        double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
        for (int i = l; i <= r; i++) av1 += T[i].x, av2 += T[i].y;
        av1 /= (r - l + 1);
        av2 /= (r - l + 1);
        for (int i = l; i <= r; i++) va1 += (av1 - T[i].x) * (av1 - T[i].x), va2 += (av2 - T[i].y) * (av2 - T[i].y);
        if (va1 > va2)
            d[mid] = 1, nth_element(T + l, T + mid, T + r + 1,
                                    [&](const node &ta, const node &tb) { return ta.x < tb.x; });
        else
            d[mid] = 2, nth_element(T + l, T + mid, T + r + 1,
                                    [&](const node &ta, const node &tb) { return ta.y < tb.y; });
        ch[mid][0] = build(l, mid - 1);
        ch[mid][1] = build(mid + 1, r);
        push_up(mid);
        return mid;
    }

    double f(int a, int b) {
        double ans = 0;
        if (L[b] > T[a].x) ans += (L[b] - T[a].x) * (L[b] - T[a].x);
        if (R[b] < T[a].x) ans += (T[a].x - R[b]) * (T[a].x - R[b]);
        if (D[b] > T[a].y) ans += (D[b] - T[a].y) * (D[b] - T[a].y);
        if (U[b] < T[a].y) ans += (T[a].y - U[b]) * (T[a].y - U[b]);
        return ans;
    }
    double ans;
    double dist(int a, int b) {
        return (T[a].x - T[b].x) * (T[a].x - T[b].x) + (T[a].y - T[b].y) * (T[a].y - T[b].y);
    }
    void query(int l, int r, int rt) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        if (mid != rt) ans = min(ans, dist(rt, mid));
        if (l == r) return ;
        double distl = f(rt, ch[mid][0]), distr = f(rt, ch[mid][1]);
        if (distl < ans && distr < ans) {
            if (distl < distr) {
                query(l, mid - 1, rt);
                if (distr < ans) query(mid + 1, r, rt);
            } else {
                query(mid + 1, r, rt);
                if (distl < ans) query(l, mid - 1, rt);
            }
        } else {
            if (distl < ans) query(l, mid - 1, rt);
            if (distr < ans) query(mid + 1, r, rt);
        }
    }
    void init() { ans = inf_ll; }
    double get_res() { return ans; }
} tree;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf%lf", &tree.T[i].x, &tree.T[i].y);
    tree.init();
    tree.build(1, n);
    for (int i = 1; i <= n; i++) {
        tree.query(1, n, i);
    }
    printf("%.4lf\n", sqrt(tree.get_res()));
}