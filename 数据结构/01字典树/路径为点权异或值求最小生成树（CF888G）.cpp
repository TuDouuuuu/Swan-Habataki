class Trie {    public:
    int T[SIZE<<4][2], top;
    Trie() {
        top = 1;
        memset(T[0], 0, sizeof(T[0]));
    }
    void insert(int x) {    // call: tree.insert(x);
        int u = 0;
        for (int i = 30; ~i; i--) {
            int ch = (x >> i) & 1;
            if(!T[u][ch]) {
                memset(T[top], 0, sizeof(T[top]));
                T[u][ch] = top++;
            }
            u = T[u][ch];
        }
    }
    ll query(int rt1, int rt2, int dp) {
        if(dp < 0) return (ll)0;
        ll res1 = -1, res2 = -1;
        if(T[rt1][0] && T[rt2][0]) res1 = query(T[rt1][0], T[rt2][0], dp-1);
        if(T[rt1][1] && T[rt2][1]) res2 = query(T[rt1][1], T[rt2][1], dp-1);
        if(~res1 && ~res2) return std::min(res1, res2);
        if(~res1) return res1; if(~res2) return res2;
        if(T[rt1][0] && T[rt2][1]) res1 = query(T[rt1][0], T[rt2][1], dp-1) + (1 << dp);
        if(T[rt1][1] && T[rt2][0]) res2 = query(T[rt1][1], T[rt2][0], dp-1) + (1 << dp);
        if(~res1 && ~res2) return std::min(res1, res2);
        if(~res1) return res1; if(~res2) return res2;
    }
} tree;
ll res;
void dfs(int a, int b) {    // call: dfs(0, 30);
    if(b<0) return ;
    if(tree.T[a][0] && tree.T[a][1]) {
        res += 1ll * tree.query(tree.T[a][0], tree.T[a][1], b-1) + 1ll * (1 << b);
    }
    if(tree.T[a][0]) dfs(tree.T[a][0], b-1);
    if(tree.T[a][1]) dfs(tree.T[a][1], b-1);
}