class Treap { public:
    int ch[MAXN][2], dat[MAXN], siz[MAXN], val[MAXN], cnt[MAXN];
    int tot;
    int pool[MAXN], pool_cnt;
    void init() { tot = 0, pool_cnt = 0; }
    inline int Newid() {
        return pool_cnt ? pool[pool_cnt--] : ++tot;
    }
    inline void Delid(int &rt) {
        if (!rt) return;
        pool[++pool_cnt] = rt;
        dat[rt] = siz[rt] = val[rt] = cnt[rt] = 0;
        ch[rt][0] = ch[rt][1] = val[rt] = 0;
        rt = 0;
    }
    inline int Newnode(int v, int _cnt = 1) {
        int nid = Newid();
        val[nid] = v, dat[nid] = rand(), siz[nid] = _cnt, cnt[nid] = _cnt;
        ch[nid][0] = ch[nid][1] = 0;
        return nid;
    }
    inline void push_up(int rt) {
        siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + cnt[rt];
    }
    inline void Rotate(int &rt, int d) {
        int temp = ch[rt][d ^ 1];
        ch[rt][d ^ 1] = ch[temp][d];
        ch[temp][d] = rt;
        rt = temp;
        push_up(ch[rt][d]), push_up(rt);
    }

    void insert(int &rt, int v, int _cnt = 1) {
        if (!rt) {
            rt = Newnode(v, _cnt);
            return;
        }
        if (v == val[rt]) cnt[rt] += _cnt;
        else {
            int d = v < val[rt] ? 0 : 1;
            insert(ch[rt][d], v, _cnt);
            if (dat[rt] < dat[ch[rt][d]]) Rotate(rt, d ^ 1);
        }
        push_up(rt);
    }
    void remove(int &rt, int v) {
        if (!rt) return;
        if (v == val[rt]) {
            if (cnt[rt] > 1) {
                cnt[rt]--, push_up(rt);
                return;
            }
            if (ch[rt][0] || ch[rt][1]) {
                if (!ch[rt][1] || dat[ch[rt][0]] > dat[ch[rt][1]]) {
                    Rotate(rt, 1), remove(ch[rt][1], v);
                } else {
                    Rotate(rt, 0), remove(ch[rt][0], v);
                }
                push_up(rt);
            } else Delid(rt);
            return;
        }
        v < val[rt] ? remove(ch[rt][0], v) : remove(ch[rt][1], v);
        push_up(rt);
    }
    
    int Kth(int rt, int k) {  // call:tree.Kth(root[find(x)], k); 与x相连的第k大值
        if (!rt) return 0;
        if (k <= siz[ch[rt][1]]) return Kth(ch[rt][1], k);
        else if (k <= siz[ch[rt][1]] + cnt[rt]) return val[rt];
        else return Kth(ch[rt][0], k - siz[ch[rt][1]] - cnt[rt]);
    }
    void merge(int &x, int &y) {
        if (ch[x][0]) merge(ch[x][0], y);
        if (ch[x][1]) merge(ch[x][1], y);
        if (cnt[x] > 0) insert(y, val[x], cnt[x]);
        Delid(x);
    }
} tree;

int F[MAXN];
int root[MAXN];

int find(int x) {
    if (F[x] == x) return x;
    else return F[x] = find(F[x]);
}
void join(int u, int v) { // 两个点相连
    int fu = find(u), fv = find(v);
    if (fu != fv) {
        if (tree.siz[fu] < tree.siz[fv]) F[fu] = fv, tree.merge(root[fu], root[fv]);
        else F[fv] = fu, tree.merge(root[fv], root[fu]);
    }
}

void change(int x, int v, int oldv) { // 将点x的值从oldv -> v
    int fx = find(x);
    tree.remove(root[fx], oldv);
    tree.insert(root[fx], v);
}
