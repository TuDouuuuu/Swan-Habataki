/*  2
    4           0.5000000
    1 3 3 4
    4           1.0000000
    2 3 3 4                     */    
int a[MAXN];
ll cnt[MAXN << 1], pre[MAXN << 1];
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, P = 0; scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            P = max(P, a[i]);
        }
        sort(a + 1, a + 1 + n);

        L = 0, limit = 1;
        while (limit <= (P << 1)) limit <<= 1, L++;
        for (int i = 0; i < limit; i++)
            R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

        for (int i = 0; i < limit; i++) A[i].x = A[i].y = B[i].x = B[i].y = 0;
        for (int i = 0; i <= (P << 1); i++) cnt[i] = 0;

        for (int i = 1; i <= n; i++) {
            A[a[i]].x++, B[a[i]].x++;
        }

        FFT(A, 1), FFT(B, 1);
        for (int i = 0; i < limit; i++) A[i] = A[i] * B[i];
        FFT(A, -1);
        for (int i = 0; i <= (P << 1); i++) {
            cnt[i] = (ll) (A[i].x / limit + 0.5);
        }

        for (int i = 1; i <= n; i++) cnt[a[i] * 2]--;
        for (int i = 0; i <= (P << 1); i++) cnt[i] /= 2;

        int len = (P << 1);
        for (int i = 0; i <= len; i++) pre[i] = pre[i - 1] + cnt[i];

        ll res = 0;
        for (int i = 1; i <= n; i++) {
            res += pre[len] - pre[a[i]];
            res -= (ll) (i - 1) * (n - i);
            res -= (ll) (n - 1);
            res -= (ll) (n - i - 1) * (n - i) / 2ll;
        }

        ll fm = (ll) n * (n - 1) * (n - 2) / 6ll;
        printf("%.7lf\n", (double) res / fm);
    }
}