class LT {  public:
    int pool[MAXN], pool_cnt;

    int fa[MAXN];
    int find(int x) {
        if (x == fa[x]) return x;
        else return fa[x] = find(fa[x]);
    }

    int val[MAXN], ch[MAXN][2], dist[MAXN];

    int tot;
    inline int New() {
        return pool_cnt ? pool[pool_cnt--] : ++tot;
    }
    inline void Del(int &rt) {
        pool[++pool_cnt] = rt;
        fa[rt] = val[rt] = ch[rt][0] = ch[rt][1] = dist[rt] = 0;
        rt = 0;
    }
    void init() { tot = 0, pool_cnt = 0; }
    inline int Newnode(int v) { // 初始化左偏树节点
        int nrt = New();
        val[nrt] = v, ch[nrt][0] = ch[nrt][1] = dist[nrt] = 0;
        fa[nrt] = nrt;
        return nrt;
    }

    int merge(int x, int y) {   // 合并左偏树，
                                // call：root[fx] = tree.merge(root[fx], root[fy]);
        if (!x || !y) return x + y;
        if (val[x] == val[y] ? x > y : val[x] > val[y]) swap(x, y); // 小根堆
        ch[x][1] = merge(ch[x][1], y);
        if (dist[ch[x][0]] < dist[ch[x][1]]) swap(ch[x][0], ch[x][1]);
        fa[ch[x][0]] = fa[ch[x][1]] = fa[x] = x;
        dist[x] = dist[ch[x][1]] + 1;
        return x;
    }
    int insert(int rt, int v) { // call：root[x] = tree.insert(root[x], y);
        return merge(rt, Newnode(v));
    }
    int pop(int rt) {   // call：root[fx] = tree.pop(root[fx]);
        int tl = ch[rt][0], tr = ch[rt][1];
        Del(rt);
        return merge(tl, tr);
    }
    bool isempty(int x) {   // call：tree.isempty(root[fx])
                            // 为空返回1，不为空返回0
        return x == 0;
    }
    int top(int x) {    // call：tree.top(root[fx])
        return val[x];
    }

} tree;