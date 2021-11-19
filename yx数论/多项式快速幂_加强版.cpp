ll LnF[MAXN * 3];

void getKsm(ll F[], ll G[], int n, int k, int k1, int k2) {
    int num0 = n;
    for (int i = 0; i <= n; i++) {
        if (F[i]) {
            num0 = i;
            break;
        }
    }
    if ((ll) num0 * k2 > (ll) n) return;

    int m = n;
    n -= num0;
    for (int i = 0; i <= n; i++)F[i] = F[i] = F[i + num0];
    int f0 = F[0], inv_f0 = inv(f0);
    for (int i = 0; i <= n; i++) F[i] = F[i] * inv_f0 % mod;

    getLn(F, LnF, n);
    for (int i = 0; i <= n; i++) LnF[i] = LnF[i] * k % mod;
    getExp(LnF, G, n);

    f0 = powmod(f0, k1);
    for (int i = 0; i <= n; i++)G[i] = G[i] * f0 % mod;

    n = m, num0 = min((ll)num0 * k2, (ll)n);
    for (int i = n; i >= num0; i--) G[i] = G[i-num0];
    for (int i = num0-1; i >= 0; i--) G[i] = 0;
}

char s[MAXN]; ll AA[MAXN * 3], BB[MAXN * 3];
int main() {
    int n; scanf("%d", &n);
    ll k = 0, k1 = 0, k2 = 0;
    scanf("%s", s + 1);
    int klen = strlen(s + 1);
    for (int i = 1; i <= klen; i++) {
        k = (k * 10 % mod + s[i] - '0') % mod;
        k1 = (k1 * 10 % (mod - 1) + s[i] - '0') % (mod - 1);
        if (k2 * 10 + s[i] - '0' <= mod) k2 = k2 * 10 + s[i] - '0';
    }
    for (int i = 0; i < n; i++) scanf("%lld", &AA[i]);

    NTT::getKsm(AA, BB, n-1, k, k1, k2);
    for (int i = 0; i < n; i++) printf("%lld ", BB[i]);
}