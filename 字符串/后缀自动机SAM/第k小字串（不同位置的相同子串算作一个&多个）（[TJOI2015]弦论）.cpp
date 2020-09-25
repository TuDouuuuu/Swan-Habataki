/*
    input   output
    aabc    aab
    0 3
    aabc    aa
    1 3
    aabc    -1
    1 11
*/
const int MAXN = 1e6 + 5;
const int MAXC = 26;

class Suffix_Automaton { public:
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC];
    int val[MAXN];

    void init() {
        rt = 1;
        link[1] = maxlen[1] = 0;
        memset(trans[0], 0, sizeof(trans[0]));
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

    int sz1[MAXN], sz2[MAXN];
    int topo[MAXN], topo_id[MAXN];

    // Graph
    struct Edge {
        int to, nex;
    } e[MAXN];
    int head[MAXN], tol;

    void addEdge(int u, int v) {
        e[tol].to = v;
        e[tol].nex = head[u];
        head[u] = tol;
        tol++;
    }

    void dfs(int u) {
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            dfs(v);
            val[u] += val[v];
        }
    }

    void build() {
        // get topo index
        for (int i = 1; i <= rt; i++) topo[maxlen[i]]++;
        for (int i = 1; i <= rt; i++) topo[i] += topo[i - 1];
        for (int i = 1; i <= rt; i++) topo_id[topo[maxlen[i]]--] = i;
        // when t = 0
        for (int i = rt; i >= 1; i--) {
            sz1[topo_id[i]] = 1;
            if (topo_id[i] == 1) sz1[topo_id[i]] = 0;
            for (int j = 0; j < MAXC; j++) {
                int v = trans[topo_id[i]][j];
                if (!v) continue;
                sz1[topo_id[i]] += sz1[v];
            }
        }
        // fail tree build begin
        for (int i = 0; i <= rt; i++) head[i] = -1;
        tol = 0;
        for (int i = 2; i <= rt; i++) addEdge(link[i], i);
        // fail tree build end
        dfs(1); // dfs val
        // when t = 1
        for (int i = rt; i >= 1; i--) {
            sz2[topo_id[i]] = val[topo_id[i]];
            if (topo_id[i] == 1) sz2[topo_id[i]] = 0;
            for (int j = 0; j < MAXC; j++) {
                int v = trans[topo_id[i]][j];
                if (!v) continue;
                sz2[topo_id[i]] += sz2[v];
            }
        }
    }

    void query0(int k) {    // 不同位置的相同子串算作一个
        if (sz1[1] < k) {
            printf("-1\n"); return ;
        }
        int u = 1;
        while (k) {
            for (int i = 0; i < MAXC; i++) {
                if (trans[u][i]) {
                    if (sz1[trans[u][i]] >= k) {
                        printf("%c", 'a' + i);
                        u = trans[u][i];
                        k--;
                        break;
                    } else k -= sz1[trans[u][i]];
                }
            }
        }
        printf("\n");
    }

    void query1(int k) {    // 不同位置的相同子串算作多个
        if (sz2[1] < k) {
            printf("-1\n"); return ;
        }
        int u = 1;
        while(k > 0) {
            for (int i = 0; i < MAXC; i++) {
                if (trans[u][i]) {
                    int v = trans[u][i];
                    if (sz2[v] >= k) {
                        printf("%c", 'a'+i);
                        u = v;
                        k -= val[v];
                        break;
                    } else k -= sz2[v];
                }
            }
        }
        printf("\n");
    }
} sa;