class LCT { public:
    int val[MAXN], sum[MAXN];
    int st_top, st[MAXN];   // stack操作
    int fa[MAXN], ch[MAXN][2];
    bool rev[MAXN];

    inline bool isroot(int x) { // 判断x是否为一个splay的根
        return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
    }
    inline void push_up(int x) {
        int l = ch[x][0], r = ch[x][1];
        sum[x] = sum[l] ^ sum[r] ^ val[x];  // 记录链上异或值
    }
    inline void push_down(int x) {
        int l = ch[x][0], r = ch[x][1];
        if (rev[x]) {
            if (l) swap(ch[l][0], ch[l][1]), rev[l] ^= 1;
            if (r) swap(ch[r][0], ch[r][1]), rev[r] ^= 1;
            rev[x] = 0;
        }
    }
    inline void rotate(int x) { // x向上旋转
        int y = fa[x], z = fa[y], l, r;
        if (ch[y][0] == x) l = 0;
        else l = 1;
        r = l ^ 1;
        if (!isroot(y)) {
            if (ch[z][0] == y) ch[z][0] = x;
            else ch[z][1] = x;
        }
        fa[x] = z, fa[y] = x;
        fa[ch[x][r]] = y;
        ch[y][l] = ch[x][r];
        ch[x][r] = y;
        push_up(y), push_up(x);
    }
    inline void splay(int x) {  // 使得x成为当前splay中的根
        st_top = 0;
        st[++st_top] = x;
        for (int i = x; !isroot(i); i = fa[i]) st[++st_top] = fa[i];
        for (int i = st_top; i; i--) push_down(st[i]);
        while (!isroot(x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y)) {
                if (ch[y][0] == x ^ ch[z][0] == y) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
    inline void access(int x) { //把x到根节点的路径搞成一个splay
        for (int i = 0; x; i = x, x = fa[x])
            splay(x), ch[x][1] = i, push_up(x);
    }
    inline void makeroot(int x) {   // 使得p成为原树的根
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]), rev[x] ^= 1;
    }
    inline int find(int x) {    // 找到x在原树的根
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);   // 非常重要！一定注意！
        return x;
    }

    void split(int x, int y) {  // 拉出x-y的路径搞成一个splay
        makeroot(x);
        access(y);
        splay(y);   // y为根, call: tree.sum[y]
    }
    void link(int x, int y) {   // 连接x,y
        makeroot(x);
        if (find(y) == x) return;
        fa[x] = y;
        return;
    }
    void cut(int x, int y) {    // 断开x,y
        makeroot(x);
        if (find(y) != x || fa[y] != x || ch[y][0]) return; // 两条不连通
        ch[x][1] = fa[y] = 0;
        push_up(x);
        return ;
    }
    void change(int x, int v) { // 修改某一点的值
        splay(x);
        val[x] = v;
        push_up(x);
    }
    bool isconnect(int x, int y) {  // 判断两点是否连通
        makeroot(x);
        if (find(y) != x) return 0; // 两条不连通
        else return 1;
    }
} tree;