/*  要求a0 = 1    */
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

inline void getD(ll F[], ll G[], int n) {
    for (int i = 1; i <= n; i++) G[i - 1] = (ll) i * F[i] % mod;
    G[n] = 0;
    for (int i = n + 1; i < limit; i++) G[i] = 0;
}
inline void getJ(ll F[], ll G[], int n) {
    for (int i = 1; i <= n; i++) G[i] = F[i - 1] * inv(i) % mod;
    G[0] = 0;
}


ll A[MAXN * 3], B[MAXN * 3];
void getLn(ll F[], ll G[], int n) {
    L = 0, limit = 1;
    while (limit <= (n << 1)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++) B[i] = 0;

    getD(F, A, n);
    getInv(F, B, n);

    L = 0, limit = 1;
    while (limit <= (n << 1)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++)
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

    NTT(A, 1), NTT(B, 1);
    for (int i = 0; i < limit; i++) A[i] = A[i] * B[i] % mod;
    NTT(A, -1);

    getJ(A, G, n);
    for (int i = n + 1; i < limit; i++) G[i] = 0;
}


ll LnG[MAXN * 3];
void getExp(ll F[], ll G[], int n) {
    if (n == 0) {
        G[0] = 1;
        return;
    }
    getExp(F, G, n >> 1);
    getLn(G, LnG, n);

    L = 0, limit = 1;
    while (limit <= (n << 1)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++)
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

    LnG[0] = (F[0] + 1 - LnG[0] + mod) % mod;
    for (int i = 1; i <= n; i++) LnG[i] = (F[i] - LnG[i] + mod) % mod;

    NTT(LnG, 1), NTT(G, 1);
    for (int i = 0; i < limit; i++) G[i] = G[i] * LnG[i] % mod;
    NTT(G, -1);

    for (int i = n + 1; i < limit; i++) G[i] = 0;
}

void getKsm(ll F[], ll G[], int n, ll times) {
    G[0] = 1;

    L = 0, limit = 1;
    while (limit <= (n << 1)) limit <<= 1, L++;
    for (int i = 0; i < limit; i++)
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

    while (times) {
        NTT(F, 1);
        if (times & 1) {
            NTT(G, 1);
            for (int i = 0; i < limit; i++) G[i] = G[i] * F[i] % mod;
            NTT(G, -1);
            for (int i = n + 1; i < limit; i++) G[i] = 0;
        }
        for (int i = 0; i < limit; i++) F[i] = F[i] * F[i] % mod;
        NTT(F, -1);
        for (int i = n + 1; i < limit; i++) F[i] = 0;

        times >>= 1;
    }
}

