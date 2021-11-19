/*  要求a0 = 1    */
char s[MAXN];
ll getK() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = ans * 10 + s[i] - '0';
        ans %= mod;
    }
    return ans;
}

ll AA[MAXN * 3], BB[MAXN * 3], CC[MAXN * 3];
int main() {
    int n; scanf("%d", &n);
    ll k = getK();
    for (int i = 0; i < n; i++) scanf("%lld", &AA[i]);
    NTT::getLn(AA, BB, n - 1);
    for (int i = 0; i < n; i++) BB[i] = BB[i] * k % mod;
    NTT::getExp(BB, CC, n - 1);
    for (int i = 0; i < n; i++) printf("%lld ", CC[i]);
}