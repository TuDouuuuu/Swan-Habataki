int a[MAXN];
class DS { public:
    // treap begin
    struct treapnode {
        int ch[2], val, dat, siz, cnt;
    } tnd[MAXN*30];
    int tot;
    inline int New_treapnode(int v) {
        tot++;
        tnd[tot].ch[0] = tnd[tot].ch[1] = 0;
        tnd[tot].val = v, tnd[tot].dat = rand(), tnd[tot].siz = 1, tnd[tot].cnt = 1;
        return tot;
    }
#define lson tnd[rt].ch[0]
#define rson tnd[rt].ch[1]
    inline void push_up(int rt) {
        tnd[rt].siz = tnd[lson].siz + tnd[rson].siz + tnd[rt].cnt;
    }
    inline void rotate(int &rt, int d) {
        int tmp = tnd[rt].ch[d ^ 1];
        tnd[rt].ch[d ^ 1] = tnd[tmp].ch[d], tnd[tmp].ch[d] = rt, rt = tmp;
        push_up(tnd[rt].ch[d]), push_up(rt);
    }
    void insert(int &rt, int v) {
        if (!rt) {
            rt = New_treapnode(v);
            return;
        }
        if (v == tnd[rt].val) tnd[rt].cnt++;
        else {
            int d = v < tnd[rt].val ? 0 : 1;
            insert(tnd[rt].ch[d], v);
            if (tnd[rt].dat < tnd[tnd[rt].ch[d]].dat) rotate(rt, d ^ 1);
        }
        push_up(rt);
    }
    void remove(int &rt, int v) {
        if (!rt) return;
        if (v == tnd[rt].val) {
            if (tnd[rt].cnt > 1) {
                tnd[rt].cnt--, push_up(rt);
                return;
            }
            if (lson || rson) {
                if (!rson || tnd[lson].dat > tnd[rson].dat) {
                    rotate(rt, 1), remove(rson, v);
                } else rotate(rt, 0), remove(lson, v);
                push_up(rt);
            } else
                rt = 0;
        }
        v < tnd[rt].val ? remove(lson, v) : remove(rson, v);
        push_up(rt);
    }

    int get_rank(int rt, int v) {
        if (!rt) return 0;
        if (v == tnd[rt].val)
            return tnd[lson].siz;
        else if (v < tnd[rt].val)
            return get_rank(lson, v);
        else
            return tnd[lson].siz + tnd[rt].cnt + get_rank(rson, v);
    }

    bool isexit(int rt, int v) {
        if (!rt) return 0;
        if (v == tnd[rt].val)
            return 1;
        else if (v < tnd[rt].val)
            return isexit(lson, v);
        else
            return isexit(rson, v);
    }

    void init() {
        tot = 0;
    }
    // treap end

    struct segnode {
        int l, r, root;
    } T[MAXN << 2];

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        for (int i = l; i <= r; i++)
            insert(T[rt].root, a[i]);
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    }

    void modify(int rt, int pos, int v) { // a[pos] -> v;
        remove(T[rt].root, a[pos]), insert(T[rt].root, v);
        if (T[rt].l == T[rt].r) {
            a[pos] = v;
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) modify(rt << 1, pos, v);
        else modify(rt << 1 | 1, pos, v);
    }

    int get_rank(int rt, int L, int R, int v) {  // op1
        if (L <= T[rt].l && T[rt].r <= R) return get_rank(T[rt].root, v);
        int mid = (T[rt].l + T[rt].r) >> 1;
        int ans = 0;
        if (L <= mid) ans += get_rank(rt << 1, L, R, v);
        if (R > mid) ans += get_rank(rt << 1 | 1, L, R, v);
        return ans;
    }

    bool isexit(int rt, int L, int R, int v) {
        if (L <= T[rt].l && T[rt].r <= R) return isexit(T[rt].root, v);
        int mid = (T[rt].l + T[rt].r) >> 1;
        bool ans = false;
        if (L <= mid) ans |= isexit(rt << 1, L, R, v);
        if (R > mid) ans |= isexit(rt << 1 | 1, L, R, v);
        return ans;
    }
} tree;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    tree.build(1, 1, n);
    while (m--) {
        int opt; scanf("%d", &opt);
        if (opt == 1) {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", tree.get_rank(1, l, r, k) + 1);
        } else if (opt == 2) {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            int L = 0, R = 1e8;
            while (L < R) {
                int mid = (L + R + 1) >> 1;
                if (tree.get_rank(1, l, r, mid) >= k) R = mid - 1;
                else L = mid;
            }
            printf("%d\n", L);
        } else if (opt == 3) {
            int pos, k; scanf("%d%d", &pos, &k);
            tree.modify(1, pos, k);
        } else if (opt == 4) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            int num = tree.get_rank(1, l, r, k); // the rank of k
            if (num == 0) printf("-2147483647\n");
            else {
                int L = 0, R = 1e8;
                while (L < R) {
                    int mid = (L + R + 1) >> 1;
                    if (tree.get_rank(1, l, r, mid) >= num) R = mid - 1;
                    else L = mid;
                }
                printf("%d\n", L);
            }
        } else if (opt == 5) {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            int num = tree.get_rank(1, l, r, k + 1);
            if (num == r - l + 1) printf("2147483647\n");
            else {
                num++;
                int L = 0, R = 1e8;
                while (L < R) {
                    int mid = (L + R + 1) >> 1;
                    if (tree.get_rank(1, l, r, mid) >= num) R = mid - 1;
                    else L = mid;
                }
                printf("%d\n", L);
            }
        }
    }
}