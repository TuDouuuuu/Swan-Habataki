class SEG { public:
    struct Node {
        int l, r;
        int pre, suf, len;
    } T[MAXN << 2];

    void Build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        T[rt].pre = T[rt].suf = T[rt].len = r - l + 1;
        if (l == r) return;
        int mid = (l + r) >> 1;
        Build(rt << 1, l, mid);
        Build(rt << 1 | 1, mid + 1, r);
    }

    inline void push_up(int rt) {
        T[rt].pre = T[rt << 1].pre;
        T[rt].suf = T[rt << 1 | 1].suf;
        T[rt].len = max(T[rt << 1].len, T[rt << 1 | 1].len);
        T[rt].len = max(T[rt].len, T[rt << 1].suf + T[rt << 1 | 1].pre);
        if (T[rt << 1].pre == T[rt << 1].r - T[rt << 1].l + 1)T[rt].pre += T[rt << 1 | 1].pre;
        if (T[rt << 1 | 1].suf == T[rt << 1 | 1].r - T[rt << 1 | 1].l + 1)
            T[rt].suf += T[rt << 1].suf;
    }

    // call: tree.update(1, x, 0); 摧毁
    //       tree.update(1, x, 1); 修复

    void update(int rt, int pos, int val) {
        if (T[rt].l == T[rt].r) {
            T[rt].pre = T[rt].suf = T[rt].len = val;
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid)update(rt << 1, pos, val);
        else update(rt << 1 | 1, pos, val);
        push_up(rt);
    }

    int query(int rt, int pos) {
        if (T[rt].l == T[rt].r || T[rt].len == 0 || T[rt].len == T[rt].r - T[rt].l + 1) {
            return T[rt].len;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) {
            if (pos >= T[rt << 1].r - T[rt << 1].suf + 1)
                return query(rt << 1, pos) + query(rt << 1 | 1, mid + 1);
            else return query(rt << 1, pos);
        } else {
            if (pos <= T[rt << 1 | 1].l + T[rt << 1 | 1].pre - 1)
                return query(rt << 1 | 1, pos) + query(rt << 1, mid);
            else return query(rt << 1 | 1, pos);
        }
    }
} tree;