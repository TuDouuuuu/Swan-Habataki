class SAM {
public:
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC];
    int val[MAXN];

    void init() {
        rt = 1;
        link[1] = maxlen[1] = 0;
        memset(trans[1], 0, sizeof(trans[1]));
    }

    SAM() { init(); }

    inline int insert(int ch, int last) {   // main: last = 1
        if (trans[last][ch]) {
            int p = last, x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) {
                val[x]++;   // 统计出现次数
                return x;
            }
            else {
                int y = ++rt;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[x] = y;
                val[y]++;
                return y;
            }
        }
        int z = ++rt, p = last;
        val[z] = 1; // dfs树统计出现次数
        maxlen[z] = maxlen[last] + 1;
        while (p && !trans[p][ch]) trans[p][ch] = z, p = link[p];
        if (!p) link[z] = 1;
        else {
            int x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) link[z] = x;
            else {
                int y = ++rt;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[z] = link[x] = y;
            }
        }
        return z;
    }
} sa;

char str[MAXNODE];
int pos[MAXN];

void dfs(int u, int last) {
    pos[u] = last = sa.insert(str[u] - 'A', last);
   // printf("pos[%d] = %d\n", u, pos[u]);
    for (int i = head[u]; ~i; i = e[i].nex) {
        int v = e[i].to;
        dfs(v, last);
    }
}

void init(int n) {
    for (int i = 1; i <= n; i++) head[i] = -1;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    init(n);
    scanf("%s", str + 1);
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        addEdge(x, i);
    }
    dfs(1, 1);  // make sam
    sa.build(); // get fail tree
    // sa.debug();
    while (q--) {
        int X, L; scanf("%d%d", &X, &L);
        printf("%d\n", sa.query(pos[X], L));
    }
   // sa.debug();
}