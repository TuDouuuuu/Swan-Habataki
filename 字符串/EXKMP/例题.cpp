/*  input   output
    3       5
    1 a     (aa aba aba abba baab)
    2 ab
    2 ba
*/
bool pali[2][MAXN];
namespace EXKMP {
    void getLCP(char T[], int T_len, int z[]) {
        int i, len = T_len;
        z[0] = len;
        for (i = 0; i < len - 1 && T[i] == T[i + 1]; i++);
        z[1] = i;
        int a = 1;
        for (int k = 2; k < len; k++) {
            int p = a + z[a] - 1, L = z[k - a];
            if ((k - 1) + L >= p) {
                int j = max((p - k + 1), 0);
                while (k + j < len && T[k + j] == T[j])j++;
                z[k] = j, a = k;
            } else z[k] = L;
        }
    }
    void exkmp(char S[], int S_len, char T[], int T_len, int extend[], int z[], int flag, int be) {
        getLCP(T, T_len, z);
        int a = 0;
        int MinLen = min(S_len, T_len);
        while (a < MinLen && S[a] == T[a])a++;
        extend[0] = a, a = 0;
        for (int k = 1; k < S_len; k++) {
            int p = a + extend[a] - 1, L = z[k - a];
            if ((k - 1) + L >= p) {
                int j = max((p - k + 1), 0);
                while (k + j < S_len && j < T_len && S[k + j] == T[j])j++;
                extend[k] = j;
                a = k;
            } else extend[k] = L;
        }
        for (int i = 0; i < S_len; i++) {
            if (i + extend[i] == S_len) pali[flag][be + i] = 1;
        }
    }
}

class TRIE {    public:
    int T[MAXN][26], cnt[MAXN], sum[MAXN];
    int top;
    void init() {
        top = 1;
        memset(T[0], 0, sizeof(T[0]));
        memset(cnt, 0, sizeof(cnt)), memset(sum, 0, sizeof(sum));
    }
    void insert(char str[], int n, int be) {
        int u = 0;
        for (int i = 0; i < n; i++) {
            int ch = str[i] - 'a';
            sum[u] += pali[0][be + i];
            if (!T[u][ch]) {
                memset(T[top], 0, sizeof(T[top]));
                T[u][ch] = top++;
            }
            u = T[u][ch];
        }
        cnt[u]++;
    }
    ll find(char str[], int n, int be) {
        ll ans = 0;
        int u = 0;
        for (int i = 0; i < n; i++) {
            int ch = str[i] - 'a';

            u = T[u][ch];
            if (!u) break;
            if ((i < n - 1 && pali[1][be + i + 1]) || (i == n - 1)) ans += cnt[u];
        }
        if (u) ans += sum[u];
        return ans;
    }
} tree;

int be[MAXN], en[MAXN]; // save begin and end
char str_[MAXN], _str[MAXN];
int extend[MAXN], z[MAXN];

int main() {
    tree.init();
    int n; scanf("%d", &n);
    int sumlen = 0;
    for (int i = 1; i <= n; i++) {
        int len; scanf("%d", &len);
        scanf("%s", str_ + sumlen);
        for (int j = 0; j < len; j++) {
            _str[sumlen + j] = str_[sumlen + len - j - 1];
        }
        be[i] = sumlen;
        en[i] = sumlen + len - 1;
        sumlen = sumlen + len;
        EXKMP::exkmp(str_ + be[i], len, _str + be[i], len, extend, z, 0, be[i]);
        EXKMP::exkmp(_str + be[i], len, str_ + be[i], len, extend, z, 1, be[i]);
        tree.insert(str_ + be[i], len, be[i]);
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        res += tree.find(_str + be[i], en[i] - be[i] + 1, be[i]);
    }
    printf("%lld\n", res);
}