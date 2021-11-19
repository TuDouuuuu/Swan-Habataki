#define IT set<pii>::iterator
class TRIE {
public:
    int T[MAXN * 30][2], top, siz[MAXN * 30];
    vector<int> vec[MAXN * 30];
    TRIE() {
        top = 1; memset(T[0], 0, sizeof(T[0]));
    }
    void insert(int x) {
        int u = 1; siz[1]++;
        for (int i = MAXD; ~i; i--) {
            int ch = (x >> i) & 1;
            if (!T[u][ch]) {
                memset(T[top], 0, sizeof(T[top]));
                T[u][ch] = ++top;
            }
            u = T[u][ch]; siz[u]++;
        }
    }
#define lson T[u][0]
#define rson T[u][1]
    void dfs(int u, int dep) {
        vec[u].resize(siz[u]);
        if (dep == -1) return;
        if (lson) dfs(lson, dep - 1);
        if (rson) dfs(rson, dep - 1);

        if (!lson) {
            for (int i = 0; i < siz[u]; i++) vec[u][i] = vec[rson][i];
        } else if (!rson) {
            for (int i = 0; i < siz[u]; i++) vec[u][i] = vec[lson][i];
        } else {
            for (auto &e: vec[u]) e = inf;
            for (int i = 0; i < siz[u]; i++) {
                if (i < siz[lson]) vec[u][i] = min(vec[u][i], vec[lson][i]);
                else vec[u][i] = min(vec[u][i], vec[rson][i - siz[lson]] | (1 << dep));

                if (i < siz[rson]) vec[u][i] = min(vec[u][i], vec[rson][i]);
                else vec[u][i] = min(vec[u][i], vec[lson][i - siz[rson]] | (1 << dep));
            }
        }
    }

    int res;
    inline void query_l(int u, int L, int R, int k, int dep, int v) {
        if (dep == -1) {
            res = min(res, v);
            return;
        }
        if ((L >> dep & 1) == 0) {
            int ch = 1;
            if (k <= siz[T[u][0 ^ ch]]) res = min(res, v | vec[T[u][0 ^ ch]][k - 1]);
            else res = min(res, v | (1 << dep) | vec[T[u][1 ^ ch]][k - siz[T[u][0 ^ ch]] - 1]);
        }
        int ch = ((L >> dep & 1));
        if (k <= siz[T[u][0 ^ ch]]) query_l(T[u][0 ^ ch], L, R, k, dep - 1, v);
        else query_l(T[u][1 ^ ch], L, R, k - siz[T[u][0 ^ ch]], dep - 1, v | (1 << dep));
    }

    inline void query_r(int u, int L, int R, int k, int dep, int v) {
        if (dep == -1) {
            res = min(res, v);
            return;
        }
        if ((R >> dep & 1) == 1) {
            int ch = 0;
            if (k <= siz[T[u][0 ^ ch]]) res = min(res, v | vec[T[u][0 ^ ch]][k - 1]);
            else res = min(res, v | (1 << dep) | vec[T[u][1 ^ ch]][k - siz[T[u][0 ^ ch]] - 1]);
        }
        int ch = ((R >> dep & 1));
        if (k <= siz[T[u][0 ^ ch]]) query_r(T[u][0 ^ ch], L, R, k, dep - 1, v);
        else query_r(T[u][1 ^ ch], L, R, k - siz[T[u][0 ^ ch]], dep - 1, v | (1 << dep));
    }

    void query(int u, int L, int R, int k, int dep, int v) {
        if (dep == -1) {
            res = min(res, v); return;
        }
        if ((L >> dep & 1) == (R >> dep & 1)) {
            int ch = (L >> dep & 1);
            if (k <= siz[T[u][0 ^ ch]]) query(T[u][0 ^ ch], L, R, k, dep - 1, v);
            else query(T[u][1 ^ ch], L, R, k - siz[T[u][0 ^ ch]], dep - 1, v | (1 << dep));
        } else {
            int ch;

            ch = 0;
            if (k <= siz[T[u][0 ^ ch]]) query_l(T[u][0 ^ ch], L, R, k, dep - 1, v);
            else query_l(T[u][1 ^ ch], L, R, k - siz[T[u][0 ^ ch]], dep - 1, v | (1 << dep));

            ch = 1;
            if (k <= siz[T[u][0 ^ ch]]) query_r(T[u][0 ^ ch], L, R, k, dep - 1, v);
            else query_r(T[u][1 ^ ch], L, R, k - siz[T[u][0 ^ ch]], dep - 1, v | (1 << dep));
        }
    }
} tree;
int a[MAXN];
int main() {
    int n, Q; scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), tree.insert(a[i]);
    tree.dfs(1, MAXD);
    while (Q--) {
        int L, R, K; scanf("%d%d%d", &L, &R, &K);
        tree.res = inf;
        tree.query(1, L, R, K, MAXD, 0);
        printf("%d\n", tree.res);
    }
}
