struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator-(const Point &tb) { return Point(x - tb.x, y - tb.y); }
    double dis(const Point &tb) {
        return sqrt((x - tb.x) * (x - tb.x) + (y - tb.y) * (y - tb.y));
    }
};
double cross(const Point &ta, const Point &tb) {
    return ta.x * tb.y - ta.y * tb.x;
}
namespace Convex {
    vector<Point> GetConvexHull(const vector<Point> &P) {
        vector<Point> ans, p(P);
        int n = SZ(p), t = -1;
        sort(p.begin(), p.end(), [&](const Point &ta, const Point &tb) {
            if (ta.x != tb.x) return ta.x < tb.x;
            else return ta.y < tb.y;
        }), ans.assign(n * 2, Point(0, 0));
        auto ins = [&](int pre, const Point &u) {
            while (t > pre && cross(ans[t - 1] - u, ans[t] - u) >= 0) t--;
            ans[++t] = u;
        };
        for (auto u:p) ins(0, u);
        for (int i = n - 2, pre = t; i >= 0; i--) ins(pre, p[i]);
        ans.resize(t);
        return ans;
    }
}
vector<Point> vec;
int main() {
    int n; scanf("%d", &n);
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &vec[i].x, &vec[i].y);
    }
    vector<Point> v = Convex::GetConvexHull(vec);
    double res = 0.0;
    for (int i = 0; i < SZ(v); i++) {
        if (i == 0) res += v[i].dis(v[SZ(v) - 1]);
        else res += v[i].dis(v[i - 1]);
    }
    printf("%.2lf\n", res);
}