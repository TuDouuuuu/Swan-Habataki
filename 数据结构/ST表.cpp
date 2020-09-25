const int MAXN = 5e4 + 5;	// n
const int MAXL = 22;
int f[MAXN][MAXL], g[MAXN][MAXL], two[MAXN];
int h[MAXN];
void pre(int n) {
    for (int i = 1; i <= n; i++) {
        f[i][0] = h[i]; g[i][0] = h[i];	// 读入h
    }
    two[1] = 0; two[2] = 1;
    for (int i = 3; i < MAXN; i++) {
        two[i] = two[i / 2] + 1;
    }
    for (int j = 1; j <= MAXL; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    for (int j = 1; j <= MAXL; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            g[i][j] = min(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
    }
}

int get_max(int x, int y) {
    int s = two[y - x + 1];
    return max(f[x][s], f[y - (1 << s) + 1][s]);
}

int get_min(int x, int y) {
    int s = two[y - x + 1];
    return min(g[x][s], g[y - (1 << s) + 1][s]);
}
