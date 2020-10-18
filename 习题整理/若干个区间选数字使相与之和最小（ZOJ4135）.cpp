/*
    input               output
    3                   6
    [0,8],[2,6],[3,9]
    3                   1
    [0,7],[0,3],[4,5]
*/
int L[MAXN], R[MAXN];
int main() {
    int n;  scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &L[i], &R[i]);
    int res = 0;
    for (int i = 30; i >= 0; i--) {
        int tmp = (1 << i);
        int flag = 1;
        for (int j = 1; j <= n; j++) {
            if (tmp > R[j]) {
                flag = 0;   break;
            }
        }
        if (flag) { // can provide 1
            res += tmp;
            for (int j = 1; j <= n; j++) {
                L[j] = max(L[j], tmp) - tmp;
                R[j] = R[j] - tmp;
            }
        } else {
            for (int j = 1; j <= n; j++) {
                if (L[j] >= tmp && R[j] >= tmp) {
                    L[j] -= tmp, R[j] -= tmp;
                } else if (L[j] < tmp && R[j] >= tmp) {
                    R[j] = tmp - 1;
                }
            }
        }
    }
    printf("%d\n", res);
}