class Treap { public:
    int ch[MAXN][2];
    int dat[MAXN], siz[MAXN], val[MAXN];
    bool fl[MAXN];
    int tot, root;

    void init() {
        tot = 0, root = 0;
    }
    Treap() { init(); }

    inline int Newnode(int v) {
        val[++tot] = v;
        dat[tot] = rand();
        siz[tot] = 1;
        return tot;
    }
    inline void push_up(int rt) {
        siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + 1;
    }

    int build(int l, int r) {
        if (l > r) return 0;
        int mid = (l + r) >> 1;
        int newnode = Newnode(mid);
        ch[newnode][0] = build(l, mid - 1);
        ch[newnode][1] = build(mid + 1, r);
        push_up(newnode);
        return newnode;
    }

    // 在外面
    if (fl[rt]) {
        if (ch[rt][0]) swap(ch[ch[rt][0]][0], ch[ch[rt][0]][1]), fl[rt] ^= 1;
        if (ch[rt][1]) swap(ch[ch[rt][1]][0], ch[ch[rt][1]][1]), fl[rt] ^= 1;
        fl[rt] = 0;
    }
    // lazy的打标记与线段树类似,在外面 val +=, lazy += ,再向下推(POJ3580)
    if (lazy[rt]) {
        if ()
        if ()
        lazy[rt] = 0;
    }
    inline void push_down(int rt) {
        if (fl[rt]) {
            swap(ch[rt][0], ch[rt][1]);
            if (ch[rt][0]) fl[ch[rt][0]] ^= 1;
            if (ch[rt][1]) fl[ch[rt][1]] ^= 1;
            fl[rt] = 0;
        }
        
    }
    


    void split(int rt, int k, int &x, int &y) { // 按照编号进行分裂
        if (!rt) x = y = 0;
        else {
            push_down(rt);
            if (k <= siz[ch[rt][0]]) {
                y = rt;
                split(ch[rt][0], k, x, ch[rt][0]);
            } else {
                x = rt;
                split(ch[rt][1], k - siz[ch[rt][0]] - 1, ch[rt][1], y);
            }
            push_up(rt);
        }
    }

    void split(int rt, int v, int &x, int &y) { // 按权值进行分裂
        if (!rt) x = y = 0;
        else {
            if (val[rt] <= v) {
                x = rt;
                split(ch[rt][1], v, ch[rt][1], y);
            } else {
                y = rt;
                split(ch[rt][0], v, x, ch[rt][0]);
            }
            push_up(rt);
        }
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (dat[x] < dat[y]) {
            push_down(x);
            ch[x][1] = merge(ch[x][1], y);
            push_up(x);
            return x;
        } else {
            push_down(y);
            ch[y][0] = merge(x, ch[y][0]);
            push_up(y);
            return y;
        }
    }

    void dfs(int rt) {
        push_down(rt);
        if (ch[rt][0]) dfs(ch[rt][0]);
        printf("%d ", val[rt]);
        if (ch[rt][1]) dfs(ch[rt][1]);
    }
} tree;

int main() {
    int n, q; scanf("%d%d", &n, &q);
    tree.build(1, n);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        int a, b, c;
        tree.split(tree.root, l - 1, a, b);
        tree.split(b, r - l + 1, b, c);
        tree.fl[b] ^= 1;
        tree.root = tree.merge(a, tree.merge(b, c));
    }
    tree.dfs(tree.root);
}