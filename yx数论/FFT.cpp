const int MAXN = 200020;
namespace FFT {
    const int mod = 998244353;
    struct cp {
        double x, y;
        cp(double _r = 0, double _i = 0) : x(_r), y(_i) {}
        cp operator+(const cp &tb) { return cp(x + tb.x, y + tb.y); }
        cp operator-(const cp &tb) { return cp(x - tb.x, y - tb.y); }
        cp operator*(const cp &tb) { return cp(x * tb.x - y * tb.y, y * tb.x + x * tb.y); }
    } A[MAXN], B[MAXN]; // 三倍空间
    const double pi = acos(-1.0);
    int L, R[MAXN]; int limit = 1;
    void FFT(cp a[], int type) {
        for (int i = 0; i < limit; i++)
            if (i < R[i]) swap(a[i], a[R[i]]);
        for (int j = 1; j < limit; j <<= 1) {
            cp Wn(cos(pi / j), type * sin(pi / j));
            for (int k = 0; k < limit; k += (j << 1)) {
                cp w(1, 0);
                for (int i = 0; i < j; i++, w = w * Wn) {
                    cp x = a[i + k], y = w * a[j + k + i];
                    a[i + k] = x + y; a[j + k + i] = x - y;
                }
            }
        }
    }
};
using FFT::L; using FFT::R; using FFT::limit;
char A[MAXN], B[MAXN]; int sum[MAXN];
int main() { // A * B
    while (~scanf("%s%s", A + 1, B + 1)) {
        int n = strlen(A + 1), m = strlen(B + 1);
        n--, m--;
        for (int i = 0; i <= n; i++) FFT::A[i].x = A[n - i + 1] - '0', FFT::A[i].y = 0;
        for (int i = 0; i <= m; i++) FFT::B[i].x = B[m - i + 1] - '0', FFT::B[i].y = 0;
        L = 0, limit = 1;
        while (limit <= n + m) limit <<= 1, L++;
        for (int i = n+1; i < limit; i++) FFT::A[i].x = 0, FFT::A[i].y = 0;
        for (int i = m+1; i < limit; i++) FFT::B[i].x = 0, FFT::B[i].y = 0;
        for (int i = 0; i < limit; i++)
            R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
        FFT::FFT(FFT::A, 1);
        FFT::FFT(FFT::B, 1);
        for (int i = 0; i < limit; i++) FFT::A[i] = FFT::A[i] * FFT::B[i];
        FFT::FFT(FFT::A, -1);
        for (int i = 0; i <= n + m; i++) {
            sum[i] = (int) (FFT::A[i].x / limit + 0.5);
        }
        sum[n+m+1] = 0;
        for (int i = 0; i <= n + m; i++) {
            sum[i + 1] += sum[i] / 10;
            sum[i] %= 10;
        }
        int len = n + m + 1;
        while (sum[len] == 0 && len > 0) len--;
        for (int i = len; i >= 0; i--)printf("%d", sum[i]);
        printf("\n");
    }
}
