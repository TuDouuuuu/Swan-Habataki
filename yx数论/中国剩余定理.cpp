ll a[MAXN], m[MAXN];
void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a%b, x, y);
    ll z = x;
    x = y, y = z - y * (a / b);
}
int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &m[i], &a[i]);
    }
    ll mul_sum = 1;
    for (int i = 1; i <= n; i++) mul_sum *= m[i];
    ll res = 0;
    for (int i = 1; i <= n;i++) {
        ll M = mul_sum / m[i];
        ll x = 0, y = 0;
        exgcd(M, m[i], x, y);
        res += a[i] * M * (x < 0 ? x + m[i] : x);
    }
    printf("%lld\n", res % mul_sum);
}