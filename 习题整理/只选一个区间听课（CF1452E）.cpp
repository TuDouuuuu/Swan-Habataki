/*  [input]     [output]
    5 4 5       8
    1 2
    2 3
    3 4
    4 5
*/
struct node {
    int l, r;
} nd[MAXN];
int sum[MAXN];
int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) scanf("%d%d", &nd[i].l, &nd[i].r);
    sort(nd + 1, nd + 1 + m, [&](const node &ta, const node &tb) {
        return ta.l + ta.r < tb.l + tb.r;
    });
    for (int i = 1; i <= n - k + 1; i++) {
        int cur = 0;
        for (int j = m; j >= 1; j--) {
            cur += max(0, min(i + k, nd[j].r+1) - max(i, nd[j].l));
            sum[j] = max(sum[j], cur);
        }
    }
    int res = sum[0];
    for (int i = 1; i <= n - k + 1; i++) {
        int cur = 0;
        for (int j = 1; j <= m; j++) {
            cur += max(0, min(i + k, nd[j].r+1) - max(i, nd[j].l));
            res = max(res, cur + sum[j + 1]);
        }
    }
    printf("%d\n", res);
}