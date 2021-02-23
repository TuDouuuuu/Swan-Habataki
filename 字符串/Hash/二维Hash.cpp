const ull base1 = 19260817;
const ull base2 = 233;
const int MAXN = 1005;
ull b1[MAXN], b2[MAXN];
void init() {
    b1[0] = 1, b2[0] = 1;
    for (int i = 1; i < MAXN; i++) b1[i] = b1[i - 1] * base1;
    for (int i = 1; i < MAXN; i++) b2[i] = b2[i - 1] * base2;
}
char pat[55][55];
ull get_hash1(int p, int q) {
    ull ans = 0;
    for (int i = 1; i <= p; i++) {
        ull tmp = 0;
        for (int j = 1; j <= q; j++) {
            tmp = tmp * base1 + pat[i][j];
        }
        ans = ans * base2 + tmp;
    }
    return ans;
}

char str[MAXN][MAXN];
ull Hash[2][MAXN][MAXN];
void get_hash2(int n, int m, int p, int q) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= q; j++) Hash[0][i][j] = (j == 1) ? str[i][j] : Hash[0][i][j - 1] * base1 + str[i][j];
        for (int j = q + 1; j <= m; j++)
            Hash[0][i][j] = Hash[0][i][j - 1] * base1 + str[i][j] - str[i][j - q] * b1[q];
    }
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= p; i++)
            Hash[1][i][j] = (i == 1) ? Hash[0][i][j] : Hash[1][i - 1][j] * base2 + Hash[0][i][j];
        for (int i = p + 1; i <= n; i++)
            Hash[1][i][j] = Hash[1][i - 1][j] * base2 + Hash[0][i][j] - Hash[0][i - p][j] * b2[p];
    }
}
multiset<ull> st;
int main() {
    init();
    int n, m, t, p, q; int kass = 1;
    while (~scanf("%d%d%d%d%d", &n, &m, &t, &p, &q) && (n + m + t + p + q)) {
        st.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%s", str[i] + 1);
        }
        for (int i = 1; i <= t; i++) {
            for (int i = 1; i <= p; i++) {
                scanf("%s", pat[i] + 1);
            }
            st.insert(get_hash1(p, q));
        }
        get_hash2(n, m, p, q);
        int res = 0;
        for (int i = p; i <= n; i++) {
            for (int j = q; j <= m; j++) st.erase(Hash[1][i][j]);
        }
        printf("Case %d: %d\n", kass++, t - SZ(st));
    }
}