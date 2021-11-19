/*  aPaPBbP
    3
    1 2         2
    1 3         1
    2 3         0       */
class BIT { public:
    int a[MAXN], n;
    inline void init(int _n) { n = _n; }
    inline int lowbit(int x) { return x & (-x); }
    void add(int pos, int v) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            a[i] += v;
        }
    }
    int sum(int x) {
        int ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i)) ans += a[i];
        return ans;
    }
    int query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
} bit;
class AC {  public:
    int T[MAXN][MAXC], fail[MAXN];
    void init(int _T[][MAXC], int top) {
        for (int i = 1; i <= top; i++) {
            for (int j = 0; j < MAXC; j++)
                T[i][j] = _T[i][j];
        }
    }
    void build() {
        fail[1] = 1;
        queue<int> q;
        for (int i = 0; i < MAXC; i++) {
            if (T[1][i]) {
                q.push(T[1][i]); fail[T[1][i]] = 1;
            } else T[1][i] = 1;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < MAXC; i++) {
                if (T[u][i]) {
                    q.push(T[u][i]);
                    fail[T[u][i]] = T[fail[u]][i];
                } else T[u][i] = T[fail[u]][i];
            }
        }
    }
    struct Edge {
        int to, nex;
    } e[MAXN];
    int head[MAXN], tol;
    void addEdge(int u, int v) {
        e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
    }
    void buildEdge(int top) {
        for (int i = 1; i <= top; i++) head[i] = -1;
        for (int i = 2; i <= top; i++) addEdge(fail[i], i);
    }
    int dfn[MAXN], son[MAXN], dfn_cnt;
    void dfs(int u) {
        dfn[u] = ++dfn_cnt;
        son[u] = 1;
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            dfs(v);
            son[u] += son[v];
        }
    }
} ac;
struct node {
    int x, y;
} nd[MAXN];
int T[MAXN][MAXC], fa[MAXN], ans[MAXN];
char s[MAXN];
vector<int> qs[MAXN];
int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int m; scanf("%d", &m);
    int u = 1, top = 1;
    vi pos;
    for (int i = 1; i <= n; i++) {
        if ('a' <= s[i] && s[i] <= 'z') {
            int ch = s[i] - 'a';
            if (!T[u][ch]) {
                T[u][ch] = ++top, fa[top] = u;
            }
            u = T[u][ch];
        } else if (s[i] == 'P') pos.pb(u);
        else u = fa[u];
    }
    ac.init(T, top), ac.build(), ac.buildEdge(top), ac.dfs(1);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &nd[i].x, &nd[i].y);
        qs[pos[nd[i].y - 1]].pb(i);
    }
    function<void(int)> dfs = [&](int u) {
        bit.add(ac.dfn[u], 1);
        for (auto idx: qs[u]) {
            int x = nd[idx].x, y = nd[idx].y;
            ans[idx] = bit.query(ac.dfn[pos[x - 1]], ac.dfn[pos[x - 1]] + ac.son[pos[x - 1]] - 1);
        }
        for (int i = 0; i < MAXC; i++) {
            if (T[u][i]) dfs(T[u][i]);
        }
        bit.add(ac.dfn[u], -1);
    };
    bit.init(top);
    dfs(1);
    for (int i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }
}