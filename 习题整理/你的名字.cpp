/*  S = scbamgepe   
    3
    smape 2 7       12
    sbape 3 8       10
    sgepe 1 9       4       */

class SEG { public:
    int ch[MAXN*30][2], maxx[MAXN*30], sum[MAXN*30];
#define lson ch[rt][0]
#define rson ch[rt][1]
    int pool[MAXN], pool_cnt, cnt;
    int New() {
        return pool_cnt ? pool[pool_cnt--] : ++cnt;
    }
    inline void push_up(int rt) {
        sum[rt] = sum[lson] + sum[rson];
        maxx[rt] = max(maxx[lson], maxx[rson]);
    }
    int add(int rt, int pos, int v, int be, int en) {
        if (!rt) rt = New();
        if (be == en) {
            sum[rt] += v;
            maxx[rt] = be;
            return rt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) lson = add(lson, pos, v, be, mid);
        else
            rson = add(rson, pos, v, mid + 1, en);
        push_up(rt);
        return rt;
    }
    int query_sum(int rt, int L, int R, int be, int en) {
        if (!rt) return 0;
        if (L <= be && en <= R) return sum[rt];
        int mid = (be + en) >> 1;
        int ans = 0;
        if (L <= mid) ans += query_sum(lson, L, R, be, mid);
        if (R > mid) ans += query_sum(rson, L, R, mid + 1, en);
        return ans;
    }
    int query_max(int rt, int L, int R, int be, int en) {
        if (!rt) return 0;
        if (L <= be && en <= R) return maxx[rt];
        int mid = (be + en) >> 1;
        int ans = 0;
        if (L <= mid) ans = max(ans, query_max(lson, L, R, be, mid));
        if (R > mid) ans = max(ans, query_max(rson, L, R, mid + 1, en));
        return ans;
    }
    int merge(int x, int y, int be, int en) {
        if (!x || !y) return x + y;
        int nrt = ++cnt;
        if (be == en) {
            sum[nrt] = sum[x] + sum[y];
            maxx[nrt] = be;
            return nrt;
        }
        int mid = (be + en) >> 1;
        ch[nrt][0] = merge(ch[x][0], ch[y][0], be, mid);
        ch[nrt][1] = merge(ch[x][1], ch[y][1], mid + 1, en);
        push_up(nrt);
        return nrt;
    }
} tree;

int root[MAXN];
namespace saS {
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC];
    void init() {
        rt = 1, link[1] = maxlen[1] = 0;
    }
    int insert(int ch, int last) {
        int z = ++rt, p = last;
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
    struct Edge {
        int to, nex;
    } e[MAXN];
    int head[MAXN], tol;
    void addEdge(int u, int v) {
        e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
    }
    void build_link_tree() {
        for (int i = 1; i <= rt; i++) head[i] = -1;
        for (int i = 2; i <= rt; i++) addEdge(link[i], i);
    }
    void dfs(int u, int f, int nS) {
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            dfs(v, u, nS);
            root[u] = tree.merge(root[u], root[v], 1, nS);
        }
    }
}

namespace saT {
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC], len[MAXN];
    ll res;
    void init() {
        rt = 1, link[1] = maxlen[1] = len[1] = 0, res = 0;
        memset(trans[1], 0, sizeof(trans[1]));
    }
    int insert(int ch, int last) {
        int z = ++rt, p = last;
        memset(trans[z], 0, sizeof(trans[z])), len[z] = 0;
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
                len[y] = 0;
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[z] = link[x] = y;
            }
        }
        return z;
    }
    struct Edge {
        int to, nex;
    } e[MAXN];
    int head[MAXN], tol;
    void addEdge(int u, int v) {
        e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
    }
    void build_link_tree() {
        for (int i = 1; i <= rt; i++) head[i] = -1;
        for (int i = 2; i <= rt; i++) addEdge(link[i], i);
    }
    void dfs(int u) {
        for (int i = head[u]; ~i; i = e[i].nex) {
            int v = e[i].to;
            dfs(v);
            len[u] = max(len[u], len[v]);
        }
        len[u] = min(len[u], maxlen[u]);
        res += maxlen[u] - maxlen[link[u]];
        res -= max(0, len[u] - maxlen[link[u]]);
    }
}

using saS::trans;
using saS::link;
using saS::maxlen;
char S[MAXN], T[MAXN];
int main() {
    scanf("%s", S + 1); int nS = strlen(S + 1);
    saS::init();
    int last = 1;
    for (int i = 1; i <= nS; i++) {
        last = saS::insert(S[i] - 'a', last);
        root[last] = tree.add(root[last], i, 1, 1, nS);
    }
    saS::build_link_tree(), saS::dfs(1, 0, nS);
    int Q; scanf("%d", &Q);
    while (Q--) {
        scanf("%s", T + 1);
        int L, R; scanf("%d%d", &L, &R);
        saT::init();
        int nT = strlen(T + 1), last = 1;
        int p = 1, nowlen = 0;
        for (int i = 1; i <= nT; i++) {
            int ch = T[i] - 'a';
            last = saT::insert(ch, last);
            while (p && !trans[p][ch]) p = link[p], nowlen = maxlen[p];
            if (!p) p = 1, nowlen = 0;
            else {
                p = trans[p][ch], nowlen++;
                while (p && !tree.query_sum(root[p], L, R, 1, nS)) p = link[p], nowlen = maxlen[p];
                while (p) {
                    int tx1 = tree.query_max(root[p], L, R, 1, nS), tx2 = maxlen[link[p]];
                    if (tx1 - tx2 + 1 >= L) break;
                    p = link[p], nowlen = maxlen[p];
                }

                if (!p) p = 1, nowlen = 0;
                saT::len[last] = min(nowlen, tree.query_max(root[p], L, R, 1, nS) - L + 1);
            }
        }
        saT::build_link_tree(), saT::dfs(1);
        printf("%lld\n", saT::res);
    }
}
