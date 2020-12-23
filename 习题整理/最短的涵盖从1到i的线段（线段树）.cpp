/*  [input]     [output]
    5 3         1 3 3
    1 3 2 3 1
*/
int init_val[MAXN];
class SEG { public:
    struct node {
        int l, r;
        int val, minn;  // val是维护的右端点，minn是线段长度
    } T[MAXN << 2];
    int lazy[MAXN << 2];
    inline void push_up(int rt) {
        T[rt].minn = min(T[rt << 1].minn, T[rt << 1 | 1].minn);
        T[rt].val = min(T[rt << 1].val, T[rt << 1 | 1].val);
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            T[rt].minn = init_val[l] - r + 1;
            T[rt].val = init_val[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    inline void push_down(int rt) {
        if (lazy[rt]) {
            T[rt << 1].val = lazy[rt], T[rt << 1 | 1].val = lazy[rt];
            T[rt << 1].minn = lazy[rt] - T[rt << 1].r + 1, T[rt << 1 | 1].minn = lazy[rt] - T[rt << 1 | 1].r + 1;
            lazy[rt << 1] = lazy[rt], lazy[rt << 1 | 1] = lazy[rt];
            lazy[rt] = 0;
        }
    }
    int query_left(int rt, int L, int R, int v) {
        if (T[rt].r < L || T[rt].l > R) return -1;
        if (T[rt].l == T[rt].r) return T[rt].l;
        push_down(rt);
        int ans = -1;
        if (T[rt << 1].val < v) ans = query_left(rt << 1, L, R, v);
        if (ans == -1 && T[rt << 1 | 1].val < v) ans = query_left(rt << 1 | 1, L, R, v);
        return ans;
    }
    int query_right(int rt, int L, int R, int v) {
        if (T[rt].r < L || T[rt].l > R) return -1;
        if (T[rt].l == T[rt].r) return T[rt].l;
        push_down(rt);
        int ans = -1;
        if (T[rt << 1 | 1].val < v) ans = query_right(rt << 1 | 1, L, R, v);
        if (ans == -1 && T[rt << 1].val < v) ans = query_right(rt << 1, L, R, v);
        return ans;
    }
    void change(int rt, int L, int R, int v) {
        if (L <= T[rt].l && T[rt].r <= R) {
            T[rt].val = v;
            T[rt].minn = v - T[rt].r + 1;
            lazy[rt] = v;
            return;
        }
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) change(rt << 1, L, R, v);
        if (R > mid) change(rt << 1 | 1, L, R, v);
        push_up(rt);
    }
} tree;
int a[MAXN];
vector<int> vec[MAXN];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) vec[a[i]].pb(i);
    int pos = inf;
    for (int i = n; i >= 1; i--) {
        if (a[i] == 1) pos = i;
        init_val[i] = pos;
    }
    tree.build(1, 1, n);
    printf("%d", tree.T[1].minn);   // m = 1
    for (int i = 2; i <= m; i++) {
        for (int j = 0; j < SZ(vec[i]); j++) {
            int l, r, p = vec[i][j];
            if (j == 0) { // segment no 1
                l = 1, r = vec[i][j];
            } else l = vec[i][j - 1] + 1, r = vec[i][j];
            int left = tree.query_left(1, l, r, p);
            int right = tree.query_right(1, l, r, p);
            if (left == -1 && right == -1) {

            } else {
                tree.change(1, left, right, p);
            }
        }
        if (vec[i][SZ(vec[i]) - 1] == n) {}
        else {
            tree.change(1, vec[i][SZ(vec[i]) - 1] + 1, n, inf);   // 忘记+1导致debug了好久
        }
        printf(" %d", tree.T[1].minn);
    }
}