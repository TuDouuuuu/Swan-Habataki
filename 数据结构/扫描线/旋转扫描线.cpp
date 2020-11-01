const double eps = 1e-8;
SEG tree; // 矩阵求和最值（POJ-2482）中的SEG
struct point {
    int x, y;
    bool operator < (const point& tb) const {return y < tb.y;}
}p[SIZE<<1];
int main() {
    int n, d; scanf("%d%d", &n, &d);
    double _alpha; scanf("%lf", &_alpha);
    int alpha = (int)(_alpha * 100.0 + eps);
    for (int i = 0; i < n; i++) {
        int r; double w;
        scanf("%d%lf", &r, &w);
        p[i].x = r; p[i].y = (int)(w * 100.0 + eps);
    }
    std::sort(p, p+n);
    for (int i = 0; i < n; i++) {
        p[i+n].x = p[i].x; p[i+n].y = p[i].y + 36000;
    }
    n *= 2;
    int l = 0, r = 0;
    int res = 0;
    tree.build(0, 100000, 1);
    while (r < n) {
        int cnt = 0;
        for (int i = r; i < n; i++) {
            if (p[i].y == p[r].y) {
                tree.update(std::max(1, p[i].x - d), p[i].x, 1, 1);
                cnt++;
            }
            else break;
        }
        while (l < r) {
            if (p[r].y - p[l].y > alpha) {
                tree.update(std::max(1, p[l].x - d), p[l].x, -1, 1);
                l++;
            }
            else break;
        }
        r += cnt;
        res = std::max(res, tree.T[1].val);
    }
    printf("%d\n", res);
}