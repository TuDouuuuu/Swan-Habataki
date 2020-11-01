char ss[N];
int h[N], sta[N], top, ans[N][N];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int u = 1; u <= n; u++) {
        scanf("%s", ss + 1);
        top = 0;
        for (int i = 1; i <= m + 1; i++) {
            h[i] = ss[i] == '1' ? h[i] + 1 : 0;
            while (top > 0 && h[sta[top]] > h[i]) {
                ans[max(h[sta[top - 1]], h[i]) + 1][i - sta[top - 1] - 1]++;
                ans[h[sta[top]] + 1][i - sta[top - 1] - 1]--;
                top--;
            }
            while (top > 0 && h[sta[top]] == h[i]) top--;
            sta[++top] = i;
        }
    }
    for (int u = 1; u <= n; u++)
        for (int i = 1; i <= m; i++)
            ans[u][i] = ans[u][i] + ans[u - 1][i];
    for (int u = 1; u <= n; u++) {
        int sum = 0, lalal = 0;
        for (int i = 2; i <= m; i++) {
            lalal = lalal + ans[u][i];
            sum = sum + ans[u][i] * i;
        }
        for (int i = 1; i <= m; i++) {
            ans[u][i] = ans[u][i] + sum;
            sum = sum - lalal - ans[u][i + 1];
            lalal = lalal - ans[u][i + 1];
        }
        // 原题解疑惑代码
        // for (int i=1;i<=m;i++) {
        //     for (int j=i+1;j<=m;j++)
        //         ans[u][i]=ans[u][i]+ans[u][j]*(j-i+1);
        // }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", ans[i][j]);   // i * j的全1矩阵个数
        }
        printf("\n");
    }
    printf("%lld\n", res);
    return 0;
}
