namespace FWT {
    // limit = 1;
    // while (limit <= (n2 << 1)) limit <<= 1;
    int limit;
    void FWT_or(int a[], int opt) {
        for (int i = 1; i < limit; i <<= 1) {
            for (int p = i << 1, j = 0; j < limit; j += p) {
                for (int k = 0; k < i; k++) {
                    if (opt == 1) a[i + j + k] = (a[j + k] + a[i + j + k]) % mod;
                    else a[i + j + k] = (a[i + j + k] + mod - a[j + k]) % mod;
                }
            }
        }
    }
    void FWT_and(int a[], int opt) {
        for (int i = 1; i < limit; i <<= 1) {
            for (int p = i << 1, j = 0; j < limit; j += p) {
                for (int k = 0; k < i; k++) {
                    if (opt == 1) a[j + k] = (a[j + k] + a[i + j + k]) % mod;
                    else a[j + k] = (a[j + k] + mod - a[i + j + k]) % mod;
                }
            }
        }
    }
    void FWT_xor(int a[], int opt) {
        for (int i = 1; i < limit; i <<= 1) {
            for (int p = i << 1, j = 0; j < limit; j += p) {
                for (int k = 0; k < i; k++) {
                    int x = a[j + k], y = a[i + j + k];
                    a[j + k] = (x + y) % mod, a[i + j + k] = (x + mod - y) % mod;
                    if (opt == -1)
                        a[j + k] = 1ll * a[j + k] * inv2 % mod, a[i + j + k] = 1ll * a[i + j + k] * inv2 % mod;
                }
            }
        }
    }
}