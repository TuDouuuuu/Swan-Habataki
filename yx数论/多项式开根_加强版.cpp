/*  要求a0是mod下的二次剩余  */
ll C[MAXN * 3];
void getInv(ll F[], ll G[], int n) {
    if (n == 0) {
        G[0] = inv(F[0]);
        return;
    }
    getInv(F, G, n >> 1);

    L = 0, limit = 1;
    while (limit <= (n << 1)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++)
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

    for (int i = 0; i <= n; i++) C[i] = F[i];
    for (int i = n + 1; i < limit; i++) C[i] = 0;
    NTT(C, 1), NTT(G, 1);
    for (int i = 0; i < limit; i++)
        G[i] = ((2ll - G[i] * C[i] % mod) + mod) % mod * G[i] % mod;
    NTT(G, -1);

    for (int i = n + 1; i < limit; i++) G[i] = 0;
}

ll A[MAXN * 3], B[MAXN * 3];
void getSqrt(ll F[], ll G[], int n) {
    if (n == 0) {
        int x, y;
        Qr(F[0], mod, x, y);
        G[0] = x;
        return;
    }
    getSqrt(F, G, n >> 1);

    L = 0, limit = 1;
    while (limit <= (n << 1)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++) A[i] = 0;

    getInv(G, A, n);

    L = 0, limit = 1;
    while (limit <= (n << 1)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++)
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

    for (int i = 0; i <= n; i++) B[i] = F[i];
    for (int i = n + 1; i < limit; i++) B[i] = 0;

    NTT(B, 1), NTT(G, 1), NTT(A, 1);
    for (int i = 0; i < limit; i++) {
        G[i] = (A[i] * B[i] % mod + G[i]) % mod * inv2 % mod;
    }
    NTT(G, -1);
    for (int i = n + 1; i < limit; i++) G[i] = 0;
}
