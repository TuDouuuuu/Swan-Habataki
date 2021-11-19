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

void Mul(ll F[], ll G[], ll Q[], int n, int m) {
    L = 0, limit = 1;

    while (limit <= (n + m)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++)
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

    NTT(F, 1), NTT(G, 1);
    for (int i = 0; i < limit; i++) Q[i] = F[i] * G[i] % mod;
    NTT(Q, -1);
}

ll Fr[MAXN * 3], Gr[MAXN * 3], Gr_inv[MAXN * 3];
// F = Q * G + R
void Div(ll F[], ll G[], ll Q[], ll R[], int n, int m) {
    for (int i = 0; i <= n; i++) Fr[n - i] = F[i];
    for (int i = 0; i <= m; i++) Gr[m - i] = G[i];
    for (int i = n - m + 1; i <= m; i++) Gr[i] = 0;

    getInv(Gr, Gr_inv, n - m);
    Mul(Fr, Gr_inv, Fr, n, n - m);

    for (int i = 0; i <= n - m; i++) Q[i] = Fr[n - m - i];
    for (int i = 0; i <= n - m; i++) printf("%lld ", Q[i]);
    printf("\n");


    Mul(G, Q, G, m, n - m);
    for (int i = 0; i < m; i++) R[i] = (F[i] - G[i] + mod) % mod;
    for (int i = 0; i < m; i++) printf("%lld ", R[i]);
    printf("\n");
}
