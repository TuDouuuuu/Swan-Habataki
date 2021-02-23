const double eps = 1e-8;
const double start_T = 10000; // 初始温度记得设足够高
struct point3d {
    double x, y, z;
} data[150];
int n;
double dis(point3d a, point3d b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
double solve() {
    double step = start_T, ans = 1e30, mt;
    point3d z;
    z.x = z.y = z.z = 0;
    int s = 0;
    while (step > eps) {
        for (int i = 0; i < n; i++)
            if (dis(z, data[s]) < dis(z, data[i])) s = i;
        mt = dis(z, data[s]);
        ans = min(ans, mt);
        z.x += (data[s].x - z.x) / mt * step;
        z.y += (data[s].y - z.y) / mt * step;
        z.z += (data[s].z - z.z) / mt * step;
        step *= 0.98;
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf", &data[i].x, &data[i].y, &data[i].z);
    }
    double ans = solve();
    printf("%.15f\n", ans);
}