/*  [input]     [output]
    1
    8 4
    2 1 1 4 4 6 2 3
    1 6 4       5
    2 5         6
    1 1 1       0
    1 8 2       14
                2 2 4 6 3 2 3 1
*/
int b[MAXN];
class FHQ { public:
    int ch[MAXN][2];
    int val[MAXN], minn[MAXN], siz[MAXN], dat[MAXN];
    ll sum[MAXN];
    int tot, root;
    int seq[MAXN], seq_tot;
    void init() {
        root = 1; tot = 0;
        val[0] = sum[0] = siz[0] = 0;
        minn[0] = inf_int;
        seq_tot = 0;
    }
    void dfs(int rt) {
        if (ch[rt][0]) dfs(ch[rt][0]);
        seq[seq_tot++] = val[rt];
        if (ch[rt][1]) dfs(ch[rt][1]);
    }
    void get_seq() {
        dfs(root);
        for (int i = 0; i < seq_tot; i++) {
            if (i) printf(" ");
            printf("%d", seq[i]);
        }
        printf("\n");
    }
    int New(int v) {
        val[++tot] = v, dat[tot] = rand(), minn[tot] = v, siz[tot] = 1;
        sum[tot] = (ll) v;
        ch[tot][0] = ch[tot][1] = 0;
        return tot;
    }
    inline void push_up(int rt) {
        siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + 1;
        minn[rt] = min(val[rt], min(minn[ch[rt][0]], minn[ch[rt][1]]));
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]] + (ll) val[rt];
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
    void split_minn(int rt, int k, int &x, int &y) {
        if (!rt) x = y = 0;
        else {
            if (minn[ch[rt][1]] < k || val[rt] < k) {
                x = rt;
                split_minn(ch[rt][1], k, ch[rt][1], y);
            } else {
                y = rt;
                split_minn(ch[rt][0], k, x, ch[rt][0]);
            }
            push_up(rt);
        }
    }
    int get_Kth(int rt, int k) {
        if (siz[ch[rt][0]] + 1 == k) return val[rt];
        else if (siz[ch[rt][0]] >= k) return get_Kth(ch[rt][0], k);
        else return get_Kth(ch[rt][1], k - siz[ch[rt][0]] - 1);
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
    void op1(int x, int y) {
        int h = get_Kth(root, x);
        if (h < y) {
            printf("0\n"); return ;
        }
        int left_, _right;
        split_id(root, x, left_, _right);
        int minn_, _minn;
        split_minn(left_, y, minn_, _minn);
        if (minn_ == 0) {
            root = merge(merge(minn_, _minn), _right);
            printf("0\n"); return ;
        }
        int pos_3 = get_Kth(minn_, siz[minn_]);
        int pos_4 = get_Kth(_minn, 1);
        int new_v = pos_4 - (y-1) + pos_3;
        int yx, shk, hjy;
        int yx_, _yx;
        split_id(minn_, siz[minn_]-1, yx_, _yx);
        int new_3 = New(new_v);
        yx = merge(yx_, new_3);
        printf("%lld\n", sum[_minn] - (ll)siz[_minn] * (ll)(y-1));  // 打印有多少格子有动
        int shk_, _shk;
        split_id(_minn, 1, shk_, _shk);
        int new_6 = New(y-1);
        shk = merge(_shk, new_6);
        hjy = _right;
        root = merge(yx, merge(shk, hjy));
    }
    void op2(int x) {
        printf("%d\n", get_Kth(root, x));
    }
} tree;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        tree.init();
        int n, q; scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
        tree.root = tree.build(1, n);
        while (q--) {
            int op; scanf("%d", &op);
            if (op == 1) {
                int x, y; scanf("%d%d", &x, &y);
                tree.op1(x, y);
            } else {
                int x; scanf("%d", &x); // 查询第x列
                tree.op2(x);
            }
        }
        tree.get_seq();
    }
}