// 颜色段的定义是极长的连续相同颜色被认为是一段。例如112221由三段组成：11、222、1。
class LCT { public:
    int st_top, st[MAXN];
    int fa[MAXN], ch[MAXN][2];
    bool rev[MAXN];
    int col[MAXN], colL[MAXN], colR[MAXN], sum[MAXN];
    int lazy[MAXN];

    inline void push_up(int x) {
        int l = ch[x][0], r = ch[x][1];
        colL[x] = l ? colL[l] : col[x];
        colR[x] = r ? colR[r] : col[x];
        if (l && r) sum[x] = sum[l] + sum[r] + 1 - (colR[l] == col[x]) - (colL[r] == col[x]);
        if (l && !r) sum[x] = sum[l] + 1 - (colR[l] == col[x]);
        if (!l && r) sum[x] = sum[r] + 1 - (colL[r] == col[x]);
        if (!l && !r) sum[x] = 1;
    }

    inline void push_down(int x) {
        int l = ch[x][0], r = ch[x][1];
        if (rev[x]) {
            if (l) swap(ch[l][0], ch[l][1]), swap(colL[l], colR[l]), rev[l] ^= 1;
            if (r) swap(ch[r][0], ch[r][1]), swap(colL[r], colR[r]), rev[r] ^= 1;
            rev[x] = 0;
        }
        if (lazy[x]) {
            if (l) colL[l] = colR[l] = col[l] = lazy[x], sum[l] = 1, lazy[l] = lazy[x];
            if (r) colL[r] = colR[r] = col[r] = lazy[x], sum[r] = 1, lazy[r] = lazy[x];
            lazy[x] = 0;
        }
    }

    inline void makeroot(int x) {   // 使得p成为原树的根
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]), swap(colL[x], colR[x]), rev[x] ^= 1;
    }

} tree;

int main() {
    int n, q;   cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> tree.col[i];
        tree.colL[i] = tree.colR[i] = tree.col[i];
        tree.sum[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        int u, v;   cin >> u >> v;
        tree.link(u, v);
    }
    while (q--) {
        char opt;   cin >> opt;
        if (opt == 'C') {   // 将节点u到节点v的路径上的所有点（包括u和v）都染成颜色c
            int u, v, c;    cin >> u >> v >> c;
            tree.split(u, v);
            tree.colL[v] = tree.colR[v] = tree.col[v] = c, tree.sum[v] = 1, tree.lazy[v] = c;
        } else {    // 询问节点u到节点v的路径上的颜色段数量
            int u, v;   cin >> u >> v;
            tree.split(u, v);
            printf("%d\n", tree.sum[v]);
        }
    }
}