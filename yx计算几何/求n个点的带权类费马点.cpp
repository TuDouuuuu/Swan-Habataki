const int MAXN = 10005;
const double eps = 1e-8;
struct node {
    double x, y, weight;
} nd[MAXN];
int n;
node solve() {
    double step = 1000;
    node ans;
    while (step > eps) {
        double x = 0, y = 0;
        for (int i = 1; i <= n; i++) {
            double tmp = sqrt((ans.x - nd[i].x) * (ans.x - nd[i].x) + (ans.y - nd[i].y) * (ans.y - nd[i].y));
            if (fabs(tmp) < eps) continue;
            x += nd[i].weight / tmp * (nd[i].x - ans.x);
            y += nd[i].weight / tmp * (nd[i].y - ans.y);
        }
        double tmp = sqrt(x * x + y * y);
        if (fabs(tmp) >= eps) {
            ans.x += step / tmp * x;
            ans.y += step / tmp * y;
        }
        step *= 0.98;
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &nd[i].x, &nd[i].y, &nd[i].weight);
    }
    node res = solve();
    printf("%.3lf %.3lf", res.x, res.y);

}