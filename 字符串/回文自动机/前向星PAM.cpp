/*  [input]     [output]
    4           6
    babb
    2           2
    aa
*/
char str[MAXN];
ll num[MAXN][2];
class PAM { public:
    struct node {
        int fail, len;
        ll num;
    } T[MAXN];
    int las, tot;
    struct Edge {
        int to, w, nex;
    } e[MAXN << 1];
    int head[MAXN], tol;
    void addEdge(int u, int v, int w) { e[tol].to = v, e[tol].w = w, e[tol].nex = head[u], head[u] = tol, tol++; }
    inline int get_fail(int x, int pos) {
        while (str[pos - T[x].len - 1] != str[pos]) x = T[x].fail;
        return x;
    }
    void init() {
        head[0] = head[1] = -1;
        T[0].fail = 1, T[1].fail = 0;
        T[0].len = 0, T[1].len = -1;
        T[0].num = 0, T[1].num = 0;
        las = 0, tot = 1;
        tol = 0;
    }
    void insert1(char s[], int len) {
        s[0] = 26;
        for (int i = 1; i <= len; i++) {
            int p = get_fail(las, i);
            int flag = 0;
            for (int j = head[p]; ~j; j = e[j].nex) {
                if (e[j].w == s[i] - 'a') {
                    flag = e[j].to;
                    break;
                }
            }
            if (!flag) {
                T[++tot].len = T[p].len + 2;
                head[tot] = -1;
                int u = get_fail(T[p].fail, i);
                int fg = 0;
                for (int j = head[u]; ~j; j = e[j].nex) {
                    if (e[j].w == str[i] - 'a') {
                        fg = e[j].to;
                        break;
                    }
                }
                T[tot].fail = fg;
                T[tot].num = T[T[tot].fail].num + 1;
                addEdge(p, tot, str[i] - 'a');
                flag = tot;
            }
            las = flag;
            num[i][0] = T[las].num;
        }
    }
    void insert2(char s[], int len) {
        s[0] = 26;
        for (int i = 1; i <= len; i++) {
            int p = get_fail(las, i);
            int flag = 0;
            for (int j = head[p]; ~j; j = e[j].nex) {
                if (e[j].w == s[i] - 'a') {
                    flag = e[j].to;
                    break;
                }
            }
            if (!flag) {
                T[++tot].len = T[p].len + 2;
                head[tot] = -1;
                int u = get_fail(T[p].fail, i);
                int fg = 0;
                for (int j = head[u]; ~j; j = e[j].nex) {
                    if (e[j].w == str[i] - 'a') {
                        fg = e[j].to;
                        break;
                    }
                }
                T[tot].fail = fg;
                T[tot].num = T[T[tot].fail].num + 1;
                addEdge(p, tot, str[i] - 'a');
                flag = tot;
            }
            las = flag;
            num[len - i + 1][1] = T[las].num;
        }
    }
} tree;
int main() {
    int n; scanf("%d", &n);
    scanf("%s", str + 1);
    tree.init();
    tree.insert1(str, n);
    int n2 = n >> 1;
    for (int i = 1; i <= n2; i++) swap(str[i], str[n - i + 1]);
    tree.init();
    tree.insert2(str, n);
    for (int i = n - 1; i >= 1; i--) {
        num[i][1] += num[i + 1][1];
        if (num[i][1] >= mod) num[i][1] -= mod;
    }
    ll res1 = 0;
    for (int i = 1; i <= n; i++) {
        res1 += num[i][0] * num[i + 1][1] % mod;
    }
    ll res2 = (ll) (num[1][1]) * (num[1][1] - 1) / 2 % mod;
    ll res = res2 - res1;
    if (res < 0) res += ((0ll - res) / mod + 1) * mod;
    printf("%lld\n", res % mod);
}