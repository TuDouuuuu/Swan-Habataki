class Suffix_Automaton {
public:
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC];
    int val[MAXN];  // 用于统计某一串出现的次数

    void init() {
        rt = 1;
        link[1] = maxlen[1] = 0;
        memset(trans[0], 0, sizeof(trans[0]));
        memset(trans[1], 0, sizeof(trans[1]));
    }

    Suffix_Automaton() { init(); }

    inline int insert(int ch, int last) {   // main: last = 1
        if (trans[last][ch]) {
            int p = last, x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) return x;
            else {
                int y = ++rt;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[x] = y;
                return y;
            }
        }
        int z = ++rt, p = last;
        val[z] = 1; // dfs树统计出现次数
        memset(trans[z], 0, sizeof(trans[z]));
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
        ans_1 += maxlen[z] - maxlen[link[z]]; // 【应用1】统计不同字串个数
        return z;
    }

    struct Edge {
        int to, nex;
    } e[MAXN << 1];
    int head[MAXN], tol;

    void addEdge(int u, int v) {
        e[tol].to = v; e[tol].nex = head[u]; head[u] = tol; tol++;
    }


/*  统计出现次数为k的字串个数
    intput          output
    2               (输入组数)
    2               6
    abcabc
    3               9
    abcabcabcabc
*/
    ll ans = 0;
    void dfs(int u, int k) {
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            dfs(v, k);
            val[u] += val[v];
        }
        if (val[u] == k) {  // val为出现次数
            ans += 1ll * (maxlen[u] - maxlen[link[u]]); // 以当前状态st为结尾的长度
        }
    }

    int build(int k) {
        tol = 0;
        for (int i = 0; i <= rt; i++) head[i] = -1;
        for (int i = 2; i <= rt; i++) addEdge(link[i], i);  // 建fail树
        dfs(1, k);
    }
} sa;