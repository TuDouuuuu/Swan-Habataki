struct LCA {
    int fa[MAXN][22], dep[MAXN], n, limt, bin[22], len[MAXN];
    ll sd[2], p[2], ha[MAXN][2], tmp[MAXN][2];
    vector<int> mp[MAXN];
    void init(int _n) {
        n = _n;
        for (limt = 1; 1 << (limt - 1) <= n; limt++);
        for (int i = bin[0] = 1; 1 << (i - 1) <= n; i++) bin[i] = (bin[i - 1] << 1);
        sd[0] = 13331, sd[1] = 23333;
        p[0] = 1e9 + 7, p[1] = 998244353;
        mem(ha[0], 0);
        tmp[0][0] = tmp[0][1] = 1;
        mem(fa[0], 0);
        for (int i = 1; i <= n; i++) {
            mp[i].clear();
            mem(fa[i], 0);
            tmp[i][0] = tmp[i - 1][0] * sd[0] % p[0];
            tmp[i][1] = tmp[i - 1][1] * sd[1] % p[1];
        }
    }
    void add_edge(int a, int b) { mp[a].pb(b); }
    void dfs(int x, int pre) {
        ha[x][0] = (ha[pre][0] * sd[0] + len[x]) % p[0];
        ha[x][1] = (ha[pre][1] * sd[1] + len[x]) % p[1];
        for (int i = 1; bin[i] <= dep[x]; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
        for (int i = 0; i < sz(mp[x]); i++) {
            int to = mp[x][i];
            if (to == pre) continue;
            dep[to] = dep[x] + 1;
            fa[to][0] = x;
            dfs(to, x);
        }
    }
    void work(int rt) {
        dep[rt] = 0;
        dfs(rt, 0);
    }
    int find(int a, int L) {
        if (len[a] == L) return a;
        for (int i = limt; ~i; i--) {
            if (len[fa[a][i]] > L) a = fa[a][i];
        }
        assert(len[fa[a][0]] == L);
        return fa[a][0];
    }
    ll get(int l, int r, int f) {
        int LEN = dep[r] - dep[l] + 1;
        if (l == 0) return ha[r][f];
        return ((ha[r][f] - ha[fa[l][0]][f] * tmp[LEN][f]) % p[f] + p[f]) % p[f];
    }
    void comp(int x, int y) {
        int tx, ty;
        tx = x, ty = y;
        if (len[tx] != len[ty]) {
            if (len[tx] < len[ty]) puts("sjfnb");
            else if (len[tx] > len[ty]) puts("cslnb");
            return;
        }
        for (int i = limt; ~i; i--) {
            if (get(fa[tx][i], tx, 0) == get(fa[ty][i], ty, 0) &&
                get(fa[tx][i], tx, 1) == get(fa[ty][i], ty, 1)) {
                tx = fa[tx][i];
                ty = fa[ty][i];
            }
        }
        tx = fa[tx][0];
        ty = fa[ty][0];
        if (len[tx] < len[ty]) puts("sjfnb");
        else if (len[tx] > len[ty]) puts("cslnb");
        else puts("draw");
    }
} lca;
int pos[MAXN];
struct Palindrome_Tree {
    struct node {
        int ch[MAXC];
        int fail, len;
    } T[MAXN];
    int las, tol;
    int c[MAXN];  // cnt 计数, pos记录位置
    int get_fail(int x, int pos) {
        while (c[pos - T[x].len - 1] != c[pos]) {
            x = T[x].fail;
        }
        return x;
    }
    void init() { // 传入字符串长度
        memset(T[0].ch, 0, sizeof(T[0].ch));
        memset(T[1].ch, 0, sizeof(T[1].ch));
        T[0].len = 0, T[1].len = -1;
        T[0].fail = 1, T[1].fail = 0;
        las = 0; tol = 1;
    }
    void insert(char s[], int len) {
        c[0] = -1;
        for (int i = 1; i <= len; i++) {
            c[i] = s[i] - 'a';
            int p = get_fail(las, i);
            if (!T[p].ch[c[i]]) {
                T[++tol].len = T[p].len + 2;
                memset(T[tol].ch, 0, sizeof(T[tol].ch));
                int u = get_fail(T[p].fail, i);
                T[tol].fail = T[u].ch[c[i]];
                T[p].ch[c[i]] = tol;
            }
            las = T[p].ch[c[i]];
            pos[i] = las;
        }
    }
    void dfs(int u) {
        printf("u = %d T[u].fail = %d T[u].len = %d\n", u, T[u].fail, T[u].len);
        for (int i = 0; i < 26; i++) {
            if (T[u].ch[i]) {
                printf("%d %d %d\n", u, i, T[u].ch[i]);
                dfs(T[u].ch[i]);
            }
        }
    }
    void build() {
        lca.init(tol + 1);
        for (int i = 1; i <= tol; i++) lca.add_edge(T[i].fail + 1, i + 1);
        for (int i = 0; i <= tol; i++) lca.len[i + 1] = T[i].len;
        lca.work(1);
    }
} tree;
char s[MAXN];
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int len;
        scanf("%d", &len);
        scanf("%s", s + 1);
        tree.init();
        tree.insert(s, len);
        tree.build();
        int q; scanf("%d", &q);
        while (q--) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            int x = lca.find(pos[b] + 1, b - a + 1);
            int y = lca.find(pos[d] + 1, d - c + 1);
            lca.comp(x, y);
        }
    }
}