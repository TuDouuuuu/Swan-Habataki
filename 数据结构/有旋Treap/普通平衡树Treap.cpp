// MAXN为最多维护的树中数的个数
class Treap {
private:
    int ch[MAXN][2];
    int val[MAXN], dat[MAXN], sz[MAXN], cnt[MAXN];
    int tot, root;

    int New(int v) {
        val[++tot] = v;
        dat[tot] = rand();
        sz[tot] = 1;
        cnt[tot] = 1;
        return tot;
    }

    void pushup(int id) {
        sz[id] = sz[ch[id][0]] + sz[ch[id][1]] + cnt[id];
    }

    void Rotate(int &id, int d) {
        int temp = ch[id][d ^ 1];
        ch[id][d ^ 1] = ch[temp][d];
        ch[temp][d] = id;
        id = temp;
        pushup(ch[id][d]), pushup(id);
    }

    void _insert(int &id, int v) {
        if (!id) {
            id = New(v);
            return;
        }
        if (v == val[id])cnt[id]++;
        else {
            int d = v < val[id] ? 0 : 1;
            _insert(ch[id][d], v);
            if (dat[id] < dat[ch[id][d]]) Rotate(id, d ^ 1);
        }
        pushup(id);
    }

    void _Remove(int &id, int v) {
        if (!id)return;
        if (v == val[id]) {
            if (cnt[id] > 1) {
                cnt[id]--, pushup(id);
                return;
            }
            if (ch[id][0] || ch[id][1]) {
                if (!ch[id][1] || dat[ch[id][0]] > dat[ch[id][1]]) {
                    Rotate(id, 1), _Remove(ch[id][1], v);
                } else Rotate(id, 0), _Remove(ch[id][0], v);
                pushup(id);
            } else id = 0;
            return;
        }
        v < val[id] ? _Remove(ch[id][0], v) : _Remove(ch[id][1], v);
        pushup(id);
    }

    int _get_rank(int id, int v) {
        if (!id) return 0;
        if (v == val[id]) return sz[ch[id][0]] + 1;
        else if (v < val[id]) return _get_rank(ch[id][0], v);
        else return sz[ch[id][0]] + cnt[id] + _get_rank(ch[id][1], v);
    }

    int _get_val(int id, int rank) {
        if (!id) return inf_int;
        if (rank <= sz[ch[id][0]]) return _get_val(ch[id][0], rank);
        else if (rank <= sz[ch[id][0]] + cnt[id]) return val[id];
        else return _get_val(ch[id][1], rank - sz[ch[id][0]] - cnt[id]);
    }

    int _get_pre(int v) {
        int id = root, pre;
        while (id) {
            if (val[id] < v)pre = val[id], id = ch[id][1];
            else id = ch[id][0];
        }
        return pre;
    }

    int _get_next(int v) {
        int id = root, next;
        while (id) {
            if (val[id] > v)next = val[id], id = ch[id][0];
            else id = ch[id][1];
        }
        return next;
    }

public:
    void init() {
        tot = 0;
        root = 0;
        root = New(-inf_int), ch[root][1] = New(inf_int);
        pushup(root);
    }

    void insert(int x) { _insert(root, x); }    // 插入x数

    void remove(int x) { _Remove(root, x); }    // 删除x数(若有多个相同的数，因只删除一个)

    int get_rank(int x) { return _get_rank(root, x) - 1; }  // 查询x数的排名(排名定义为比当前数小的数的个数+1)

    int get_val(int x) { return _get_val(root, x + 1); }    // 查询排名为x的数

    int get_pre(int x) { return _get_pre(x); }  // 求x的前驱(前驱定义为小于x，且最大的数)

    int get_next(int x) { return _get_next(x); }    // 求x的后继(后继定义为大于x，且最小的数)
} tree;