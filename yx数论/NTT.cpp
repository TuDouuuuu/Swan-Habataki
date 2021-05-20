const int mod = 998244353;
const int mod_g = 3;
const int mod_g_inv = inv(mod_g);

int limit = 1;
int L, R[MAXN * 3];

void NTT(ll a[], int type) {
    for (int i = 0; i < limit; i++)
        if (i < R[i]) swap(a[i], a[R[i]]);
    for (int j = 1; j < limit; j <<= 1) {
        ll Wn = powmod(type == 1 ? mod_g : mod_g_inv, (mod - 1) / (j << 1));
        for (int k = 0; k < limit; k += (j << 1)) {
            ll w = 1;
            for (int i = 0; i < j; i++, w = w * Wn % mod) {
                int x = a[i + k], y = w * a[j + k + i] % mod;
                a[i + k] = (x + y) % mod;
                a[j + k + i] = (x - y + mod) % mod;
            }
        }
    }
    if (type == -1) {
        int inv_limit = inv(limit);
        for (int i = 0; i < limit; i++) a[i] = (ll) a[i] * inv_limit % mod;
    }
}