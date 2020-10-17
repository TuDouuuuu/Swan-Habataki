/*
    input       output
    6 3
    ABABBA
    1 1 3 3 4
    2 2         3
    2 1         3
    6 4         1
*/
class SAM { public:
    struct Edge {
        int to, nex;
    } e[MAXN];
    int head[MAXN], tol;

    void addEdge(int u, int v) {
        e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
    }
    void dfs(int u) {
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            dfs(v);
            val[u] += val[v];
        }
    }

    int fa[MAXN][32];
    void build() {
        for (int i = 1; i <= rt; i++) head[i] = -1;
        for (int i = 2; i <= rt; i++) addEdge(link[i], i);
        dfs(1);
        for (int i = 1; i <= rt; i++) fa[i][0] = link[i];
        for (int i = 1; i < 32; i++) {
            for (int j = 1; j <= rt; j++) {
                fa[j][i] = fa[fa[j][i - 1]][i - 1];
            }
        }
    }

    int query(int X, int L) {
        for (int i = 31; ~i; i--) { if (maxlen[fa[X][i]] >= L) X = fa[X][i];    }
        return val[X];
    }

    void debug() {
        for (int i = 1; i <= rt; i++) printf("link[%d] = %d\n", i, link[i]);
        for (int i = 1; i <= rt; i++) printf("val[%d] = %d\n", i, val[i]);
        for (int i = 1; i <= rt; i++) printf("maxlen[%d] = %d\n", i, maxlen[i]);
    }
} sa;

struct Edge {
    int to, nex;
} e[MAXNODE];
int head[MAXNODE], tol;

void addEdge(int u, int v) {
    e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
}

char str[MAXNODE];  int pos[MAXN];

struct node {
    int v, last;
    node(int _v = 0, int _last = 0) : v(_v), last(_last) {}
};

void bfs() {
    queue<node> q;
    q.push(node(1, 1));
    int last = 1;
    while (!q.empty()) {
        node u = q.front(); q.pop();
        int nls = sa.insert(str[u.v]-'A', u.last);
        pos[u.v] = nls;
        for (int i = head[u.v]; ~i; i = e[i].nex) {
            int to = e[i].to;
            q.push(node(to, nls));
        }
    }
//    pos[u] = last = sa.insert(str[u] - 'A', last);
//    for (int i = head[u]; ~i; i = e[i].nex) {
//        int v = e[i].to;
//        dfs(v, last);
//    }
}

void init(int n) {  for (int i = 1; i <= n; i++) head[i] = -1;  }
int main() {
    int n, q;   scanf("%d%d", &n, &q);
    init(n);
    scanf("%s", str + 1);
    for (int i = 2; i <= n; i++) {
        int x;  scanf("%d", &x);
        addEdge(x, i);
    }
    bfs();
//    dfs(1, 1);  // make sam
    sa.build(); // get fail tree
    while (q--) {
        int X, L;   scanf("%d%d", &X, &L);
        printf("%d\n", sa.query(pos[X], L));
    }
}