int blen, bep;
class HJT {
public:
    struct node {
        int lson, rson, maxx;
    } T[MAXN * 70];
    int tol;
#define ls T[rt].lson
#define rs T[rt].rson
    inline void push_up(int rt) {
        T[rt].maxx = max(T[ls].maxx, T[rs].maxx);
    }
    int build(int l, int r) {
        int nrt = ++tol;
        int mid = (l + r) >> 1;
        T[nrt].lson = T[nrt].rson = 0; T[nrt].maxx = bep;
        if (l < r) {
            T[nrt].lson = build(l, mid);
            T[nrt].rson = build(mid + 1, r);
            push_up(nrt);
        }
        return nrt;
    }
    int query(int rt, int R, int be, int en) {
        if (be == en) return be;
        int ans = -1;
        int mid = (be + en) >> 1;
        if (T[ls].maxx > R) ans = query(T[rt].lson, R, be, mid);
        if (ans == -1 && T[rs].maxx > R) ans = query(T[rt].rson, R, mid + 1, en);
        return ans;
    }
} tree;

int arr[MAXN], root[MAXN];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
    Discrete::push(0);
    for (int i = 1; i <= n; i++) Discrete::push(arr[i]), Discrete::push(arr[i] + 1);
    Discrete::init();
    bep = n + 1;
    root[n + 1] = tree.build(1, blen);
    for (int i = n; i >= 1; i--) {
        int x = Discrete::lb(arr[i]);
        root[i] = tree.update(root[i + 1], 1, blen, x, i);
    }
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int res = tree.query(root[l], r, 1, blen);
        if (res == -1) res = blen;
        printf("%d\n", Discrete::get_num(res));
    }
}
