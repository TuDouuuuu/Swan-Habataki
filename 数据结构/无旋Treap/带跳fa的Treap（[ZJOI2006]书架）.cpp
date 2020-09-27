class FHQ { public:
    int ch[MAXN][2];
    int val[MAXN], dat[MAXN], siz[MAXN], pos[MAXN], fa[MAXN];
    int tot, root;
    void init() {
        root = 1, tot = 0, val[0] = siz[0] = 0;
        fa[1] = 0;
    }
    int New(int v) {
        val[++tot] = v, dat[tot] = rand(), siz[tot] = 1, fa[tot] = 0;
        ch[tot][0] = ch[tot][1] = 0;
        pos[v] = tot; //  值所在的位置，用于跳fa
        return tot;
    }
    inline void push_up(int rt) {
        siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + 1;
        if (ch[rt][0]) fa[ch[rt][0]] = rt;
        if (ch[rt][1]) fa[ch[rt][1]] = rt;
    }
    int build(int l, int r) {
        if (l > r) return 0;
        int mid = (l + r) >> 1;
        int newnode = New(b[mid]);
        ch[newnode][0] = build(l, mid - 1);
        ch[newnode][1] = build(mid + 1, r);
        push_up(newnode);
        return newnode;
    }
    void split_id(int rt, int k, int &x, int &y) {
        if (!rt) x = y = 0;
        else {
            if (k <= siz[ch[rt][0]]) {
                y = rt;
                split_id(ch[rt][0], k, x, ch[rt][0]);
            } else {
                x = rt;
                split_id(ch[rt][1], k - siz[ch[rt][0]] - 1, ch[rt][1], y);
            }
            push_up(rt);
        }
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (dat[x] < dat[y]) {
            ch[x][1] = merge(ch[x][1], y);
            push_up(x);
            return x;
        } else {
            ch[y][0] = merge(x, ch[y][0]);
            push_up(y);
            return y;
        }
    }
    int get_pos(int v) {
        int rt = pos[v];
        int ans = 1 + siz[ch[rt][0]];
        while (fa[rt] && rt!= root) {
            int f = fa[rt];
            if (ch[f][1] == rt) ans += 1 + siz[ch[f][0]];
            rt = f;
        }
        return ans;
    }
} tree;
